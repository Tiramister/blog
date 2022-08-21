import re
import sys


text: str = sys.stdin.read()


def search(pattern: str):
    global text
    return re.search(pattern, text, flags=re.DOTALL)


def findall(pattern: str):
    global text
    return re.findall(pattern, text, flags=re.DOTALL)


def sub(pattern: str, repl: str):
    global text
    text = re.sub(pattern, repl, text, flags=re.DOTALL)


# タイトル
title: str = search('\A# (.*?)\n').group(1)
sub('\A# .*?\n', '')

# タグ削除
sub('###### tags: .*?\n', '')

# ソースコードを退避
for (id, (language, code)) in enumerate(findall(r'```(.*?)=\n(.*?)```')):
    filename: str = f'{id}.{language}'
    with open(filename, 'w') as f:
        f.write(code)
sub(r'```(.*?)```', r'{{<code file="main.cpp" language="cpp">}}')

# リンクを退避
links: list[tuple[str, str]] = findall(r'\[(.*?)\]\((.*?)\)')
sub(r'\[.*?\]\(.*?\)', '')

# 前後スペース
sub(r'(\$.+?\$)', r' \1 ')
sub(r'(\*.+?\*)', r' \1 ')
sub(r'(\*\*.+?\*\*)', r' \1 ')

# 数式内の特殊文字にバックスラッシュ
sub(r'([\\_\'\{\}])', r'\\\1')


print(r'''---
title: {}
date: 
tags: [atcoder, abc]
links:'''.format(title))
for (label, url) in links:
    print(r'''  - label: {}
    url: {}'''.format(label, url))
print("---")

print(text)
