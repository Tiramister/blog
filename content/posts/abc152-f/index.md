---
title: "AtCoder Beginner Contest 152 F - Tree and Constraints"
date: 2020-01-19
tags: [atcoder]
---

[F - Tree and Constraints](https://atcoder.jp/contests/abc152/tasks/abc152_f)

## 問題

$n$ 頂点の木が与えられる．この木の各辺を白か黒に塗る方法で，以下の $m$ 個の条件を全て満たすものの数を求めよ．

- $i$ 番目の条件は頂点 $u\_i, v\_i$ からなる．
- $u\_i$ と $v\_i$ を結ぶパス上に，少なくとも 1 つ黒い辺がなければならない．

### 制約

- $2 \\leq n \\leq 50$
- $1 \\leq m \\leq 20$

## 考察

条件 $i$ を満た **さない** 辺の塗り方の集合を $S\_i$ とすると，答えは $2\^\{n - 1\} - |\\cup S\_i|$ となる．というわけで包除原理を使うと，答えは

$$
2\^\{n - 1\} + \\sum\_\{T \\subseteq [n]\} (-1)\^\{|T|\} \\left| \\bigcap\_\{i \\in T\} S\_i \\right|
$$

となる．

$\\left| \\bigcap\_\{i \\in T\} S\_i \\right|$ を求めたい．
ある塗り方が「 $S\_i$ に属すること」と「 $u\_i$ と $v\_i$ を結ぶパス上の辺が全て白で塗られていること」が同値なので， $E\_\{u, v\}$ を「パス $u, v$ 上に含まれる辺の集合」とすると，

$$
\\left| \\bigcap\_\{i \\in T\} S\_i \\right| = 2\^\{(n - 1) - \\left| \\bigcup\_\{i \\in T\} E\_\{u, v\} \\right|\}
$$

となる(白で塗られることが確定した辺以外は自由に塗っていい)．これで $E\_\{u, v\}$ を前計算することで解が求められる．

$E\_\{u, v\}$ は DFS 等でそのまま求めてもよいが，経路復元等が必要で面倒．一方で $E\_v$ を「 $v$ から根までのパス上の辺の集合」とすると，

$$
E\_\{u, v\} = E\_u \\oplus E\_v
$$

となるので，辺集合を bit で管理するようにすれば，実装が楽だし計算量も落ちる(全点対調べる必要がないため)．

## 実装例

[提出 #9616745 - AtCoder Beginner Contest 152](https://atcoder.jp/contests/abc152/submissions/9616745)

```cpp
#include <iostream>
#include <vector>
#include <queue>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    Graph<> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].emplace_back(u, v);
        graph[v].emplace_back(v, u);
    }

    // BFSでn-1を根とする根付き木に変換
    // iから親に伸びる辺の番号をiとする
    std::vector<int> par(n, -1);
    std::vector<lint> paths(n, 0);

    std::queue<int> que;
    que.push(n - 1);
    par[n - 1] = n - 1;

    while (!que.empty()) {
        int v = que.front();
        que.pop();

        for (auto e : graph[v]) {
            int u = e.dst;
            if (par[u] >= 0) continue;
            par[u] = v;
            paths[u] = (paths[v] | (1LL << u));
            que.push(u);
        }
    }

    int m;
    std::cin >> m;

    std::vector<lint> ss(m);
    // ui-vi間の辺の集合
    for (auto& s : ss) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        s = (paths[u] ^ paths[v]);
    }

    // 包除原理
    lint ans = 0;
    for (int b = 0; b < (1 << m); ++b) {
        int sign = (__builtin_popcount(b) % 2 == 0 ? 1 : -1);

        lint s = 0;  // 白で塗る辺の集合
        for (int i = 0; i < m; ++i) {
            if ((b >> i) & 1) s |= ss[i];
        }

        int free = n - 1 - __builtin_popcountll(s);
        ans += sign * (1LL << free);
    }

    std::cout << ans << std::endl;
}
```

