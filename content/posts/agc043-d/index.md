---
title: "AtCoder Grand Contest 043 D - Merge Triplets"
date: 2020-09-06
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/agc043/tasks/agc043_d"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/agc043/submissions/16531893"
---

## 問題

長さ $3n$ の順列 $(p\_i)$ で、以下で生成されうるものの個数を求めよ。

1. 長さ $3$ の数列を $n$ 個用意する。これを $(a\_i)$ としたとき、 $(a\_i)$ には $1$ から $3n$ がちょうど一度ずつ出現する。
2. $(a\_i)$ で空でないもののうち、先頭が最小のものを $a\_i$ とする。
3. $(p\_i)$ の末尾に $a\_i$ の先頭を追加し、 $a\_i$ の先頭を削除する。
4. 全ての $(a\_i)$ が空でなければ 2 に戻る。

### 制約

- $1 \\leq n \\leq 2 \\cdot 10\^3$

## 考察

例えば $p\_2, \\cdots, p\_m$ が $p\_1$ より小さかったとする。このとき、 $p\_1, \\cdots, p\_m$ は同じ $a\_i$ に属さなければならない。これは他の数列の先頭が $p\_1$ より大きいためである。

そこで、 $(p\_i)$ を同じ数列に属さなければならないブロックに区切る。先程の考察から、 $p\_i$ がそれまでで最大である $i$ について、 $p\_\{i-1\}, p\_i$ の間を区切れば良いことが分かる。

すると「これらのブロックを組み替えて、大きさ $3$ のブロックを $n$ 個作れる」ことが必要条件となる。一方で、前のブロックから順に組み替えに従って並べていけば、 $(p\_i)$ を生成する $(a\_i)$ を作ることができる。つまりこれは十分条件となる。

これで $(p\_i)$ の必要十分条件が分かったが、これは「サイズ $4$ 以上のブロックが存在せず、サイズ $2$ 以上のブロックが $n$ 個以下である」ことと同値である。これは「長さ $k$ の順列で、サイズ $2$ 以上のブロックが $i$ 個である」という状態を持つ挿入 DP で、個数を計算できる。

## 実装例

{{<code file="0.cpp" language="cpp">}}