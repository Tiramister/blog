---
title: "第一回日本最強プログラマー学生選手権決勝 F - Count Permutations Many Times"
date: 2020-10-22
tags: [atcoder]
---

[F - Count Permutations Many Times](https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_f)

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

[提出 #17569521 - 第一回日本最強プログラマー学生選手権決勝](https://atcoder.jp/contests/jsc2019-final/submissions/17569521)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <atcoder/modint>

constexpr int M = 45;

namespace ac = atcoder;
using mint = ac::modint998244353;

// *(1 + ax)
void mul(std::vector<mint>& f, mint a) {
    if (a == 0) return;

    f.push_back(0);
    for (int i = (int)f.size() - 1; i > 0; --i) {
        f[i] += f[i - 1] * a;
    }
}

// /(1 + ax)
void div(std::vector<mint>& f, mint a) {
    if (a == 0) return;

    for (int i = 1; i < (int)f.size(); ++i) {
        f[i] -= f[i - 1] * a;
    }
    f.pop_back();
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    // 階乗の前計算
    std::vector<mint> facts(n + 1, 1);
    for (int i = 2; i <= n; ++i) facts[i] = facts[i - 1] * i;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;

    std::vector<std::pair<int, int>> ps(q);
    for (auto& [l, r] : ps) std::cin >> l >> r;

    // Mo's algorithm: クエリを並び替える
    std::vector<int> idxs(q);
    std::iota(idxs.begin(), idxs.end(), 0);
    std::sort(idxs.begin(), idxs.end(),
              [&](auto i, auto j) {
                  auto [li, ri] = ps[i];
                  auto [lj, rj] = ps[j];

                  if (li / M == lj / M) {
                      return ri < rj;
                  } else {
                      return li < lj;
                  }
              });

    int l = 0, r = 0;
    std::vector<mint> f{1};
    std::vector<int> cnt(n, 0);

    std::vector<mint> ans(q, 0);
    for (auto i : idxs) {
        auto [nl, nr] = ps[i];

        // extend
        while (nl < l) {
            --l;
            div(f, cnt[xs[l]]);
            ++cnt[xs[l]];
            mul(f, cnt[xs[l]]);
        }
        while (r < nr) {
            div(f, cnt[xs[r]]);
            ++cnt[xs[r]];
            mul(f, cnt[xs[r]]);
            ++r;
        }

        // shrink
        while (l < nl) {
            div(f, cnt[xs[l]]);
            --cnt[xs[l]];
            mul(f, cnt[xs[l]]);
            ++l;
        }
        while (nr < r) {
            --r;
            div(f, cnt[xs[r]]);
            --cnt[xs[r]];
            mul(f, cnt[xs[r]]);
        }

        for (int k = 0; k < (int)f.size(); ++k) {
            ans[i] += f[k] * facts[n - k] * mint(-1).pow(k);
        }
    }

    for (auto a : ans) std::cout << a.val() << "\n";
}
```

