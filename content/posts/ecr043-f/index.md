---
title: "Educational Codeforces Round 43 F - Minimal k-covering"
date: 2020-02-18
tags: [codeforces]
links:
  - label: "Problem link"
    url: "https://codeforces.com/contest/976/problem/F"
  - label: "My Submission"
    url: "https://codeforces.com/contest/976/submission/71258581"
---

## 問題

二部グラフ $G = (U, V, E)$ が与えられる． $G$ の最小次数を $D$ としたとき，各 $0 \\leq k \\leq D$ について以下の問に答えよ．

- $(U, V, E\')$ の最小次数が $k$ となる $E\' \\subseteq E$ で， $|E\'|$ が最小のものを求めよ．

### 制約

- $1 \\leq |U|, |V| \\leq 2 \\cdot 10\^3$
- $0 \\leq |E| \\leq 2 \\cdot 10\^3$

## 考察

単純にフローでやろうとすると，「 $s \\to U, V \\to g$ の各辺に流量下限 $k$ を設定したときの最小流」みたいになる．これを流量下限付き最小費用流で解くことができるかもしれないが，発想を変えるともっと自然になる．

「最小流」というのはよく分からないので，見慣れた「最大流」にしたくなる．そこで「残す辺の数を最小化」ではなく「**消す辺の数を最大化**」することにしてみる．

頂点 $v$ の次数を $d\_v$ としたとき， $v$ と接続する辺で消せるのは $d\_v - k$ 本まで．逆にこれが全ての頂点で満たされていれば，消した後も全頂点の次数は $k$ 以上なので OK．したがって「 $s \\to U, V \\to g$ の各辺に流量上限 $d\_v - k$ を設定したときの最大流」で消す辺が求まる．

計算量は 1 回のフローに $O(\\sqrt\{n\}m)$ で $D \\leq \\sqrt\{m\}$ なので[^1]，全体で $O(\\sqrt\{nm\}m)$ ．

[^1]: 完全二部グラフが worst case．

## 実装例

{{<code file="0.cpp" language="cpp">}}
