---
title: JAG 模擬地区 2013 F - Shipura
date: 2020-11-14
tags: [icpc]
links:
  - label: Problem link
    url: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2570?year=2013
  - label: My Submission
    url: https://onlinejudge.u-aizu.ac.jp/solutions/problem/2570/review/4990718/misteer/C++17
---

## 問題

以下の BNF で表される言語を考える。

```text
expr ::= term | expr sp ">>" sp term
term ::= number | "S" sp "<" sp expr sp ">"
```

ここで`sp`は 0 個以上のスペースからなる文字列、`number`は $0$ 以上 $10\^9$ 以下の整数を表す。

言語の評価規則は以下の通り。

- `x>>y`は $\\left\\lfloor \\frac\{x\}\{2\^y\} \\right\\rfloor$ と評価される。
- `S<x>`は $x\^2 \\bmod\{10\^9 + 7\}$ と評価される。

`expr`で表現可能な文字列が与えられるので、それを評価した結果を求めよ。

### 制約

- 文字列の長さは $2 \\cdot 10\^6$ 以下

## 考察

何も考えずに実装すると、入力例にある`S<S<S<S<S<2>>>>>`でパースエラーになる。
これは「`S<x>`中の`>`が 2 つ連なったもの」と、「`x>>y`中の`>>`」が区別できないためである。

これを区別するために、何らかのアドホックな処理が必要になる。
以下の実装では、「`S<S<x>>`のような項の直後に`term`は来ない」ことを利用して、「`>>`の後に`S`か数字が来るかどうか」で判定をしている。

## 実装例

C++11 以降のコンパイラって偉いな〜というお気持ちになる。

{{<code file="main.cpp" language="cpp">}}
