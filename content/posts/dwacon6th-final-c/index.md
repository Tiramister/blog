---
title: "第 6 回 ドワンゴからの挑戦状 本選 C - Tree Shrinking"
date: 2020-02-14
tags: [atcoder]
---

[C - Tree Shrinking](https://atcoder.jp/contests/dwacon6th-final/tasks/dwacon6th_final_c)

## 問題

木 $G = (V, E)$ が与えられる．この木に対して以下の操作を $n - 1$ 回行う．最初スコアは $0$ である．

- $e = uv \\in E$ を当確率でランダムに選ぶ．
- $deg(u) \\cdot deg(v)$ がスコアに加算される．
- $e$ を縮約する．

最終的なスコアの期待値を求めよ．

### 制約

- $2 \\leq |V| \\leq 10\^5$

## 考察

期待値の積ということで，各辺対 $e\_1, e\_2 \\in E$ の「スコアへの寄与の期待値」，言い換えると「操作中に $e\_1, e\_2$ 両方に接続する辺が選ばれる回数の期待値」が知りたくなる．**辺対は順序対ではない**，つまり $(e\_1, e\_2)$ と $(e\_2, e\_1)$ で 2 回カウントしないことに注意．

まず $e\_1, e\_2$ が隣接しているとき．この場合はどんな順番に操作をしても， $e\_1$ か $e\_2$ が操作対象になるときにちょうど 1 回だけカウントされる．よって期待値は $1$ ．$e\_1 = e\_2$ のケースも考えることに注意．

そうでない場合．2 辺間の距離を $d$ とすると，2 辺を両端とするパス内で 2 辺間の辺が先に全て選ばれた場合のみちょうど **2 回** カウントされる．よって期待値は $\\frac\{2\}\{\{\}\_\{d + 2\} C\_2\}$ ．

このままでも進められるのだが，後々考えやすくするために「辺対」と「その外側の頂点対」の間で一対一対応を作る．すると，スコアの期待値は以下の式で求まる．

$$
\\sum\_\{1 \\leq u \\lt v \\leq |V|\} e\_\{d(u, v)\} \\quad
\\left(
   e\_d =
   \\begin\{cases\}
       1                  & (d \\leq 2) \\\\
       \\frac\{2\}\{\{\}\_d C\_2\} & (d \\gt 2)
   \\end\{cases\}
\\right)
$$

よって 2 点対間の距離分布が分かれば，それに適当な係数 $e\_d$ を掛けることで解が求まる．

距離分布については，蟻本 P.321 に部分問題である「距離 $k$ 以下の頂点対の個数」を重心分解で求める方法が載っている．今回も基本的な方針はこれと同じ．

ある 2 つの部分木の距離分布 $(a\_d), (b\_d)$ が与えられたとする．このとき，これら 2 つの部分木をマージしたときの距離分布を $(c\_d)$ とすると，

$$
c\_d = \\sum\_\{0 \\leq d\' \\leq d\} a\_\{d\'\} b\_\{d - d\'\}
$$

となる．これはまんま和に関する畳み込みなので，**FFT**で高速化できる．ただこれを全部分木対に対して計算すると遅いので，累積和を取りながらやる必要がある．なぜか次数が小さい方からマージすると速くなる．

## 実装例

1 つ 1 つの処理はライブラリに丸投げすることを意識すると，意外と考えることは少ない．

[提出 #10090069 - 第6回 ドワンゴからの挑戦状 本選](https://atcoder.jp/contests/dwacon6th-final/submissions/10090069)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>

/* ----- Mod Int ----- */
template <int MOD>
struct ModInt { ... };
constexpr int MOD = 998244353;
using mint = ModInt<MOD>;
using mints = std::vector<mint>;

/* ----- NTT ----- */
template <int MOD, int Root>
struct NumberTheoreticalTransform { ... };
const NumberTheoreticalTransform<MOD, 3> NTT;

/* ----- Graph ----- */
template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

/* ----- Centroid Decomposition ----- */
template <class Cost = int>
struct Centroid { ... };

/* ----- main ----- */
// priority queue用の比較関数
struct Compare {
    bool operator()(const mints& lhs, const mints& rhs) {
        return lhs.size() > rhs.size();
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
    std::queue<int> cents;  // 次見る部分木の代表点
    cents.push(0);
    std::vector<int> dist(n);  // BFS用

    mints distr(n, 0);
    while (!cents.empty()) {
        int r = cents.front();
        cents.pop();

        // 重心を探す
        r = cent.find(r);
        cent.deleted[r] = true;

        // 各部分木の距離分布 次数について昇順に格納
        std::priority_queue<mints, std::vector<mints>, Compare> polys;

        for (auto e : graph[r]) {
            if (cent.deleted[e.dst]) continue;
            cents.push(e.dst);

            // BFSで距離分布を求める
            mints poly(1, 0);
            std::queue<std::pair<int, int>> que;
            que.emplace(e.dst, r);
            dist[e.dst] = 1;

            while (!que.empty()) {
                int v, p;
                std::tie(v, p) = que.front();
                que.pop();

                while ((int)poly.size() <= dist[v]) poly.push_back(0);
                poly[dist[v]] += 1;

                for (auto f : graph[v]) {
                    if (p == f.dst || cent.deleted[f.dst]) continue;
                    dist[f.dst] = dist[v] + 1;
                    que.emplace(f.dst, v);
                }
            }
            polys.push(poly);
        }

        // 頂点数1の部分木を用意するとやりやすい
        mints acc(1, 1);

        while (!polys.empty()) {
            auto poly = polys.top();
            polys.pop();

            // 畳み込みして全体に加算
            auto prod = NTT.ntt(poly, acc);
            for (int d = 0; d < (int)prod.size(); ++d) {
                distr[d] += prod[d];
            }

            // 累積和にも加算
            while (acc.size() < poly.size()) acc.push_back(0);
            for (int d = 0; d < (int)poly.size(); ++d) {
                acc[d] += poly[d];
            }
        }
    }

    // 係数と共に畳み込み
    mint ans = 0;
    for (int d = 1; d < n; ++d) {
        ans += distr[d] * (d <= 2 ? 1 : mint(4) / (mint(d) * (d - 1)));
    }
    for (int d = 1; d < n; ++d) ans *= d;
    std::cout << ans << std::endl;
}
```

