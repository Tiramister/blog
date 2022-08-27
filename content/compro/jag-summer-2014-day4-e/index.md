---
title: "JAG 夏合宿 2014 day4E - AI"
date: 2020-09-03
tags: [icpc, voluntary]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/search/titles/2643"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/2643/review/4815014/misteer/C++14"
---

## 問題

一部が壁になっている $h \\times w$ のグリッドに、北を向いたロボットが 1 体置かれている。またゴールと呼ばれるマスが 1 つ存在する。

ロボットの動作を決めるプログラム $s$ が与えられるので、ロボットはゴールに到達可能か、可能ならゴールに到達するまでに処理された動作命令数を求めよ。

なおプログラムの文法は以下の BNF で与えられる。
`<prog>`がプログラム全体、`<move-expr>`が動作命令に当たる。

{{<code file="0.txt" language="txt">}}

### 制約

- $1 \\leq h, w \\leq 50$
- $1 \\leq |s| \\leq 10\^3$
- $s$ は正しい文法である
- グリッドは壁で囲まれている

## 考察

ロボットの座標、向きを持ちながら構文解析をする。

1 つ問題となるのは、while 文で無限ループにハマるケース。この無限ループを検知するには、「過去にループの先頭で取ったことのある状態」を set で持ってやるとよい。

## 実装例

実装はストレートだが、量が多くて萎える。

{{<code file="0.cpp" language="cpp">}}
