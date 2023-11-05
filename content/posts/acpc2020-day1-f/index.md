---
title: "ACPC 2020 day1 F - コマの配置"
date: 2020-09-20
tags: [voluntary]
---

[3198 < VPC TUATPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/TUATPC/3198)

## 問題

$N \\times N$ のグリッドがある。最初、そのうち $M$ マスが白マスで、それ以外が黒マスになっている。

グリッドに対して $Q$ 回の変更が行われる。各変更では 1 つのマスが指定され、そのマスの色を白黒反転させる。

各変更直後について、白マスに $N$ 個のコマを置くことで、各行・各列にコマがちょうど 1 つずつ置かれているようにできるか判定せよ。

### 制約

- $1 \\leq N, M, Q \\leq 5 \\cdot 10\^3$

## 考察

### マッチングへの帰着

まず各行・列に対応する頂点を $N$ 個ずつ用意し、各白マス $(r, c)$ について、行側の頂点 $r$ と列側の頂点 $c$ を繋ぐ辺を張る。
するとこのグラフは $2N$ 頂点 $M$ 辺の二部グラフとなり、「コマの置き方」が「辺の選び方」と対応する。

そして問題文中の判定問題をこのグラフ上で解釈すると、「サイズ $N$ のマッチングが存在するか？」となる。
二部グラフの最大マッチングは、蟻本 P.195 や [この記事](https://qiita.com/drken/items/e805e3f514acceb87602#%E6%9C%80%E5%A4%A7%E4%BA%8C%E9%83%A8%E3%83%9E%E3%83%83%E3%83%81%E3%83%B3%E3%82%B0%E5%95%8F%E9%A1%8C%E3%82%92%E6%9C%80%E5%A4%A7%E6%B5%81%E5%95%8F%E9%A1%8C%E3%81%AB%E5%B8%B0%E7%9D%80%E3%81%99%E3%82%8B) で述べられているように、最大流問題に帰着することで解くことができる。

### 高速化

しかし毎回愚直に最大流を求めていると間に合わない。
例えば Ford-Fulkerson のアルゴリズムでは、流量の最大値が $N$ なので、計算量は各クエリ $O(N(N+M+Q))$ となる(他のアルゴリズムでもほとんど同様)。

だがよく考えると、**一度のクエリで最大流は高々 1 しか増減しない**。
よって、前に流したフローをそのまま保持しておき、新たに流れたフローだけを求めることで、各クエリ $O(N+M+Q)$ で処理できる。

### 辺の削除

上の解法では、クエリ毎に辺の追加・削除を行う必要がある。追加は簡単だが、削除は少し考える必要がある。

まず消したい辺にフローが流れていない場合。この場合はその辺の容量を 0 にするだけでよい。

問題なのは消したい辺にフローが流れている場合で、この場合はこの辺を通るフローを消す必要がある。
今回は 2 部グラフなので、消したい辺が $uv$ である場合、このフローは常に $s \\to u \\to v \\to g$ という形になっている[^flow]。よって辺 $su, uv, vg$ の流量を 0 にすればよい。

[^flow]: もしもっと長い形をしている場合、流量を増やすことができる。例えば $s \\to u\' \\to v\' \\to u \\to v \\to g$ なら、 $s \\to u \\to v\' \\to g$ に流すことができる。

## 実装例

ac-library の MaxFlow は辺の流量・容量変更ができるので便利。

[Run #4856232 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3198/review/4856232/misteer/C++17)

```cpp
#include <atcoder/maxflow>

namespace ac = atcoder;

#include <iostream>
#include <vector>
#include <map>

void solve() {
    int n, m;
    std::cin >> n >> m;

    int s = n * 2, g = n * 2 + 1;
    ac::mf_graph<int> graph(n * 2 + 2);

    std::vector<bool> exist;                 // 辺が存在するか
    std::map<std::pair<int, int>, int> eid;  // 辺のグラフ中におけるid

    auto add_edge = [&](int u, int v) {
        eid[std::make_pair(u, v)] = graph.add_edge(u, v, 1);
        exist.push_back(true);
    };

    for (int i = 0; i < n; ++i) {
        add_edge(s, i);
        add_edge(i + n, g);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        add_edge(u, v + n);
    }

    // 初期流量
    int f = graph.flow(s, g);

    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        if (eid.count({u, v + n})) {
            int i = eid[{u, v + n}];

            if (exist[i]) {
                // 辺iの容量を0にする
                if (graph.get_edge(i).flow == 1) {
                    // 押し戻す
                    --f;
                    graph.change_edge(eid[{s, u}], 1, 0);
                    graph.change_edge(eid[{v + n, g}], 1, 0);
                }
                graph.change_edge(i, 0, 0);

            } else {
                // 辺iの容量を1にする
                graph.change_edge(i, 1, 0);
            }
            exist[i] = !exist[i];

        } else {
            // 新たな辺を追加
            add_edge(u, v + n);
        }

        // 差分だけ流す
        f += graph.flow(s, g);

        std::cout << (f == n ? "Yes" : "No") << "\n";
    }
}
```

