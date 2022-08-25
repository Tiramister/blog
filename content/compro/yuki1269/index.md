---
title: "yukicoder No.1269 - I hate Fibonacci Number"
date: 2020-10-24
tags: [yukicoder]
links:
  - label: "Problem link"
    url: "https://yukicoder.me/problems/no/1269"
  - label: "My Submission"
    url: "https://yukicoder.me/submissions/570836"
---

## 問題

フィボナッチ数列 $(F\_i)$ を以下のように定める。

- $F\_0 = F\_1 = 1$
- $F\_i = F\_\{i-1\} + F\_\{i-2\} \\quad (i \\geq 2)$

また $(F\_i)$ に出現する整数をフィボナッチ数ということにする。

以下を満たす正整数 $M$ の個数 $\\pmod\{10\^9+7\}$ を求めよ。なお整数の表記は 10 進法とする。

- $M$ は $N$ 桁以下である。
- $M$ の連続部分列として、 $L$ 以上 $R$ 以下のフィボナッチ数が出現しない。

### 制約

- $1 \\leq N \\leq 5 \\cdot 10\^3$
- $1 \\leq L \\leq R \\leq 10\^\{18\}$

## 考察

フィボナッチ数は指数的に増加するので、「 $L$ 以上 $R$ 以下のフィボナッチ数」はそれほど多くないと推測できる(高々 86 個らしい)。ということで最初にこれを列挙する。

後は $M$ を長さ $N$ の数字列と見れば、禁止文字列条件付きの文字列数え上げ問題になる。これは Aho-Corasick 法により線形時間でできる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
