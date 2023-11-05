---
title: "WUPC 2020 L - Count Pow Sum"
date: 2020-09-23
tags: [voluntary]
---

[3162 < VPC WUPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/WUPC/3162)

## 問題

以下の形式のクエリが $Q$ 個与えられるので処理せよ。

整数 $a, l, r$ が与えられる。 $\\sum\_\{k=l\}\^\{r\} \\lfloor (a + \\sqrt\{a\^2 - 1\})\^k \\rfloor \\bmod\{10\^9+7\}$ を求めよ。

### 制約

- $1 \\leq Q \\leq 10\^4$
- $1 \\leq a \\leq 10\^9$
- $0 \\leq l \\leq r \\leq 10\^9$

## 考察

まず $f(n) = \\sum\_\{k=0\}\^\{n-1\} \\lfloor (a + \\sqrt\{a\^2 - 1\})\^k \\rfloor$ とすれば(半開区間であることに注意)、解は $f(r+1) - f(l)$ なので、そちらを求めればよい。

床関数がついていると難しいので、まず $g(k) = (a + \\sqrt\{a\^2 - 1\})\^k$ から考える。
$g(k) = p\_k + q\_k \\sqrt\{a\^2 - 1\}$ とおくと、以下のようになる。

- $p\_0 = 1, q\_0 = 0$
- $p\_\{k+1\} = a p\_k + (a\^2 - 1) q\_k$
- $q\_\{k+1\} = p\_k + a q\_k$

線形漸化式なので、これは行列累乗によって高速に求めることができる。

問題は床関数がついた場合だが、これは知らないと正直厳しい。

$h(k) = (a - \\sqrt\{a\^2 - 1\})\^k$ という関数を考えると、これは $h(k) = p\_k - q\_k \\sqrt\{a\^2 - 1\}$ を満たす。
よって $g(k) + h(k) = 2p\_k$ となり、整数になる。
さらに $0 \\lt a - \\sqrt\{a\^2 - 1\} \\leq 1$ より $0 \\lt h(k) \\leq 1$ が成り立つので、 $\\lfloor g(k) \\rfloor = 2p\_k - 1$ となる。

したがって $f(n) = \\sum\_\{k=0\}\^\{n-1\} \\lfloor g(k) \\rfloor = 2 \\sum\_\{k=0\}\^\{n-1\} p\_i - n$ となる。 $\\sum\_\{k=0\}\^\{n-1\} p\_i$ も、行列を少し変更すれば高速に求まる。

## 実装例

[Run #4865597 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3162/review/4865597/misteer/C++17)

```cpp
#include <iostream>
#include <array>
#include <atcoder/modint>

namespace ac = atcoder;

template <class T, int D>
struct Vector { ... };

template <class T, int D>
struct Matrix { ... };

using mint = ac::modint1000000007;
using Vec = Vector<mint, 3>;
using Mat = Matrix<mint, 3>;

mint calc(int n, int a) {
    Vec v;  // p, q, psum
    v[0] = 1;

    Mat m;
    m[0][0] = a, m[0][1] = mint(a) * a - 1;
    m[1][0] = 1, m[1][1] = a;
    m[2][0] = 1, m[2][2] = 1;

    auto psum = (m.pow(n) * v)[2];
    return psum * 2 - n;
}

void solve() {
    int a, l, r;
    std::cin >> a >> l >> r;

    auto ans = calc(r + 1, a) - calc(l, a);
    std::cout << ans.val() << "\n";
}
```

