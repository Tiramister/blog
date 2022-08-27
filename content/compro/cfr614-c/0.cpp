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
