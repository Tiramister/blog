---
title: "Codeforces Round 613 F - Classical?"
date: 2020-01-16
tags: [codeforces]
links:
  - label: Problem link
    url: http://codeforces.com/contest/1285/problem/F
  - label: My Submission
    url: https://codeforces.com/contest/1285/submission/68893805
---

$\\gdef\\lcm\{\\operatorname\{lcm\}\}\\lcm$

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる． $\\max\_\{i \\neq j\} \\lcm (a\_i, a\_j)$ を求めよ．

### 制約

- $2 \\leq n \\leq 10\^5$
- $1 \\leq a\_i \\leq 10\^5 (= X)$

## 考察

LCM なので例によって $\\lcm(x, y) = \\dfrac\{xy\}\{\\gcd(x, y)\}$ と変形する．そこで GCD によって分類する，つまり $g$ を固定して GCD が $g$ のものについて考える．

$g$ の倍数しか考えなくていいので， $\\\{ a\_i \\\}$ から $g$ の倍数を抽出し，全て $g$ で割ったものを $\\\{ b\_i \\\}$ とする．この中で，互いに素なペアの積の最大値が求めるものである．

ここで最大値しか要らないことから， **スライド最大値** に似たテクニックを使う．まず $\\\{ b\_i \\\}$ を降順にソートし，前から順にスタックに入れていく．

途中で $b\_i$ と互いに素な要素がスタック内に存在すれば，それらが全て取り出されるまで **スタックから捨て続けていい** ，というのが肝．これは，スタックから捨てられた要素は $b\_i$ によって作られるペアより大きい積を作れないことから従う(スタックには上から **小さい** 要素が入っていて，数列の残りは $b\_i$ 以下であることに注意)．

後は「スタック内に $b\_i$ と互いに素なものが存在するか」を判定できればよいが，ここで [この記事](/blog/posts/mobius/) で説明したテクニックを使う．

## 実装例

{{<code file="0.cpp" language="cpp">}}
