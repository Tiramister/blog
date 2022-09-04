import re
import sys
import requests
from typing import Callable, Optional, Match


class PatternType:
    def __init__(self, pattern: str, process: Callable[[Match], str]):
        self.__pattern: str = pattern
        self.__process: Callable[[Match], str] = process

    def match(self, text: str) -> Optional[str]:
        match = re.search(self.__pattern, text)
        if match:
            return self.__process(match)
        else:
            return None

    def subst(self, text: str, repl: str) -> str:
        return re.sub(self.__pattern, repl, text, 1)


class FrontMatter:
    title: str = ""
    date: str = ""
    tags: list[str] = []
    links: list[tuple[str, str]] = []

    @classmethod
    def to_string(cls) -> str:
        texts: list[str] = []
        texts.append("---")
        texts.append(f'title: "{cls.title}"')
        texts.append(f'date: {cls.date}')
        texts.append(f'tags: [{",".join(cls.tags)}]')
        texts.append(f'links:')
        for label, url in cls.links:
            texts.append(f"  - label: {label}")
            texts.append(f"    url: {url}")
        texts.append("---")
        return "\n".join(texts)


def insert_spaces(text: str) -> str:
    return f' {text} '


def set_title(title: str) -> str:
    FrontMatter.title = title
    return ""


def set_tags(tags: str) -> str:
    for tag in ['atcoder', 'codeforces', 'icpc', 'topcoder']:
        if re.search(tag, tags, re.IGNORECASE):
            FrontMatter.tags.append(tag)
    return ""


resource_id: int = 0


def save_code(language: str, code: str) -> str:
    global resource_id
    id: int = resource_id
    resource_id += 1

    if not language:
        language = "txt"
    filename: str = f'{id}.{language}'

    with open(filename, 'w') as f:
        f.write(code)

    return f'{{{{<code file="{filename}" language="{language}">}}}}'


def fetch_image(alt: str, src: str) -> str:
    global resource_id
    id: int = resource_id
    resource_id += 1

    ext = src.split('.')[-1]
    filename = f"{id}.{ext}"

    if src.startswith("http"):
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


def escapse_equation(equation: str) -> str:
    # バックスラッシュ
    equation = re.sub(r'\\', r'\\\\\\\\', equation)
    # それ以外の記号
    equation = re.sub(r'([_\'\^\{\}])', r'\\\1', equation)
    # align -> aligned
    equation = re.sub(r'\{align\}', '{aligned}', equation)
    return insert_spaces(equation)


def replace_link(label: str, url: str) -> str:
    for problem_text in ['問題', 'problem']:
        if re.search(problem_text, label, re.IGNORECASE):
            FrontMatter.links.append((label, url))
            return ""
    for submission_text in ['提出', 'submission']:
        if re.search(submission_text, label, re.IGNORECASE):
            FrontMatter.links.append((label, url))
            return ""
    return insert_spaces(f'[{label}]({url})')


pattern_types: list[PatternType] = [
    # タイトル
    PatternType('(?:^|\n)# (.*)', lambda match: set_title(match.group(1))),
    # タグ
    PatternType('(?:^|\n)#{6} tags: (.*)',
                lambda match: set_tags(match.group(1))),
    # 改行コード
    PatternType(r'<br\s?/?>', lambda _: ""),
    # ソースコード
    PatternType(r'```(\w*)=?\n((?:.|\s)*?)```',
                lambda match: save_code(match.group(1), match.group(2))),
    # 複数行数式
    PatternType(r'\$\$(?:.|\s)*?\$\$',
                lambda match: escapse_equation(match.group())),
    # インライン数式
    PatternType(r'\$(?:.|\s)*?\$',
                lambda match: escapse_equation(match.group())),
    # 画像
    PatternType(r'!\[([^\[\]]*?)\]\((.*?)\)',
                lambda match: fetch_image(match.group(1), match.group(2))),
    # リンク
    PatternType(r'\[([^\[\]]*?)\]\((.*?)\)',
                lambda match: replace_link(match.group(1), match.group(2))),
    # 太字 + 斜体
    PatternType(r'\*\*\*.*?\*\*\*',
                lambda match: insert_spaces(match.group())),
    # 太字
    PatternType(r'\*\*.*?\*\*',
                lambda match: insert_spaces(match.group())),
    # 斜体
    PatternType(r'\*.*?\*',
                lambda match: insert_spaces(match.group())),
]

text: str = sys.stdin.read()

new_texts: list[str] = []
for pattern_type in pattern_types:
    while True:
        new_text: Optional[str] = pattern_type.match(text)
        if new_text == None:
            break
        text = pattern_type.subst(text, f'<{len(new_texts)}>')
        new_texts.append(new_text)

# 置換と逆の順番で展開
for id, new_text in reversed(list(enumerate(new_texts))):
    text = re.sub(f'<{id}>', new_text, text)

print(FrontMatter.to_string())
print(text)
