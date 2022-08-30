---
title: "Typical DP Contest G - 辞書順"
date: 2020-01-24
tags: [atcoder]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1279/problem/E
  - label: My Submission
    url: https://atcoder.jp/contests/tdpc/tasks/tdpc_lexicographical
---

## 問題

文字列 $s$ の空でない部分文字列で，(存在すれば)辞書順で $k$ 番目のものを求めよ．

ただし， $s$ 上の異なる index から構成されたものでも，文字列として同じなら 1 つとして考える．

### 制約

- $1 \\leq |s| \\leq 10\^6$
- $1 \\leq k \\leq 10\^\{18\}$

## 考察

$dp\_\{i, c\} =$ 「 $s\_\{[i, n)\}$ の部分文字列で， $c$ から始まるものの個数」を求めたい．

$s\_\{[i, n)\}$ に $c$ が含まれない場合は $0$ ，そうでなければ **一番前にある** $c$ を先頭に使うと最も多くの部分文字列を作れる．よって $s\_j = c$ を満たす最小の $j \\geq i$ を取ると，

$$
dp\_\{i, c\} = 1 + \\sum\_\{d \\in \\Sigma\} dp\_\{j + 1, d\}
$$

となる． $\\Sigma$ はアルファベットの集合．先頭の $+1$ は部分文字列 $c$ の分．
これで $i$ について降順に $dp$ を埋めることができる。

後は $dp$ を参照しながら，先頭から文字を確定させていけばよい．

## 実装例

辞書順何番目は 0-indexed で考えるとやりやすい気がする(特に順列みたいに割りたいとき)．

あとなぜかこの問題は異様にメモリに厳しいので注意．`next`(次に $c$ が出てくる index)を各 index について持ったら MLE した．

{{<code file="0.cpp" language="cpp">}}
