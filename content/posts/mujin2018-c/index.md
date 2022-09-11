---
title: "Mujin Programming Challenge 2018 C - 右折"
date: 2018-08-05
tags: [atcoder]
links:
  - label: "Problem"
    url: https://atcoder.jp/contests/mujin-pc-2018/tasks/mujin_pc_2018_c
  - label: "My Submission"
    url: https://atcoder.jp/contests/mujin-pc-2018/submissions/2946983
---

## 概要

所々壁になっている $N \\times M$ の盤面が与えられる。

このとき、始点から 1 マス以上直進して中継点で右に 90 度ターンし、また 1 マス以上直進して終点へ着く、という経路が存在する始点と終点の組は全部で何通り考えられるか。

## 制約

- $2 \\leq N, M \\leq 2 \\times 10\^3$
- $s\_\{ij\}$ はマス $(i, j)$ が壁なら `#` 、何もないなら `.`

### 解説

超簡単に言えば、「 `#` を通らない L 字は盤面上にいくつあるか？」ということである。

ここで注目すべきは、始点でも終点でもなく **中継点** である。

{{<image src="0.png">}}

上のように、「中継点」と「方向」さえ決めれば、突き当たりまでのマス数の積で経路数が求められる。
具体的には、上下左右の突き当たりまでのマス数をそれぞれ $U, D, L, R$ とすると、そのマスを中継点とする経路の総数は以下で求められる。

$$
UL + LD + DR + RU = (U + D)(L + R)
$$

後は各マスについて $U, D, L, R$ を求めればいいのだが、愚直に突き当たるまで探索すると $O(NM(N + M))$ くらいの計算量になってしまう。
この計算量削減には色々な方法があるが、私はメモ化することで再計算を防ぐことにした。

## 解答例

{{<code file="0.cpp" language="cpp">}}
