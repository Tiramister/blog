---
title: AtCoder Grand Contest 047 C - Product Modulo
date: 2020-08-10
tags: [atcoder]
---

[C - Product Modulo](https://atcoder.jp/contests/agc047/tasks/agc047_c)

## 問題

$P = 2 \cdot 10^5 + 3$ (素数)とする。

$n$ 個の整数 $\\\{ a\_i \\\}$ が与えられる。 $\sum\_{i \\lt j} (a\_i a\_j \\bmod P)$ を求めよ。

### 制約

- $2 \leq n \leq 2 \cdot 10^5$
- $0 \leq a\_i \lt P$

## 考察

コンテスト中は $x \bmod P = x - \lfloor x / P \rfloor \cdot P$ を使うとずっと思っていたが違った。

以降 $a\_i = 0$ なる $i$ は無視して考える。

$g = 2$ は $P$ の原始根なので、任意の $1 \leq x \lt P$ に対して $g^k \equiv x$ なる $0 \leq k \leq P - 2$ が存在する。
そこで、 $g^{b\_i} = a\_i$ を満たす数列 $\\\{ b\_i \\\}$ を考える。すると、 $a\_i a\_j \equiv g^{b\_i + b\_j}$ となり、「 $\\\{a\_i\\\}$ 同士の掛け算」が「 $\\\{b\_i\\\}$ 同士の足し算」に変わる。よって各 $0 \leq k \leq 2(P - 2)$ について $b\_i + b\_j = k$ なる $i \lt j$ を数え上げればよく、これは FFT によって $\Theta(P \log P)$ でできる。

## 実装例

[提出 #15794827 - AtCoder Grand Contest 047](https://atcoder.jp/contests/agc047/submissions/15794827)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>

template <int MOD>
struct ModInt { ... };

template <int K>
struct FastFourierTransform { ... };

constexpr int MOD = 200003;
using mint = ModInt<MOD>;
const FastFourierTransform<20> FFT;

using lint = long long;

void solve() {
    // g^log[x] = x
    std::vector<int> log(MOD);
    mint g = 2;
    for (int i = 0; i < MOD - 1; ++i) {
        log[g.pow(i).val] = i;
    }

    std::vector<lint> cnt(MOD - 1, 0);

    int n;
    std::cin >> n;
    while (n--) {
        int a;
        std::cin >> a;
        if (a != 0) ++cnt[log[a]];
    }

    // FFTで畳み込む
    auto res = FFT.fft(cnt, cnt);

    lint ans = 0;
    for (int i = 0; i < (int)res.size(); ++i) {
        lint num = llround(res[i]);
        ans += g.pow(i).val * num;
    }

    // a_i * a_iを省く
    for (int i = 0; i < (int)cnt.size(); ++i) {
        lint num = llround(cnt[i]);
        ans -= g.pow(i * 2).val * num;
    }

    // i > jを省く
    ans /= 2;

    std::cout << ans << "\n";
}
```

