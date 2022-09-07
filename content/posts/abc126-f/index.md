---
title: "AtCoder Beginner Contest 126 F - XOR Matching"
date: 2019-05-20
tags: [atcoder]
links:
  - label: "Problem"
    url: https://atcoder.jp/contests/abc126/tasks/abc126_f
  - label: "My Submission"
    url: https://atcoder.jp/contests/abc126/submissions/5484245
---

## 問題

以下の条件を満たす長さ $2\^\{M+1\}$ の数列 $\\\{a\_i\\\}$ を、存在するならば 1 つ構成せよ。

- $0, 1, \\cdots, 2\^M - 1$ がそれぞれ丁度 2 回ずつ現れる。
- $a\_i = a\_j$ なる任意の $i, j \\, (i \\lt j)$ について、 $a\_i \\oplus a\_\{i + 1\} \\oplus \\cdots \\oplus a\_j = K$ 。

ここで $\\oplus$ は bitwise xor を表す。

### 制約

- $0 \\leq M \\leq 17$
- $0 \\leq K \\leq 10\^9$

## 考察

これといって良いアイデアが浮かばなかったので、とりあえず以下のコードで実験することにした。

{{<code file="0.cpp" language="cpp" title="実験コード">}}

$M = 2, K = 1$ の解を求めると以下の通り。

{{<code file="1.txt" language="txt" title="実験結果">}}

`1:[0,1,0,3,2,1,2,3,]` がとても好例で、ここから $a, b, c, \\cdots, c, b, a$ のように配置をすると $a\_i = a, b, c$ の場合に値が一致することに気づく。この $\\cdots$ の部分が $K$ になるようにすればいい。というか $K$ 単体をそこに置けばいい。

これで $a\_i \\neq K$ なる $i$ については条件が満たされたが、 $a\_i = K$ ではどうだろうか。何とも都合のいいことに、 **$M \\geq 2$ では**

$$
0 \\oplus 1 \\oplus \\cdots K - 1 \\oplus K + 1 \\oplus \\cdots \\oplus 2\^M - 1 = K
$$

が成立する。これは $i \\equiv 3 \\pmod\{4\}$ で $0 \\oplus 1 \\oplus \\cdots \\oplus i = 0$ となることから従う。
よって $M \\geq 2$ かつ $K \\lt 2\^M$ では、

$$
\\\{0, 1, \\cdots, K - 1, K + 1, \\cdots, 2\^M - 1, K, \\\\
2\^M - 1, \\cdots, K + 1, K - 1, \\cdots, 1, 0, K\\\}
$$

が解となる。 $K \\geq 2\^M$ ではそもそも $K$ が作れないので解なし。

そしてコーナーケースである $M \\leq 1$ 。 $M = 0$ では $K = 0$ のみ解あり ($\\\{0, 0\\\}$) で、 $M = 1$ ではサンプルに答えがある。

## 実装例

{{<code file="2.cpp" language="cpp">}}
