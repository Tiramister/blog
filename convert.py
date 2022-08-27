import re
import sys


text: str = sys.stdin.read()


def search(pattern: str):
    global text
    return re.search(pattern, text, flags=re.DOTALL)


def findall(pattern: str):
    global text
    return re.findall(pattern, text, flags=re.DOTALL)


def sub_all(pattern: str, repl: str):
    global text
    text = re.sub(pattern, repl, text, flags=re.DOTALL)


def sub_once(pattern: str, repl: str):
    global text
    text = re.sub(pattern, repl, text, count=1, flags=re.DOTALL)


# タイトル退避
pattern = '\A# (.*?)\n'
title: str = search(pattern).group(1)
sub_all(pattern, '')

# タグ削除
pattern = '###### tags: .*?\n'
sub_all(pattern, '')

# 改行タグ削除
sub_all(r'<br[/\ ]*>', '')

# ソースコードを退避
code_id = 0
pattern = r'```(.*?)=\n(.*?)```'
while True:
    match = search(pattern)
    if match == None:
        break

    (language, code) = match.groups()
    if language == '':
        language = 'txt'

    filename = f'{code_id}.{language}'
    sub_once(
        pattern, '{{' + f'<code file="{filename}" language="{language}">' + '}}')
    with open(filename, 'w') as f:
        f.write(code)

# 複数行の数式を退避
eqs: list[str] = []
pattern = r'(\$\$.*?\$\$)'
while True:
    eq = search(pattern)
    if eq == None:
        break
    sub_once(pattern, f' <math-{len(eqs)}> ')
    eqs.append(eq.group(0))

# インライン数式を退避
pattern = r'(\$.*?\$)'
while True:
    eq = search(pattern)
    if eq == None:
        break
    sub_once(pattern, f' <math-{len(eqs)}> ')
    eqs.append(eq.group(0))

# リンクを退避
pattern = r'\[([^\[\]]*?)\]\((http.*?)\)'
links: list[tuple[str, str]] = findall(pattern)
sub_all(pattern, '')

# 数式を戻す
pattern = r'([_\'\^\{\}])'
for (id, eq) in enumerate(eqs):
    # 記号をエスケープ
    eq = re.sub(r'\\', r'\\\\\\\\', eq)
    eq = re.sub(pattern, r'\\\1', eq)
    sub_all(f'<math-{id}>', eq)

print(r'''---
title: "{}"
date:
tags: [atcoder]
links:'''.format(title))
for (label, url) in links:
    print(r'''  - label: "{}"
    url: "{}"'''.format(label, url))
print("---")
print(text)
