---
title: "Codeforces Round #190 C - Ciel the Commander"
date: 2020-02-13
tags: [codeforces]
links:
  - label: "Problem link"
    url: "https://codeforces.com/problemset/problem/321/C"
  - label: "My Submission"
    url: "https://codeforces.com/contest/321/submission/70939113"
---

## 問題

木 $G = (V, E)$ が与えられる．以下を満たす各 $v \\in V$ への大文字アルファベットの割り付け $(a\_v)$ を求めよ．

- $a\_u = a\_v$ なる相異なる $u, v \\in V$ を任意に取る．
- パス $u, v$ 上にある頂点 $w$ が存在して， $a\_w \\lt a\_u$ ．

### 制約

- $2 \\leq |V| \\leq 10\^5$

## 考察

まず $A$ を割り当てる頂点は高々 1 つでなくてはならない．そこである $v \\in V$ を取って $a\_v = A$ としたとする．

すると，B が割り当てられる頂点対は $v$ を跨いでいればよい．これはすなわち， $G$ から $v$ を削除してできる森を考えたときに，異なる連結成分上に存在していればよい．逆に同じ連結成分上にあるとパスに $v$ が含まれないのでアウト．
よって各連結成分から $B$ を割り当てる頂点を 1 つずつ選べる．

以上から，以下を繰り返すことで割り当てを決められる．

1. 各連結成分から 1 つずつ頂点を選ぶ．選んだ頂点集合を $S$ とする．
2. 各 $v \\in S$ について， $a\_v$ にまだ割り当てられていないアルファベットを割り当てる．
3. $G$ から $S$ を削除する．

このループの回数が 26 回以内ならよい．

問題は各連結成分からどの頂点を選ぶかだが，削除後の連結成分のサイズを極力小さくすることを考えると， **重心** が良いことが分かる．実際，分解後の最大の連結成分のサイズは 1 ステップ毎に半分になるので， $2\^\{17\} \\gt |V|$ より上のループは 17 回以内で終わる．

## 実装例

実装はガチで重心分解をやるだけなので，重心分解の verify に使える．
今回は重心分解ライブラリも折りたたまずにそのまま載せておく．

{{<code file="0.cpp" language="cpp">}}
