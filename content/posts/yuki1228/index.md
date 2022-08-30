---
title: "yukicoder No.1228 - I hate XOR Matching"
date: 2020-09-12
tags: [yukicoder]
links:
  - label: "Problem link"
    url: "https://yukicoder.me/problems/no/1228"
  - label: "My Submission"
    url: "https://yukicoder.me/submissions/552082"
---

## 問題

以下を満たす長さ $n$ の整数列 $(a\_i)$ が存在すれば 1 つ構成せよ。

- $1 \\leq n \\leq 40$
- $0 \\leq a\_i \\lt 2\^\{20\}$
- 同じ値が 3 回以上出現しない。
- 空でない部分列 $2\^n-1$ 個のうち、全体の XOR が $k$ であるものがちょうど $x$ 個存在する。

### 制約

- $0 \\leq k \\lt 2\^\{20\}$
- $0 \\leq x \\leq 10\^9$

## 考察

$x=0$ の場合は $k$ でない要素 1 つからなる数列が条件を満たす。

「空でない部分列」というのが後々厄介なので、 $k=0$ のときに $x$ を 1 増やすことで以降「全ての部分列」と考える。

ここで $(a\_i)$ を $GF(2)$ 上の $20 \\times n$ 行列 $A$ として見たとき、 $A$ に列基本変形を施しても、全体の XOR が $k$ であるものの個数は変わらない。
よって全体の XOR が $k$ であるものの個数は、 $0$ 個か $2\^\{\\ker A\}$ 個となる。したがって、 $x = 2\^p$ という形で表せない場合、構成が不可能であることが分かる。

$x = 2\^p$ である場合、 $p = \\ker A$ より線形従属な要素がちょうど $p$ 個必要になる。
$p \\lt 2\^5$ なので、 $(2\^0, 2\^1, \\cdots, 2\^4, 0, \\cdots, p-1)$ とすれば、これを達成できる。
ただしこのままでは $k$ を作れるとは限らない。具体的には $k$ が $2\^0, \\cdots, 2\^4$ から作れない、つまり $k \\geq 2\^5$ の場合は $k$ を加える必要がある。

こうして得られる数列の長さは高々 $36$ なので、 $n \\leq 40$ の制約も満たしている。

## 実装例

{{<code file="0.cpp" language="cpp">}}