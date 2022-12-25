# [Tiramister's Blog](https://tiramister.net/blog/)

## 必要なもの

- [Hugo](https://gohugo.io/)

## コマンド

```sh
# 記事を作成
hugo new content/posts/{dir-name}/index.md

# サーバーを立てる。
# localhost:1313/blog/ でアクセスできる。
# -D で draft も見られるようになる。
hugo server [-D]

# ビルド結果を /public/ に出力する。
# 以前のビルド結果を勝手に消してくれないので、事前に消しておくこと。
hugo
```

## Git に関する注意

このレポジトリは submodule として [hugo-theme-terminal](https://github.com/panr/hugo-theme-terminal) を含むため、 clone の際はこれらも clone する必要がある。

```sh
# submodule ごと clone する。
git clone --recursive <このレポジトリ>

# 既に clone してしまった場合は、以下で submodule を clone できる。
git submodule update --init --recursive
```
