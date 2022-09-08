from abc import ABC, abstractmethod
import re
import sys
import requests
from typing import Optional, Match


class FrontMatter:
    def __init__(self) -> None:
        self.title: str = ''
        self.date: str = ''
        self.tags: list[str] = []
        self.links: list[tuple[str, str]] = []

    def to_string(self) -> str:
        texts: list[str] = []
        texts.append('---')
        texts.append(f'title: "{self.title}"')
        texts.append(f'date: {self.date}')
        texts.append(f'tags: [{", ".join(self.tags)}]')
        texts.append(f'links:')
        for label, url in self.links:
            texts.append(f'  - label: "{label}"')
            texts.append(f'    url: {url}')
        texts.append('---')
        return '\n'.join(texts)


class IPattern(ABC):
    @abstractmethod
    def get_pattern(self) -> str:
        raise NotImplementedError

    @abstractmethod
    def process(self, match: Match) -> str:
        raise NotImplementedError

    def match(self, text: str) -> Optional[Match]:
        return re.search(self.get_pattern(), text)

    def subst(self, text: str, repl: str) -> str:
        return re.sub(self.get_pattern(), repl, text, 1)


# マッチした箇所を消す
class ErasePattern(IPattern):
    def __init__(self, pattern: str):
        self.__pattern = pattern

    def get_pattern(self) -> str:
        return self.__pattern

    def process(self, _: Match) -> str:
        return ''


# 前後にスペースを1つずつ追加する
class WrapBySpacePattern(IPattern):
    def __init__(self, pattern: str):
        self.__pattern = pattern

    def get_pattern(self) -> str:
        return self.__pattern

    def process(self, match: Match) -> str:
        text: str = match.group()
        return f' {text.strip()} '


class EquationPattern(IPattern):
    def __init__(self, pattern: str):
        self.__pattern = pattern

    def get_pattern(self) -> str:
        return self.__pattern

    def process(self, match: Match) -> str:
        equation: str = match.group()
        # バックスラッシュ
        equation = re.sub(r'\\', r'\\\\\\\\', equation)
        # それ以外の記号
        equation = re.sub(r'([_\'\^\{\}])', r'\\\1', equation)
        # align -> aligned
        equation = re.sub(r'\{align\}', '{aligned}', equation)
        return f' {equation.strip()} '


class CodeBlockPattern(IPattern):
    def __init__(self) -> None:
        self.__code_id: int = 0

    def get_pattern(self) -> str:
        return r'(?s)```(?P<lang>\w*)=?\n(?P<code>.*?)```'

    def process(self, match: Match) -> str:
        language: str = match.group('lang')
        code: str = match.group('code')

        id: int = self.__code_id
        self.__code_id += 1

        if not language:
            language = 'txt'
        filename: str = f'{id}.{language}'

        with open(filename, 'w') as f:
            f.write(code)
        return f'{{{{<code file="{filename}" language="{language}">}}}}'


class ImagePattern(IPattern):
    def __init__(self) -> None:
        self.__image_id: int = 0

    def get_pattern(self) -> str:
        return r'\s?!\[(?P<alt>[^\[\]]*?)\]\((?P<src>.*?)\)\s?'

    def process(self, match: Match) -> str:
        id: int = self.__image_id
        self.__image_id += 1

        alt: str = match.group('alt')
        src: str = match.group('src')

        ext: str = src.split('.')[-1]
        filename = f'{id}.{ext}'

        if src.startswith('http'):
            # 画像のダウンロード
            response = requests.get(src)
            if response.status_code != 200:
                print(f'Failed to fetch {src}', file=sys.stderr)
            elif 'image' not in response.headers['content-type']:
                print(f'Response of {src} is not an image', file=sys.stderr)
            else:
                with open(filename, 'wb') as f:
                    f.write(response.content)

        return f'{{{{<image src="{id}.{ext}" alt="{alt}">}}}}'


# FrontMatter に対して操作を行うようなパターン
class IPatternWithFrontMatter(IPattern):
    def __init__(self, front_matter: FrontMatter) -> None:
        self._front_matter: FrontMatter = front_matter


class TitlePattern(IPatternWithFrontMatter):
    def __init__(self, front_matter: FrontMatter) -> None:
        super(TitlePattern, self).__init__(front_matter)

    def get_pattern(self) -> str:
        return r'(?m)^# (?P<title>.*)$'

    def process(self, match: Match) -> str:
        title: str = match.group('title')
        self._front_matter.title = title
        return ''


class TagPattern(IPatternWithFrontMatter):
    def __init__(self, front_matter: FrontMatter) -> None:
        super(TagPattern, self).__init__(front_matter)

    def get_pattern(self) -> str:
        return r'(?m)^###### tags: (?P<tags>.*)$'

    def process(self, match: Match) -> str:
        tags: str = match.group('tags')
        for tag in ['atcoder', 'codeforces', 'icpc', 'topcoder']:
            if re.search(tag, tags, re.IGNORECASE):
                self._front_matter.tags.append(tag)
        return ''


class LinkPattern(IPatternWithFrontMatter):
    def __init__(self, front_matter: FrontMatter) -> None:
        super(LinkPattern, self).__init__(front_matter)

    def get_pattern(self) -> str:
        return r'\s?\[(?P<label>[^\[\]]*?)\]\((?P<uri>.*?)\)\s?'

    def process(self, match: Match) -> str:
        matched: str = match.group()
        label: str = match.group('label')
        uri: str = match.group('uri')

        for common_label in ['問題', 'problem', '提出', 'submission']:
            if re.search(common_label, label, re.IGNORECASE):
                self._front_matter.links.append((label, uri))
                return ''
        return (f' {matched.strip()} ')


def format(text: str) -> str:
    front_matter: FrontMatter = FrontMatter()

    patterns: list[IPattern] = [
        TitlePattern(front_matter),
        TagPattern(front_matter),
        ErasePattern(r'<br\s?/?>'),  # 改行タグ
        CodeBlockPattern(),
        ImagePattern(),
        EquationPattern(r'(?s)\$\$.*?\$\$'),  # 複数行数式
        EquationPattern(r'[ ]?\$.*?\$[ ]?'),  # インライン数式
        LinkPattern(front_matter),
        WrapBySpacePattern(r'[ ]?`.*?`[ ]?'),   # インラインコード
        WrapBySpacePattern(r'[ ]?\*\*_.*?_\*\*[ ]?'),  # 太字 + 斜体
        WrapBySpacePattern(r'[ ]?\*\*.*?\*\*[ ]?'),   # 太字
        WrapBySpacePattern(r'[ ]?_.*?_[ ]?'),   # 斜体
    ]

    # <id> で置換
    replacing_texts: list[tuple[str, int]] = []
    for pattern in patterns:
        while True:
            match: Optional[Match] = pattern.match(text)
            if match == None:
                break
            replacing_text: str = pattern.process(match)

            id: int = len(replacing_texts)
            text = pattern.subst(text, f'<{id}>')
            replacing_texts.append((replacing_text, id))

    # 置換と逆の順番で展開
    for replacing_text, id in reversed(replacing_texts):
        text = re.sub(f'<{id}>', replacing_text, text)

    return front_matter.to_string() + text


def main() -> None:
    text: str = sys.stdin.read()
    print(format(text))


if __name__ == '__main__':
    main()
