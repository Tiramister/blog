---
title: "yukicoder No.1201 お菓子配り-4"
date: 2020-08-29
tags: [yukicoder]
---

[No.1201 お菓子配り-4 - yukicoder](https://yukicoder.me/problems/no/1201)

## 問題

長さ $n, m$ の数列 $\\\{ a\_i \\\}, \\\{ b\_j \\\}$ が与えられるので、以下を求めよ $\\pmod\{10\^9+7\}$ 。

$$
\\sum\_\{i=1\}\^\{n\} \\sum\_\{j=1\}\^\{m\} \\sum\_\{k=1\}\^\{b\_j\}
   2 \\left\\lfloor \\frac\{a\_i k\}\{b\_j\} \\right\\rfloor
$$

### 制約

- $1 \\leq n, m \\leq 2 \\cdot 10\^3$
- $0 \\leq a\_i \\leq 10\^8$
- $1 \\leq b\_j \\leq 10\^8$

## 考察

$i, j$ を固定して以下を高速に求めることを考える。

$$
\\sum\_\{k=1\}\^\{b\} \\left\\lfloor \\frac\{a k\}\{b\} \\right\\rfloor
$$

まず切り捨ては考えにくいので、以下のように式変形する。

$$
\\begin\{aligned\}
       \\sum\_\{k=1\}\^\{b\} \\left\\lfloor
           \\frac\{a k\}\{b\} \\right\\rfloor
   &=
       \\sum\_\{k=1\}\^\{b\} \\frac\{a k - (ak \\bmod b)\}\{b\} \\\\
   &=
       \\frac\{a\}\{b\} \\sum\_\{k=1\}\^\{b\} k -
       \\frac\{1\}\{b\} \\sum\_\{k=1\}\^\{b\} (ak \\bmod b)
\\end\{aligned\}
$$

前者の $\\sum$ は簡単に $\\frac\{b(b+1)\}\{2\}$ と分かるので、後者の $\\sum$ を考える。

ここで $a, b$ が互いに素であると仮定する。すると $ak \\bmod b$ は $k = 1, \\cdots, b$ で $0, 1, \\cdots, b-1$ を一度ずつ経由することが分かる。よって総和は $\\frac\{b(b-1)\}\{2\}$ となる。

一般の場合でも、 $g = \\gcd(a, b), a\' = \\frac\{a\}\{g\}, b\' = \\frac\{b\}\{g\}$ とすれば、 $a\', b\'$ は互いに素なので以下のように変形できる。

$$
\\begin\{aligned\}
       \\sum\_\{k=1\}\^\{b\} (ak \\bmod b)
   &=
       g \\sum\_\{k=1\}\^\{b\} (a\'k \\bmod b\') \\\\
   &=
       g\^2 \\sum\_\{k=1\}\^\{b\'\} (a\'k \\bmod b\') \\\\
   &=
       \\frac\{1\}\{2\} g\^2 b\' (b\' - 1) \\\\
   &=
       \\frac\{1\}\{2\} b (b - g) \\\\
\\end\{aligned\}
$$

以上を整理すると、以下の通り。

$$
\\begin\{aligned\}
       \\sum\_\{k=1\}\^\{b\} 2 \\left\\lfloor
           \\frac\{a k\}\{b\} \\right\\rfloor
   &=
       \\frac\{2a\}\{b\} \\sum\_\{k=1\}\^\{b\} k -
       \\frac\{2\}\{b\} \\sum\_\{k=1\}\^\{b\} (ak \\bmod b) \\\\
   &=
       \\frac\{a\}\{b\} \\cdot b (b + 1) -
       \\frac\{1\}\{b\} \\cdot b (b - g) \\\\
   &=
       a (b + 1) - (b - g) \\\\
   &=
       ab + a - b + g
\\end\{aligned\}
$$

## 実装例

[#543046 (C++17) No.1201 お菓子配り-4 - yukicoder](https://yukicoder.me/submissions/543046)

```cpp
#include <iostream>
#include <numeric>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

using lint = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<lint> xs(n), ys(m);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    mint ans = 0;
    for (auto a : xs) {
        for (auto b : ys) {
            ans += a * b + a - b + std::gcd(a, b);
        }
    }

    std::cout << ans << "\n";
}
```

