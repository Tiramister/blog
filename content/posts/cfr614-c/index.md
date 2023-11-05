---
title: "Codeforces Round 614 C - Xenon's Attack on the Gangs"
date: 2020-01-30
tags: [codeforces]
---

[Problem - C - Codeforces](https://codeforces.com/contest/1292/problem/C)

## 問題

$n$ 頂点の木が与えられる．各頂点には番号 $1, \\cdots, n$ が割り当てられている．

今からこの木の各辺に $0, \\cdots, n - 2$ の重みを互いに異なるように割り当てる．そして割り当て $c$ に対するスコアを，2 点 $u, v$ を結ぶパスからなる辺集合を $P\_\{uv\}$ としたときに

$$
\\sum\_\{1 \\leq u \\lt v \\leq n\} \\text\{mex\} (\\\{ c(e) \\mid e \\in P\_\{uv\} \\\})
$$

と定める．ここで $\\text\{mex\}(S)$ は $S$ に属さない最小の非負整数とする．

スコアの最大値を求めよ．

### 制約

- $2 \\leq n \\leq 3 \\times 10\^3$

## 考察

まずスコアについて本質的なのは， $0, \\cdots, k-1$ からなるパスである．この両端を $u, v$ とすると， $u, v$ を根とする部分木からそれぞれ頂点を 1 つずつ取ってきたとき，それに対する mex は $k$ 以上になる．逆にそれ以外の点対に対する mex は $k$ 以上たり得ない．
ここから，連続した重みが割り当てられたパスの両端を伸ばしていく割り当て方が最善と分かる．

$u, v$ がパスの両端である場合を考える．辺 $uw$ に新たな重みを割り当てるとき，この辺によるスコアの寄与は $w$ の部分木のサイズと $v$ の部分木のサイズの積となる．よって $dp\_\{u, v\} =$ 「 $u, v$ がパスの両端であるとき，それ以降の寄与の和の最大値」とすると，これは $u, v$ の各子に対して再帰的に計算することで埋めることができる．

ここで問題となるのは，「部分木のサイズが現在のパスに依存する」ということ．しかし部分木のサイズは $0$ を割り当てる辺(これを根とする)にのみ依存するので，全方位木 DP で部分木のサイズを更新しながら，全ての辺についてそれを根とした場合のスコアを計算すればよい．

なお $dp$ は全ての根について共通で使えることに注意(それ以降の部分木のサイズは両端について一意なため)．ここから全体の計算量は $O(n\^2)$ となる．

## 実装例

[Submission #69795958 - Codeforces](https://codeforces.com/contest/1292/submission/69795958)

```cpp
#include <iostream>
#include <vector>

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

template <class T>
std::vector<T> vec(int len, T elem) { ... }

using lint = long long;

std::vector<std::vector<lint>> dp;
Graph<> tree;
std::vector<lint> sz;

// calculate the size of subtrees
lint szdfs(int v, int p) {
    sz[v] = 1;
    for (auto e : tree[v]) {
        if (e.dst == p) continue;
        sz[v] += szdfs(e.dst, v);
    }
    return sz[v];
}

// the ends of the current path is u and v
// each root is ru and rv
lint dfs(int u, int v, int ru, int rv) {
    if (dp[u][v] >= 0) return dp[u][v];

    auto& ret = dp[u][v];
    ret = 0;
    for (auto e : tree[u]) {
        if (e.dst == v || e.dst == rv || sz[e.dst] > sz[u]) continue;
        ret = std::max(ret, sz[e.dst] * sz[v] + dfs(e.dst, v, ru, rv));
    }
    for (auto e : tree[v]) {
        if (e.dst == u || e.dst == ru || sz[e.dst] > sz[v]) continue;
        ret = std::max(ret, sz[u] * sz[e.dst] + dfs(u, e.dst, ru, rv));
    }
    return ret;
}

lint calc(int v, int p) {
    lint ret = 0;
    for (auto e : tree[v]) {
        if (e.dst == p) continue;

        // remove subtree of e.dst
        sz[v] -= sz[e.dst];
        ret = std::max(ret, sz[v] * sz[e.dst] + dfs(v, e.dst, v, e.dst));

        // move to e.dst
        lint psz = sz[e.dst];
        sz[e.dst] = tree.size();
        ret = std::max(ret, calc(e.dst, v));

        // revert size
        sz[e.dst] = psz;
        sz[v] += sz[e.dst];
    }
    return ret;
}

void solve() {
    int n;
    std::cin >> n;

    tree = Graph<>(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        tree[u].emplace_back(u, v);
        tree[v].emplace_back(v, u);
    }

    sz.resize(n);
    szdfs(0, -1);

    dp = vec(n, vec(n, -1LL));
    std::cout << calc(0, -1) << std::endl;
}
```

