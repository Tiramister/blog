---
title: "yukicoder No.1240 - Or Sum of Xor Pair"
date: 2020-09-26
tags: [yukicoder]
---

[No.1240 Or Sum of Xor Pair - yukicoder](https://yukicoder.me/problems/no/1240)

## 問題

長さ $N$ の整数列 $(A\_i)$ と整数 $X$ が与えられる。

$0 \\leq i \\lt j \\lt N$ かつ $A\_i \\oplus A\_j \\lt X$ なる全ての $(i, j)$ について、 $A\_i \\lor A\_j$ の総和を求めよ。

ここで $\\lor, \\oplus$ はそれぞれ bitwise or, bitwise xor を表す。

### 制約

- $2 \\leq N \\leq 2 \\cdot 10\^5$
- $1 \\leq X \\lt 2\^\{18\} (=M)$
- $0 \\leq A\_i \\lt M$

## 考察

桁毎に考える、つまり

- $0 \\leq i \\lt j \\lt N$
- $A\_i \\oplus A\_j \\lt X$
- $A\_i \\lor A\_j$ の $k$ 桁目が $1$

を満たす $(i, j)$ の個数を各 $k$ について求める。

ここで $A\_i \\lor A\_j$ の $k$ 桁目が $1$ である $(i, j)$ の個数は、「全体」から「 $A\_i, A\_j$ の $k$ 桁目が共に $0$ であるものの個数」を引いたものとなる。
よって $k$ 桁目が $0$ であるような $A\_i$ のみを取り出せば、後者も前者と同じように数えられる。

後は

- $0 \\leq i \\lt j \\lt N$
- $A\_i \\oplus A\_j \\lt X$

を満たす $(i, j)$ の個数を求めればよいが、これは俗に「xor 畳み込み」と呼ばれるテクニックによって $\\Theta(N + M \\log M)$ で数え上げられる。
具体的なアルゴリズムは [こちら](https://kazuma8128.hatenablog.com/entry/2018/05/31/144519) を参照。

## 実装例

$i = j$ や $i \\gt j$ なる $(i, j)$ の省き方に注意。
$i = j$ のとき $A\_i \\oplus A\_j = 0$ であることを利用すると簡単に省ける。

[#559055 (C++17) No.1240 Or Sum of Xor Pair - yukicoder](https://yukicoder.me/submissions/559055)

```cpp
#include <iostream>
#include <numeric>
#include <vector>

using lint = long long;
constexpr int K = 18;

// 自身とのxor畳み込み
void xor_convolution(std::vector<lint>& xs) {
    for (int i = 1; i < (1 << K); i <<= 1) {
        for (int b = 0; b < (1 << K); ++b) {
            if (b & i) continue;
            auto l = xs[b],
                 r = xs[b | i];
            xs[b] = l + r;
            xs[b | i] = l - r;
        }
    }

    for (auto& x : xs) x *= x;

    for (int i = 1; i < (1 << K); i <<= 1) {
        for (int b = 0; b < (1 << K); ++b) {
            if (b & i) continue;
            auto l = xs[b],
                 r = xs[b | i];
            xs[b] = l + r;
            xs[b | i] = l - r;
        }
    }

    for (auto& x : xs) x >>= K;
}

void solve() {
    int n, a;
    std::cin >> n >> a;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;

    lint tot;  // 全体の個数
    {
        int sz = 0;
        std::vector<lint> cnt(1 << K, 0);
        for (auto x : xs) {
            ++cnt[x];
            ++sz;
        }

        xor_convolution(cnt);
        cnt[0] -= sz;                 // 0にi=jなるものが含まれることに注意
        for (auto& c : cnt) c >>= 1;  // i>jを除外
        tot = std::accumulate(cnt.begin(), cnt.begin() + a, 0LL);
    }

    lint ans = 0;
    for (int k = 1; k < (1 << K); k <<= 1) {
        // lg(k)桁目が0であるもののみの個数
        lint num;

        {
            int sz = 0;
            std::vector<lint> cnt(1 << K, 0);
            for (auto x : xs) {
                if (x & k) continue;
                ++cnt[x];
                ++sz;
            }

            xor_convolution(cnt);
            cnt[0] -= sz;
            for (auto& c : cnt) c >>= 1;
            num = std::accumulate(cnt.begin(), cnt.begin() + a, 0LL);
        }

        ans += k * (tot - num);
    }

    std::cout << ans << "\n";
}
```

