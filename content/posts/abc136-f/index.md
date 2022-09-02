---
title: "AtCoder Beginner Contest 136 F - Enclosed Points"
date: 2019-10-28
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/abc136/tasks/abc136_f
  - label: My Submission
    url: https://atcoder.jp/contests/abc136/submissions/8184968
---

## 問題

2 次元空間上の $n$ 点集合 $S$ が与えられる(制約に注意)．

$S$ の空でない部分集合 $T$ に対して，

- $R(T) =$ 辺が座標軸に並行かつ $T$ を覆う最小の長方形
- $f(T) = R(T)$ が覆う $S$ 中の点の数

と定める． $\\sum\_\{\\emptyset \\neq T \\subseteq S\} f(T)$ を求めよ．

### 制約

- $1 \\leq n \\leq 2 \\times 10\^5$
- $-10\^9 \\leq x\_i, y\_i \\leq 10\^9$
- $S$ の任意の点対について，x 座標 **と** y 座標は異なる．

## 考察

よくある言い換えとして，各 $p \\in S$ について $p \\in R(T)$ を満たすような $T \\subseteq S$ の個数を代わりに求めることにする．
これは

- x 座標が $p$ より小さい
- y 座標が $p$ より小さい
- x 座標も y 座標も $p$ より小さい

ような点の数が求まれば，ちょっとした包除原理によって求められる([この問題](https://atcoder.jp/contests/abc003/tasks/abc003_4)と同じ感じ)．
1 つ目と 2 つ目は良いとして，問題は 3 つ目． $\\Theta(N\^2)$ が許させるなら累積和を取るのだが，そうはいかない．

そこで座圧をしてみることにする．すると， $S$ を x 座標についてソートしたとき y 座標は順列になっている．これを $(y\_i)$ とする．
$p$ が $i$ 番目のとき，求めたいのは $j \\lt i$ かつ $y\_j \\lt y\_i$ なる $j$ の個数だが，これはセグ木を使って転倒数と全く同じ要領で求められる．

ちなみに座圧したことで 1 つ目と 2 つ目も簡単に求められるようになって地味に嬉しい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
