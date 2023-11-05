---
title: "Educational Codeforces Round 39 - Fibonacci String Subsequences"
date: 2020-01-07
tags: [codeforces]
---

[Problem - F - Codeforces](https://codeforces.com/contest/946/problem/F)

## 問題

長さ $n$ の文字列 $s$ が与えられる．

文字列 $t$ のコストを，「 $t$ 中に $s$ が連続部分文字列として現れる箇所の個数」と定義する．

また，整数 $k$ に対して文字列 $F(k)$ を以下のように定義する．

- $F(0) = 0$
- $F(1) = 1$
- $F(k) = F(k - 1) + F(k - 2) \\quad (k \\geq 2)$
- $+$ は文字列の結合

与えられた $x$ に対して， $F(x)$ の全ての部分文字列のコストの総和を求めよ．

### 制約

- $1 \\leq n \\leq 100$
- $0 \\leq x \\leq 100$

## 考察

$F(k)$ の長さを $m\_k$ ，全ての部分文字列のコストを $c\_k$ とおく．
$F(k) = F(k - 1) + F(k - 2)$ から， $F(k)$ の部分文字列中に現れる $s$ は大きく以下の 3 つに分けられる．

1.  $F(k - 1)$ からの文字のみを使うもの．
2.  $F(k - 2)$ からの文字のみを使うもの．
3.  $F(k - 1), F(k - 2)$ 両方の文字を使うもの．

$F(k - 1)$ からの各選び方について， $F(k - 2)$ からの選び方は $2\^\{m\_\{k - 2\}\}$ 通りある．よって 1 による寄与は $c\_\{k - 1\} \\cdot 2\^\{m\_\{k - 2\}\}$ となる．同様に，2 による寄与は $c\_\{k - 2\} \\cdot 2\^\{m\_\{k - 1\}\}$ ．

残るは 3 つ目だが，これは以下の値を計算することで $O(n)$ で求められる．

- $p\_\{k, l, r\}$ : $F(k)$ の部分文字列で，その接頭辞が $s[l, r)$ と一致するものの個数．
- $s\_\{k, l, r\}$ : 上の接尾辞版．

$F(k - 1)$ から $i$ 文字来るような連続部分文字列の寄与は $p\_\{k - 1, 0, i\} \\cdot s\_\{k - 2, i, n\}$ で求まるので，これを $i = 1, \\cdots, n - 1$ について足し合わせれば良い．

後は $p, s$ を十分高速に更新できればよいが，これは以下の値も計算しておくことで各要素を $O(n)$ で更新できる．

- $a\_\{k, l, r\}$ : $F(k)$ の部分文字列で， $s[l, r)$ と一致するものの個数．

更新式は区間最大和をセグ木に載せるやつと同じ要領で立つ．詳しく知りたい人は実装例をどうぞ．

## 実装例

[Submission #68360775 - Codeforces](https://codeforces.com/contest/946/submission/68360775)

```cpp
#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

int main() {
    int n, x;
    std::string t;
    std::cin >> n >> x >> t;

    auto sdp = vec(x + 2, vec(n + 1, vec(n + 1, mint(0))));
    auto pdp = sdp, adp = sdp;
    auto cnts = vec(x + 2, mint(0));    // 解
    auto lenpow = vec(x + 2, mint(0));  // 2^|F(k)|

    // 初期化
    for (int k = 0; k < 2; ++k) {
        std::string s(1, '0' + k);  // F(k)

        for (int l = 0; l <= n; ++l) {
            // 空文字列
            sdp[k][l][l] = 2;
            pdp[k][l][l] = 2;
            adp[k][l][l] = 1;

            if (s == t.substr(l, 1)) {
                sdp[k][l][l + 1] = 1;
                pdp[k][l][l + 1] = 1;
                adp[k][l][l + 1] = 1;
            }
        }
        cnts[k] = adp[k][0][n];
        lenpow[k] = 2;
    }

    for (int k = 2; k <= x; ++k) {
        lenpow[k] = lenpow[k - 1] * lenpow[k - 2];

        for (int l = 0; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                pdp[k][l][r] = 0;
                sdp[k][l][r] = 0;
                adp[k][l][r] = 0;

                for (int i = l; i <= r; ++i) {
                    // F(k-1)から[l, i)を貰う
                    pdp[k][l][r] += (i == r ? pdp : adp)[k - 1][l][i] * pdp[k - 2][i][r];
                    sdp[k][l][r] += sdp[k - 1][l][i] * (i == l ? sdp : adp)[k - 2][i][r];
                    adp[k][l][r] += adp[k - 1][l][i] * adp[k - 2][i][r];
                }
            }
        }

        // 解の更新
        cnts[k] = cnts[k - 1] * lenpow[k - 2] + cnts[k - 2] * lenpow[k - 1];
        for (int i = 1; i < n; ++i) {
            cnts[k] += sdp[k - 1][0][i] * pdp[k - 2][i][n];
        }
    }

    std::cout << cnts[x] << std::endl;
    return 0;
}
```

