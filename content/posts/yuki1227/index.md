---
title: "yukicoder No.1227 - I hate ThREE"
date: 2020-09-11
tags: [yukicoder]
---

[No.1227 I hate ThREE - yukicoder](https://yukicoder.me/problems/no/1227)

## 問題

$n$ 頂点の木がある。 $1$ 以上 $k$ 以下の整数からなる長さ $n$ の数列 $(p\_i)$ で、以下を満たすものの個数を求めよ。

- 全ての辺 $uv$ について、 $|p\_u - p\_v| = 3$ 。

### 制約

- $1 \\leq n \\leq 10\^3$
- $4 \\leq k \\leq 10\^9$

## 考察

まず素朴な解法として、その頂点に割り振られた値を持つ木 DP によって $O(nk)$ で解ける。しかし $k$ がかなり大きい場合、これでは間に合わない。

しかしよく考えてみると、根の値が $3n-2$ 以上である場合、 $p\_v \\leq 0$ なる $v$ が存在するように割り振ることはできない。というのも、根から最も遠い頂点までの距離は高々 $n-1$ だからである。
同様に、根の値が $k-3n+3$ 以下である場合、 $p\_v \\gt k$ なる $v$ が存在するように割り振ることはできない。

したがって根の値が $3n-3$ 以上 $k-3n+2$ 以下の場合、全ての割り当て $2\^\{n-1\}$ 通りが条件を満たす。根の値が $3n-2$ 以下の場合、頂点の値として考えられるのは $6n-5$ 以下なので、DP 配列の長さをこれに制限して DP すれば $\\Theta(n\^2)$ で解が求まる。 $k-3n+3$ 以上も同様。

## 実装例

[#551995 (C++17) No.1227 I hate ThREE - yukicoder](https://yukicoder.me/submissions/551995)

```cpp
#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

Graph<> graph;
int sz;

std::vector<mint> dfs(int v, int p) {
    std::vector<mint> dp(sz, 1);

    for (auto e : graph[v]) {
        int u = e.dst;
        if (u == p) continue;

        auto cdp = dfs(u, v);
        for (int i = 0; i < sz; ++i) {
            // 子と根の差分が3の場合を掛け合わせる
            mint sum = 0;
            for (int j : {-3, 3}) {
                int ni = i + j;
                if (ni < 0 || sz <= ni) continue;
                sum += cdp[ni];
            }
            dp[i] *= sum;
        }
    }

    return dp;
}

void solve() {
    int n, k;
    std::cin >> n >> k;

    graph = Graph<>(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.span(false, --u, --v);
    }

    mint ans = 0;
    if (k < 6000) {
        // 小さい場合は普通にDP
        sz = k;
        auto dp = dfs(0, -1);
        for (int i = 0; i < k; ++i) ans += dp[i];

    } else {
        sz = 6000;
        auto dp = dfs(0, -1);

        for (int i = 0; i < 3000; ++i) ans += dp[i];
        ans *= 2;  // 上と下の分

        // 中央の分
        ans += mint(2).pow(graph.size() - 1) * (k - 6000);
    }

    std::cout << ans << "\n";
}
```

