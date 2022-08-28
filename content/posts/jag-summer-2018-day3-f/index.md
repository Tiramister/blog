---
title: JAG 夏合宿 2018 day3 F - Nim without Zero
date: 2020-11-14
tags: [icpc]
links:
  - label: Problem link
    url: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2909?year=2018
  - label: My Submission
    url: https://onlinejudge.u-aizu.ac.jp/solutions/problem/2909/review/4987004/misteer/C++17
---

## 問題

長さ $N$ の非負整数列 $(a\_i)$ を使って Alice と Bob がゲームを行う。

ゲームは Alice が先攻のターン制で進む。
各ターンにプレイヤーは $0$ でない $a\_i$ を 1 つ選び、 $a\_i$ より小さい任意の非負整数に置き換える。
操作の直後に $a\_1 \\oplus \\cdots \\oplus a\_N = 0$ となった場合、その操作をしたプレイヤーの負けとなる。

両者が最適な戦略でこのゲームをプレイしたとき、どちらが勝つか求めよ。

### 制約

- $1 \\leq N \\leq 10\^5$
- $1 \\leq a\_i \\leq 10\^9$

## 考察

こういうゲームはとりあえず小さい $N$ で実験してみるのが良かったりする。
実際に $N=2$ で実験すると、 $(2k, 2k), (2k, 2k+1), (2k+1, 2k)$ の 3 パターンでのみ Bob の勝ちとなることが分かる。

よく考えてみると、 $(2k, 2k+1), (2k+1, 2k)$ というのは「全体の XOR が $1$」と同値である。
XOR が 1 で渡された場合、ルール上 XOR を 0 にできないので操作後の XOR は必ず 2 以上になる。
そして相手は通常の Nim 同様、常に XOR を 1 に減らすことができる。

後は $(2k, 2k)$ だが、これは\* _最初から XOR が_ \_ $0$ のケースに当たる。
この場合 Alice は XOR を 1 に変えたくなるが、**全てが偶数である場合** に限りこれができない。

よってこれら 2 つが Bob が勝つ必要十分条件となる。

## 実装例

{{<code file="main.cpp" language="cpp">}}
