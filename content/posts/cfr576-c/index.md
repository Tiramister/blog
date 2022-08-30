---
title: "Codeforces Round 576 C - Matching vs Independent Set"
date: 2020-01-21
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1198/problem/C
  - label: My Submission
    url: https://codeforces.com/contest/1198/submission/69231665
---

## 問題

$3n$ 頂点 $m$ 辺の無向グラフが与えられる．サイズ $n$ のマッチングかサイズ $n$ の独立集合のうち、どちらか一方を出力せよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $0 \\leq m \\leq 5 \\cdot 10\^5$

## 考察

結論を言うと，「極大マッチングに接続しない頂点の集合は独立集合をなす」という性質を使う
証明は簡単で，ある $uv \\in E$ が存在してどちらも極大マッチングと接続しないとき，辺 $uv$ を追加することでより大きいマッチングが作れるので極大性に矛盾する．

したがって極大マッチングのサイズが $n$ 以上ならそれを出力，そうでなければ接続しない頂点が少なくとも $n$ 個あるのでそれらを出力すればよい。

## 実装例

{{<code file="0.cpp" language="cpp">}}
