---
title: "HUPC 2020 day3 M - Hokkaido High School"
date: 2020-09-17
tags: [voluntary]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/CVPC/3184"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/3184/review/4849307/misteer/C++17"
---

## 問題

ある学校には $M$ 個の科目があり、各科目について $1, 2, 3$ の 3 段階で評価が付けられる。

生徒 A と B について以下が成り立つとき、「A は B の*上位互換*である」という。

- 全ての科目について、A の評価は B の評価以上である。
- A の評価が B の評価より大きい科目が少なくとも 1 つ存在する。

今から $Q$ 人の学生が教室に入ってくる。入ってきた学生は、教室に既に自分の上位互換の学生が存在するときに*悲しく*なる。悲しくなる学生の人数を求めよ。

### 制約

- $1 \\leq Q \\leq 5 \\cdot 10\^5$
- $1 \\leq M \\leq 15$

## 考察

全ての評価パターン $3\^M$ 通りについて、「既に上位互換が存在するか」を持つテーブルを更新することを考える。

パターン $S$ が追加されたとしよう。このとき $S$ の下位互換の値を全て true に更新しなければならない。
科目 $i$ の評価が $S$ より 1 少ないパターンを $S\_i\'$ とすると、各 $i$ について以下を行えばよい。

- $S\_i\'$ の値を true に更新する。
- $S\_i\'$ の下位互換の更新を再帰的に行う。

しかし、この処理を毎回愚直に行っていると間に合わない。

そこで「 $S\_i\'$ の値が true なら、過去に $S\_i\'$ の下位互換は更新されている」という性質を用いて、「 $S\_i\'$ の値が既に true なら処理しない」という枝刈りを加える。
これで各パターンについて更新処理を行う回数は高々 1 回となるので、全体の計算量が $O(M 3\^M + QM)$ に落ちる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
