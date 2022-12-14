---
title: "第一回日本最強プログラマー学生選手権決勝 F - Count Permutations Many Times"
date: 2020-10-22
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_f"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/jsc2019-final/submissions/17569521"
---

## 問題

長さ $N$ の数列 $(A\_i)$ が与えられる。以下の形式で与えられる $Q$ 個のクエリを処理せよ。

各クエリでは整数 $L, R$ が与えられる。
$(0, \\cdots, N-1)$ の順列 $(p\_i)$ で、全ての整数 $i \\in [L, R)$ について $p\_i \\neq A\_i$ が成り立つものの個数 $\\pmod\{998,244,353\}$ を求めよ。

### 制約

- $1 \\leq N \\leq 2 \\cdot 10\^3$
- $0 \\leq A\_i \\leq N-1$
- $1 \\leq Q \\leq 2 \\cdot 10\^3$
- $0 \\leq L \\lt R \\leq N$

## 考察

### クエリが 1 つの場合

求めるものが攪乱順列の個数に似ているので、攪乱順列と同様の包除原理を考える。
区間 $[L, R)$ における整数 $i$ の出現回数を $c\_i$ とすると、以下の式で答えが求まる。

$$
\\sum\_\{S \\subseteq [N]\} (-1)\^\{|S|\} (N - |S|)! \\prod\_\{i \\in S\} c\_i
$$

$S$ が条件に違反する整数の集合である。なお $[N] = \\\{ 0, \\cdots, N-1 \\\}$ とする。

上の式において、 $\\prod\_\{i \\in S\} c\_i$ の部分以外は $|S|$ にしか依存しない。
よって $|S|$ 毎の $\\prod\_\{i \\in S\} c\_i$ の総和が求まればよいが、これは母関数によって計算できる。具体的には、

$$
f(x) = \\prod\_\{i=0\}\^\{N-1\} (1 + c\_i x)
$$

という多項式を考えたとき、 $x\^k$ の係数が $|S|=k$ における $\\prod\_\{i \\in S\} c\_i$ の総和となっている。

### クエリが複数の場合

各クエリの計算量は $O(N\^2)$ なので、上をそのまま実装すると TLE する。

ここで、区間の拡張・縮小が割と簡単に処理できることに着目する。
区間の拡張で整数 $i$ の出現回数が $1$ 増えたとき、 $f(x)$ は以下のように更新できる。

$$
f(x) \\leftarrow \\frac\{1 + (c\_i + 1)x\}\{1 + c\_i x\} f(x)
$$

この更新にかかる計算量は $O(N)$ 。縮小もほとんど同様。

区間の拡張・縮小が簡単にできるとき、**Mo's Algorithm**が有効である。
つまりクエリを適当に並び替えることで、区間の拡張・縮小回数を全体で $O((N+Q)\\sqrt\{N\})$ に抑えられる。
よって計算量 $O((N+Q)N\\sqrt\{N\})$ でこの問題が解けた。

## 実装例

ちなみに TL が緩めなので、Mo's Algorithm のブロックサイズを 1 にしても通る。

{{<code file="0.cpp" language="cpp">}}
