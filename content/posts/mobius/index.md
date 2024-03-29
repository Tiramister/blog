---
title: "集合内の x と互いに素な要素の個数(メビウス関数)"
date: 2020-01-15
tags: [algorithm]
---

[これ](https://codeforces.com/contest/1285/problem/F) を解いていたら出てきた部分問題で，それ自体興味深かったので独立で扱うことにした．

## 問題

最初集合 $S$ は空である．以下の 3 種類のクエリを $q$ 回処理せよ．

1.  $S$ に $x$ を追加する．
2.  $S$ から $x$ を削除する．
3.  $S$ 内の $x$ と互いに素な要素の個数を出力する．

### 制約

- $1 \\leq x \\leq 10\^5$
- $1 \\leq q \\leq 10\^5$

## 考察

最大公約数が絡む問題は，「約数に対して全て足すと上手くいく」ような係数を考えると良いことがある．今回もその方針で係数を考えることにする．

以下のような性質を満たす関数 $f, g$ を考える．

- $f(1) = 1$
- $f(n) = - \\sum\_\{d|n, d \\lt n\} f(d)$
- $g(n) = \\sum\_\{d|n\} f(d)$

すると， $f$ の定義から $g$ は以下の性質を満たす．

- $g(1) = 1$
- $g(n) = 0 \\quad (n \\gt 1)$

よって $y$ について $c\_d = 1 \\iff d|y \\; (\\text\{otherwise\}  \\; 0)$ と定めれば，

$$
\\sum\_\{d|x\} f(d) c\_d = \\sum\_\{d|x, d|y\} f(d) =
\\sum\_\{d|\\gcd(x, y)\} f(d) = g(\\gcd(x, y))
$$

より，この値は $x, y$ が互いに素なときのみ $1$ となる．

これを拡張して，集合 $S$ に対して $c\_d = |\\\{x \\in S \\mid d | x \\\}|$ ，つまり「 $d$ を約数にもつ要素数」と定義すれば， $\\sum\_\{d|x\} f(d) c\_d$ で解が求まる．

$f$ は定義通り「約数から貰う」という方針で計算すると，約数列挙に $O(\\sqrt\{n\})$ かかるので $O(n \\sqrt\{n\})$ になる．
一方で「倍数に配る」という方針なら調和級数で $O(n \\log n)$ に落ちる．この方針で各 $x \\leq 10\^5$ についてその約数を事前に列挙しておけば，取得クエリも $c$ の更新も $O(\\log n)$ でできる．

よって全体の計算量は，集合の操作を無視すれば $O((n + q) \\log n)$ となる．

## $f$ is 何

実はここで出てきた $f$ には名前がついていて，その名も **メビウス関数** という．そしてメビウス関数 $\\mu$ は，通常以下の定義で与えられることが多い．

- $\\mu(x) = 0$ ( $x$ が平方因子を持つ，つまり $1$ 以外の平方数で割り切れる)
- $\\mu(x) = 1$ (上を満たさず，かつ素因数の個数が奇数)
- $\\mu(x) = -1$ (それ以外)

この 2 つの定義が同値であることの証明は省略．

## 応用

$f$ の定義で出た

- $f(n) = - \\sum\_\{d|n, d \\lt n\} f(d) \\quad (n \\gt 1)$

は言わば「陽的」な表現で，以下のような「陰的」な表現の方がその性質を理解しやすいだろう．

- $\\sum\_\{d|n\} f(d) = \\delta(n, 1)$

ここで $\\delta(n, 1)$ はクロネッカーのデルタで、 $n=1$ のときのみ $1$ で他は $0$ となる。

これを応用して，適当な関数 $h$ に対して

- $\\sum\_\{d|n\} f(d) = h(n)$

と定義してやることができる．

今回の問題では「$h(n) = \\delta(n, 1)$ 」( $\\delta$ はクロネッカーのデルタ) となっている.

