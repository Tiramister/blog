---
title: 第四回 アルゴリズム実技検定(PAST) O - 宝箱
date: 2020-11-09
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/past202010-open/tasks/past202010_o
  - label: My Submission
    url: https://atcoder.jp/contests/past202010-open/submissions/18010296
---

## 問題

$N$ 個の宝箱がある。 $i$ 番目の宝箱を開けると $a\_i$ 円得られる。

あなたは金を払うことで $M$ 種類の鍵を得ることができる。
$i$ 番目の鍵は $c\_i$ 円するが、宝箱 $l\_i$ から $r\_i$ までを全て開けることができる。

利益 ($=$ 得られた金額 $-$ 払った金額) の最大値を求めよ。

### 制約

- $1 \\leq N, M \\leq 2 \\cdot 10\^5$
- $1 \\leq a\_i, c\_i \\leq 10\^9$

## 考察

インライン DP を軸に考える。 $dp\_i$ を「 $[1, i]$ の宝箱しかないときの利益の最大値」とすると、
宝箱を開けないときの更新式は単純に以下のようになる。

$$
dp\_i \\leftarrow dp\_\{i-1\}
$$

そして$ i $番目の鍵による更新式は以下のようになる。

$$
dp\_\{r\_i\} \\leftarrow \\max\_\{l\_i - 1 \\leq x \\lt r\_i\} \\left\\\{ dp\_\{x\} + \\sum\_\{j=x+1\}\^\{r\_i\} a\_j \\right\\\} - c\_i
$$

しかしこのままでは $\\sum\_\{j=x+1\}\^\{r_i\} a_j$ の項が ($x$ と $r\_i$ に依存していて)邪魔なので、なんとかしなくてはならない。
そのためには、 $\\sum\_\{j=x+1\}\^\{r_i\} a_j$ がデフォルトで加えられている、つまり **宝箱が全て開いている状態から、開けられない毎にペナルティが掛かる** と問題を言い換えればよい。

$dp\_i$ を「$[1, i]$ の宝箱しかないときのペナルティの最小値」と定め直す。
すると上 2 つの更新式は以下のようになる。

$$
\\begin\{aligned\}
dp\_i &\\leftarrow dp\_\{i-1\} + a\_i \\\\
dp\_\{r\_i\} &\\leftarrow \\min\_\{l\_i - 1 \\leq x \\lt r\_i\} \\\{ dp\_\{x\} \\\} + c\_i
\\end\{aligned\}
$$

これでセグメント木で処理できる形になった。
さらにここからグラフの最短路問題に変換することもできるが、それは公式解説を参照。

## 実装例

{{<code file="main.cpp" language="cpp">}}
