---
title: "Codeforces Round #190 C - Ciel the Commander"
date: 2020-02-13
tags: [codeforces]
---

[Problem - 321C - Codeforces](https://codeforces.com/problemset/problem/321/C)

## 問題

木 $G = (V, E)$ が与えられる．以下を満たす各 $v \\in V$ への大文字アルファベットの割り付け $(a\_v)$ を求めよ．

- $a\_u = a\_v$ なる相異なる $u, v \\in V$ を任意に取る．
- パス $u, v$ 上にある頂点 $w$ が存在して， $a\_w \\lt a\_u$ ．

### 制約

- $2 \\leq |V| \\leq 10\^5$

## 考察

まず $A$ を割り当てる頂点は高々 1 つでなくてはならない．そこである $v \\in V$ を取って $a\_v = A$ としたとする．

すると，B が割り当てられる頂点対は $v$ を跨いでいればよい．これはすなわち， $G$ から $v$ を削除してできる森を考えたときに，異なる連結成分上に存在していればよい．逆に同じ連結成分上にあるとパスに $v$ が含まれないのでアウト．
よって各連結成分から $B$ を割り当てる頂点を 1 つずつ選べる．

以上から，以下を繰り返すことで割り当てを決められる．

1. 各連結成分から 1 つずつ頂点を選ぶ．選んだ頂点集合を $S$ とする．
2. 各 $v \\in S$ について， $a\_v$ にまだ割り当てられていないアルファベットを割り当てる．
3. $G$ から $S$ を削除する．

このループの回数が 26 回以内ならよい．

問題は各連結成分からどの頂点を選ぶかだが，削除後の連結成分のサイズを極力小さくすることを考えると， **重心** が良いことが分かる．実際，分解後の最大の連結成分のサイズは 1 ステップ毎に半分になるので， $2\^\{17\} \\gt |V|$ より上のループは 17 回以内で終わる．

## 実装例

実装はガチで重心分解をやるだけなので，重心分解の verify に使える．
今回は重心分解ライブラリも折りたたまずにそのまま載せておく．

[Submission #70939113 - Codeforces](https://codeforces.com/contest/321/submission/70939113)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

template <class Cost = int>
struct Centroid {
    Graph<Cost> graph;
    std::vector<bool> deleted;
    std::vector<int> sz;

    explicit Centroid(const Graph<Cost>& graph)
        : graph(graph), deleted(graph.size(), false), sz(graph.size()) {}

    // DFSで部分木のサイズを求める
    szdfs(int v, int p = -1) {
        sz[v] = 1;
        for (auto e : graph[v]) {
            if (e.dst == p || deleted[e.dst]) continue;
            sz[v] += szdfs(e.dst, v);
        }
        return sz[v];
    }

    int find(int v) {
        int n = szdfs(v);

        int p = -1;
        // 子の最大サイズがn/2以下になるまで，最大サイズの子に潜る
        while (true) {
            int nxt = -1;  // 最もサイズが大きい子
            for (auto e : graph[v]) {
                if (e.dst == p || deleted[e.dst]) continue;
                if (nxt == -1 || sz[e.dst] > sz[nxt]) nxt = e.dst;
            }

            if (nxt == -1 || sz[nxt] <= n / 2) return v;
            p = v;
            v = nxt;
        }
    }
};

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

    Centroid<> cent(graph);
    std::queue<std::pair<int, int>> cents;
    cents.emplace(0, 0);
    // 次に探す連結成分中の1頂点と，その深さ

    std::vector<int> ans(n);
    while (!cents.empty()) {
        int r, d;
        std::tie(r, d) = cents.front();
        cents.pop();

        // 重心に割り当てて削除
        r = cent.find(r);
        ans[r] = d;
        cent.deleted[r] = true;

        // 各子の頂点から1つずつcentに突っ込む
        for (auto e : graph[r]) {
            if (cent.deleted[e.dst]) continue;
            cents.emplace(e.dst, d + 1);
        }
    }

    for (auto a : ans) {
        std::cout << char(a + 'A') << " ";
    }
    std::cout << std::endl;
}
```

