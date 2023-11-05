---
title: "AtCoder Beginner Contest 149 F - Surrounded Nodes"
date: 2019-12-29
tags: [atcoder]
---

[F - Surrounded Nodes](https://atcoder.jp/contests/abc149/tasks/abc149_f)

## 問題

$n$ 頂点の木が与えられる．

今からこの木の各頂点を，独立に確率 $\\frac\{1\}\{2\}$ で黒か白に塗る．
塗り終わった後，黒い頂点を全て含む最小の部分木 $S$ を取る．

このとき， $S$ に含まれる白い頂点の個数の期待値を求めよ．

### 制約

- $2 \\leq n \\leq 2 \\times 10\^5$

## 考察

期待値問題の常套手段として，代わりに $p\_v =$ 「頂点 $v$ が白く塗られ，かつ $S$ に含まれる確率」を求めることにする．すると答えは $\\sum p\_v$ となる．
ただ，ここでは $p\_v$ の代わりに求めやすい「頂点 $v$ が白く塗られ，かつ $S$ に含まれない確率」を求めることにする．

木から頂点 $v$ を取り除くと，いくつかの部分木 $T\_1, \\cdots, T\_k$ へと分解される．このとき「 $v$ が $S$ に含まれない」ことは，「 $T\_1, \\cdots, T\_k$ のうち黒い頂点を含むものが 1 つ以下である」ことと同値となる。

黒い頂点を含む $T\_i$ が 1 つもない確率は、全頂点が白である場合のみなので $2\^\{-n\}$ ．黒い頂点を含む $T\_i$ がちょうど 1 つである確率は，各 $i$ について「 $T\_i$ が黒い頂点を少なくとも 1 つ含み，他は全部白の確率」を足し上げればよく，これは

$$
\\sum\_\{i=1\}\^\{k\} \\frac\{1\}\{2\^\{n - |T\_i|\}\} \\cdot
\\left(1 - \\frac\{1\}\{2\^\{|T\_i|\}\} \\right)
$$

で求まる．

よって後は各 $v$ について $|T\_1|, \\cdots, |T\_k|$ が求まればよく，これは DFS により全体で $O(n)$ で計算できる．

## 実装例

[提出 #9227350 - AtCoder Beginner Contest 149](https://atcoder.jp/contests/abc149/submissions/9227350)

```cpp
#include <iostream>
#include <vector>
#include <functional>

template <int MOD>
struct ModInt { ... };

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    const mint twoinv = mint(2).inv();

    int n;
    std::cin >> n;

    Graph<> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        tree[u].emplace_back(u, v);
        tree[v].emplace_back(v, u);
    }

    mint ans = 0;

    // vを根とする部分木のサイズを返す
    std::function<int(int, int)> dfs =
        [&](int v, int r) {
            std::vector<int> ch;
            int sz = 0;

            for (auto e : tree[v]) {
                if (e.dst == r) continue;
                ch.push_back(dfs(e.dst, v));
                sz += ch.back();
            }

            // rを含む部分木のサイズ
            ch.push_back(n - 1 - sz);

            mint co = twoinv.pow(n);  // 全部白
            for (auto c : ch) {
                // 1つだけ黒を含む
                co += twoinv.pow(n - c) * (mint(1) - twoinv.pow(c));
            }

            ans += twoinv - co;  // 余事象を取る
            return sz + 1;
        };

    dfs(0, -1);
    std::cout << ans << std::endl;
    return 0;
}
```

