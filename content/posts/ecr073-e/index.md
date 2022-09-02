---
title: "Educational Codeforces Round 73 E - Game With String"
date: 2020-01-17
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1221/problem/E
  - label: My Submission
    url: https://codeforces.com/contest/1221/submission/68987208
---

## 問題

Alice と Bob が文字列 $s$ を使ってゲームをする．

$s$ は`.`と`X`からなり，Alice (resp. Bob) は自分のターンに連続する $a$ (resp. $b$ ) 個の`.`を`X`に変える． **ただし** $a \\gt b$ **が常に成り立つ** ．

自分のターンで操作が行えなくなった方の負けとなる．Alice が先攻のとき，どちらが勝つか判定せよ．

### 制約

- $1 \\leq |s| \\leq 3 \\cdot 10\^5$
- $1 \\leq b \\lt a \\leq 3 \\cdot 10\^5$

## 考察

まず重要な点として，操作に対称性がないので **Grundy 数は使えない** ．
よってアドホックに考察することとなる．

このゲームの極めて本質的な性質として，「長さ $b$ **以上** $a$ **未満の区間があると絶対 Bob が勝つ** 」というのがある．なぜなら Bob がこの区間を最後まで残し続ければ、 Bob の方が最後に 1 ターン長く生き残れるからだ．よって Bob の最善策は、長さ $b$ 以上 $a$ 未満の区間を作ることとなる．

Bob のターンに長さ $2b$ 以上の区間がある場合、左端から $b$ 個の `.` を残すように消せば Bob の勝ちとなる．よって最初の時点で長さ $2b$ 以上の区間が $2$ 個以上あると Bob の勝ち．一方で $0$ 個なら，お互いが区間を一個ずつ潰し合うことになるので，区間の個数の偶奇で勝敗が決まる．

残るは長さ $2b$ 以上の区間が $1$ 個の場合．この場合 Alice は真っ先にこの区間を潰すべきなので，この潰し方を全探索すればいい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
