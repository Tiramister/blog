---
title: "Educational Codeforces Round 36 F - Imbalance Value of a Tree"
date: 2020-09-11
tags: [codeforces]
---

[Problem - F - Codeforces](https://codeforces.com/contest/915/problem/F)

## 問題

$n$ 頂点の木が与えられる。また頂点 $i$ には整数 $a\_i$ が書かれている。

$I(x, y)$ を「 $xy$ パス上の頂点の中での、 $a\_i$ の最大値と最小値の差」と定める。
$\\sum\_\{x=1\}\^\{n\} \\sum\_\{y=x\}\^\{n\} I(x, y)$ を求めよ。

### 制約

- $1 \\leq n \\leq 10\^6$
- $1 \\leq a\_i \\leq 10\^6$

## 考察

まず $\\sum\_\{x=1\}\^\{n\} \\sum\_\{y=x\}\^\{n\} I(x, y)$ の代わりに $\\sum\_\{x=1\}\^\{n\} \\sum\_\{y=1\}\^\{n\} I(x, y)$ を求めることにする。 $I(x,x)=0$ なので、これは答えの 2 倍となる。

そして「最大値と最小値の差の和」を「最大値の和と最小値の和の差」と分解する。
すると各 $v \\in V$ について「 $xy$ パス上で $a\_\{v\}$ が最大となるような $x, y \\in V$ がいくつあるか」を高速に数えられればよい。

グラフが最初空の状態から、 $v$ を $a\_v$ について昇順にグラフに加えていくことを考える。
すると、「 $xy$ パス上で $a\_\{v\}$ が最大となる」というのは「 $xy$ パスが $v$ を通り、 $v$ を加えた時点で $x, y$ が連結である」と同値となる。そのような $x, y$ の個数は以下の式で求まる。

$$
s\_v\^2 - \\sum\_\{u \\in \\Gamma(v)\} s\_u\'\^2
$$

ここで

- $s\_v$ は $v$ を加えた直後での、 $v$ を含む連結成分のサイズ
- $s\_u\'$ は $v$ を加える直前での、 $u$ を含む連結成分のサイズ
- $\\Gamma(v)$ は $v$ と隣接する頂点の集合

である。第 1 項で「 $v$ を加えた時点で $x, y$ が連結である」ものの個数を数え、第 2 項で「 $xy$ パスが $v$ を通らない」ものの個数を引いている。

そして $s\_v$ の計算・更新は UnionFind を使えば十分高速に行える。

## 実装例

「最小値の和を引く」というのは「 $a\_i$ の符号を反転させて、最大値の和を足す」で実現できる。
こうすることで、2 回の単純なループで実装できる。

[Submission #92350304 - Codeforces](https://codeforces.com/contest/915/submission/92350304)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

struct UnionFind { ... };

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    Graph<> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.span(false, --u, --v);
    }

    lint ans = 0;

    std::vector<int> vs(n);
    std::iota(vs.begin(), vs.end(), 0);

    for (int q = 0; q < 2; ++q) {
        // vをx_vについて昇順に並べる
        std::sort(vs.begin(), vs.end(),
                  [&](int u, int v) { return xs[u] < xs[v]; });

        UnionFind uf(n);
        std::vector<bool> visited(n, false);

        for (auto v : vs) {
            visited[v] = true;

            lint c2sum = 0;
            for (auto e : graph[v]) {
                int u = e.dst;
                if (!visited[u]) continue;

                lint sz = uf.size(u);
                c2sum += sz * sz;

                uf.unite(u, v);
            }

            lint sz = uf.size(v);
            ans += (sz * sz - c2sum) * xs[v];
        }

        for (auto& x : xs) x = -x;
    }

    std::cout << ans / 2 << "\n";
}
```

