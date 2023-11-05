---
title: "第 6 回 ドワンゴからの挑戦状 本選 B - Harvest Festival"
date: 2020-02-09
tags: [atcoder]
---

[B - Harvest Festival](https://atcoder.jp/contests/dwacon6th-final/tasks/dwacon6th_final_b)

## 問題

$n$ 頂点 $m$ 辺の単純無向重み付きグラフが与えられる．辺 $i$ の重みは $d\_i$ ．
さらに，頂点集合の部分集合 $W \\subseteq V$ が与えられる．

$S \\subseteq V$ に対して， $f(S)$ を「 $W$ のうち， $S$ の任意の頂点からの距離が $l$ 以内である頂点の集合」と定める．より形式的には，以下のように定める．

$$
f(S) = \\\{ w \\in W \\mid \\forall v \\in S, \\; d(v, w) \\leq l \\\}
$$

各 $T \\subseteq W$ について， $f(S) = T$ なる $\\emptyset \\neq S \\subseteq V$ の個数を求めよ[^output]．

[^output]: 実際は $\\bmod 998,244,353$ を取ったものの XOR を出力する．

### 制約

- $1 \\leq n \\leq 10\^5$
- $0 \\leq m \\leq 2 \\times 10\^5$
- $1 \\leq |W| (= k) \\leq 20$
- $1 \\leq l, d\_i \\leq 10\^9$

## 考察

まず各 $w \\in W$ について，そこから距離 $l$ 以内の頂点集合を $U\_w$ とする．これは Dijkstra 法により $O(k (n + m) \\log m)$ で求まる．

これを拡張して， $T \\subseteq W$ について， $U\_T = \\bigcap\_\{w \\in T\} U\_w$ と定める．
つまり $U\_T$ は「 $T$ の任意の頂点から距離 $l$ 以内の頂点集合」である．

すると，任意の $S \\subseteq U\_T$ について $f(S) \\supseteq T$ が成り立つ．しかしこれは「ぴったり」，つまり $f(S) = T$ になっていない．
それでもこれは **メビウス変換** によって「ぴったり」にできる．

具体的には， $f(S) \\supseteq T$ を満たすものから $f(S) \\supsetneq T$ を満たすものを抜けばいい．
言い換えると， $U\_T$ から各 $T\' \\supsetneq T$ について $U\_\{T\'\}$ を抜けばいい．
よって $|U\_T|$ さえ求まっていれば， **高速メビウス変換** によって $O(k 2\^k)$ で解が求まる．

$|U\_T|$ を求めるアルゴリズムとして，「各 $v \\in V$ について $X\_v = \\\{ w \\subseteq W \\mid d(v, w) \\leq l \\\}$ を求め，各 $T \\subseteq X\_v$ に対して $|U\_T|$ を増やす」という方法を考える．
そのままでは $O(n 2\^k)$ で間に合わないのだが，

- 各 $v \\in V$ について $|U\_\{X\_v\}|$ を 1 増やす．
- これに対して(上位集合の) **高速ゼータ変換** を行う．

とすることで $O(nk + k 2\^k)$ に落ちて間に合う．

## 実装例

[提出 #9964494 - 第6回 ドワンゴからの挑戦状 本選](https://atcoder.jp/contests/dwacon6th-final/submissions/9964494)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

using lint = long long;

// modint
template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;


// graph
template <class Cost = int>
struct Edge { .. };

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

// dijkstra
template <class T>
using MaxHeap = std::priority_queue<T>;
template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr lint INF = std::numeric_limits<lint>::max();

template <class Cost>
std::vector<Cost> dijkstra(const Graph<Cost>& graph, int s) { ... }

// main
void solve() {
    int n, m, k;
    lint l;
    std::cin >> n >> m >> k >> l;

    std::vector<int> ws(k);
    for (auto& w : ws) std::cin >> w;

    Graph<lint> graph(n);
    while (m--) {
        int u, v;
        lint d;
        std::cin >> u >> v >> d;
        graph[u].emplace_back(u, v, d);
        graph[v].emplace_back(v, u, d);
    }

    std::vector<std::vector<lint>> dist(k);
    for (int i = 0; i < k; ++i) dist[i] = dijkstra(graph, ws[i]);

    std::vector<int> cnt(1 << k, 0);
    // cnt[T] = T中の全ての街から距離l以内の街の数
    for (int v = 0; v < n; ++v) {
        int b = 0;
        for (int i = 0; i < k; ++i) {
            if (dist[i][v] <= l) b |= (1 << i);
        }
        ++cnt[b];
    }

    // 上位集合に対する高速ゼータ変換
    for (int i = 0; i < k; ++i) {
        for (int b = (1 << k) - 1; b >= 0; --b) {
            if ((b >> i) & 1) {
                cnt[b ^ (1 << i)] += cnt[b];
            }
        }
    }

    std::vector<mint> xs(1 << k);
    for (int b = 0; b < (1 << k); ++b) {
        // 選ばられるべきは，cnt[T]個の頂点集合の部分集合で空でないもの
        xs[b] = (mint(2).pow(cnt[b])).val - 1;
    }

    // 上位集合に対する高速メビウス変換
    for (int i = 0; i < k; ++i) {
        for (int b = 0; b < (1 << k) - 1; ++b) {
            if (((b >> i) & 1) == 0) {
                xs[b] -= xs[b | (1 << i)];
            }
        }
    }

    int ans = 0;
    for (int b = 0; b < (1 << k); ++b) {
        ans ^= xs[b].val;
    }

    std::cout << ans << std::endl;
}
```

