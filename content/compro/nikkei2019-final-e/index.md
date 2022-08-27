---
title: "第一回全国統一プログラミング王決定戦 (日経コン 2019) 本戦 E - Erasure"
date: 2020-02-14
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_e"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/nikkei2019-final/submissions/10080765"
---

## 問題

$n$ 個のマスが並んでいる．最初全てのマスの色は白である．

これから長さ $k+1$ 以上の区間をいくつか選び，各区間に対して以下の操作を行う．

- 区間を $[l, r]$ とする．
  - $r - l \\geq k$
- 各 $l \\leq i \\leq r$ について，マス $i$ を黒く塗る．

最終的に全てのマスが黒く塗られるような区間の選び方の総数を求めよ．

### 制約

- $1 \\leq k + 1 \\leq n \\leq 5 \\cdot 10\^3$

## 考察

$dp\_m =$ 「 $n = m$ のときの答え」を求める．
条件を満たさない選び方を重複なく数えるために，これらを「左から連続する黒マスの数」で区別することにする．

左から黒マスがちょうど $l$ マス連続するような選び方を数える．
このとき左から $l+1$ マス目は白，それより右側は自由に塗れる．よって長さ $l$ の区間に含まれる長さ $k+1$ の区間の個数を $p\_l$ とすると，そのような選び方は $dp\_\{l\} \\cdot 2\^\{p\_\{m - l - 1\}\}$ 通りとなる。

ここで問題文にもある通り， $p_l$ は以下で求まる。

$$
p\_l =
\\begin\{cases\}
0                            & (l \\leq k) \\\\
\\frac\{(l - k)(l - k + 1)\}\{2\} & (l \\gt k)
\\end\{cases\}
$$

以上より，

$$
\\begin\{aligned\}
  dp\_0 &= 1 \\\\
  dp\_m &= 2\^\{p\_m\} - \\sum\_\{l = 0\}\^\{m - 1\} dp\_\{l\} \\cdot 2\^\{p\_\{m - l - 1\}\}
\\end\{aligned\}
$$

となるので， $p$ を前計算すれば $O(n\^2)$ で DP テーブルが埋められる．

## 実装例

以下では $p\_l$ でなく $2\^\{p\_l\}$ を前計算している．今回は大丈夫だろうが，累乗は地味に時間が掛かるので注意．

{{<code file="0.cpp" language="cpp">}}
