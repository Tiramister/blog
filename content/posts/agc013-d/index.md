---
title: "AtCoder Grand Contest 013 D - Piling Up"
date: 2019-10-27
tags: [atcoder]
---

[D - Piling Up](https://atcoder.jp/contests/agc013/tasks/agc013_d)

## 問題

最初，箱に赤玉と青玉が合わせて $n$ 個入っている．
この箱を使って，以下の操作を $m$ 回行うことで長さ $2m$ の玉の列を作る．

- 箱から 1 つ玉を取り出し，列の末尾に加える．
- 赤玉と青玉を 1 つずつ箱に入れる．
- 箱から 1 つ玉を取り出し，列の末尾に加える．

こうしてできる列として考えうるものが何通りあるか求めよ．

### 制約

- $1 \\leq n \\leq 3,000$
- $1 \\leq m \\leq 3,000$

## 考察

余事象を取って，考えられない列の数を数えることにする．

一番最初に矛盾が起こるのが $i$ 番目の赤玉であったとする．
対称性から青玉のものも同数だけあるので，最後に 2 倍すればいい．

これは，以下の条件が全て成り立つことと同値である．

- $i$ 番目の玉を置こうとした時点で，箱の中に赤玉がない．
- 途中で箱の中から青玉がなくなっている瞬間がある．

2 つの条件が重要で，そうでなければ最初に入っている青玉を 1 つ赤玉に変えられることから従う[^1]．

[^1]: 最初から全て赤玉なら，「最初」が青玉がなくなっている瞬間であることに注意．

そこで，最初に入っている赤玉の数(以降「初期状態」とする)を固定してしまえば

- 各操作の後に箱に入っている赤玉の数
- 過去に青玉がなくなった瞬間があるか

を状態とする DP によって，「その初期状態にて」矛盾する列の数を数え上げることができる．

さらに重要な事実として，初期状態によって分類することで，矛盾する列全体の集合は **排反に** 分割できる．
これは，1 つの矛盾する列に対して，他の初期状態では

- 途中で青玉の数が負になっている
- 矛盾している点にて過去に青玉がなくなっていない

の一方が成り立つことから従う．

よって全ての初期状態に対して上の DP を行えばいいのだが，DP 自体の計算量が $\\Theta(N M)$ なので間に合わない．

そこで先に述べた排反性を利用すると，全ての初期状態の和を取った状態から DP をすることで，全初期状態の DP を並列に行うことができる．
これで全体の計算量が $\\Theta(NM)$ に落ちる．

## 実装例

[提出 #8136410 - AtCoder Grand Contest 013](https://atcoder.jp/contests/agc013/submissions/8136410)

```cpp
#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T, class Int>
T ipow(T b, Int n) { ... }

int main() {
    int n, m;
    std::cin >> n >> m;
    mint ans = ipow(mint(2), m * 2);
    mint out = 0;

    std::vector<std::vector<mint>>
        dp(2, std::vector<mint>(n + 1, 0)),
        ndp(2, std::vector<mint>(n + 1));
    // 途中で青が0になったか, 赤の個数

    // 初期状態の和
    for (int r = 0; r <= n; ++r) {
        dp[r == n][r] = 1;
    }

    for (int i = 0; i < m; ++i) {
        out += dp[true][0] * ipow(mint(2), (m - i) * 2 - 1);
        // 矛盾した後は自由に並べられるので，後ろの係数がつく

        for (auto& v : ndp) {
            std::fill(v.begin(), v.end(), 0);
        }

        for (int b = 0; b < 2; ++b) {
            for (int r = 0; r <= n; ++r) {
                if (r > 0) {
                    // RB
                    ndp[b][r] += dp[b][r];
                    // RR
                    ndp[b][r - 1] += dp[b][r];
                }
                if (r < n) {
                    // 操作中に青玉が0になるかどうか
                    bool nb = b || (r == n - 1);
                    // BR
                    ndp[nb][r] += dp[b][r];
                    // BB
                    ndp[nb][r + 1] += dp[b][r];
                }
            }
        }
        std::swap(dp, ndp);
    }

    std::cout << ans - out * 2 << std::endl;
    return 0;
}
```

