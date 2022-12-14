---
title: "AtCoder Grand Contest 005 D - ~K Perm Counting"
date: 2020-02-18
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/agc005/tasks/agc005_d"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/agc005/submissions/10062125"
---

## 問題

整数 $n, k$ が与えられる．長さ $n$ の順列 $(p\_i)$ で，以下を満たすものの個数を求めよ．

- 任意の $i$ について， $|p\_i - i| \\neq k$ ．

### 制約

- $2 \\leq n \\leq 2 \\cdot 10\^3$
- $1 \\leq k \\leq n - 1$

## 考察

どう見ても包除原理なので包除原理で考える．

順列を二部グラフで見たとき，差の絶対値が $k$ になる辺を $x$ 本先に引いてしまえば，残りはどう繋いでもよい．よって各 $x$ 本の張り方に対して $(n - x)!$ 通りの順列が対応する．

後は $x$ 本の張り方の数え方だが，厄介なことに「 $(1)-(4)\'$ を結んだ後に $(7)-(4)\'$ は結べない」みたいな依存関係がある．よって普通に DP しようとすると，直前 $2k$ 個くらいについて「上に繋いだか？」を持つ必要がある．

しかしこの依存関係について考えてみると， $(i)-(i+k)\'-(i+2k)-\\cdots$ のようなジグザグのパス上にしか依存関係が存在しない．よって二部グラフの頂点をこのジグザグなパスに分解することで，各々を独立に解ける．

各々は「直前で上に繋いだか？」を状態として持つ DP で解けて，マージは多項式の積でできる．多項式の積を普通にやると TLE しそうだが，木の二乗 DP と全く同じ理由から計算量は $O(n\^2)$ に収まる．

## 実装例

{{<code file="0.cpp" language="cpp">}}
