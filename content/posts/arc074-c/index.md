---
title: "AtCoder Regular Contest 074 C - Chocolate Bar"
date: 2018-09-17
tags: [atcoder]
links:
  - label: "Problem"
    url: https://atcoder.jp/contests/arc074/tasks/arc074_a
  - label: "My Submission"
    url: https://atcoder.jp/contests/arc074/submissions/34748518
---

## 概要

$H \\times W$ のグリッド状をした板チョコがある。これを切れ目に沿って長方形に 3 分割したとき、(最大のピースの面積)-(最小のピースの面積)の最小値を求めよ。

### 制約

- $2 \\leq H, W \\leq 10\^5$

## 解説

いかにも数学っぽい問題だが、数学で解こうとするとパターンが多くて苦戦する。今回は制約が小さいので、プログラムの力でゴリ押すのが吉となる。

まず「最初に横の切れ目で折る」ケースを考える。こうすれば後は、上半分の板チョコをできるだけ 2 等分する問題へ帰着される。2 等分になってしまえば問題は簡単で、ほぼ真ん中の位置で縦と横両方で割ってみればいい。

{{<image src="0.png">}}

これを全ての切れ目で試せばいい。

残るは「最初に縦の切れ目で折るケース」だが、これはチョコを 90 度回転させれば、先のケースに帰着できる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
