---
title: "AtCoder Grand Contest 037 D - Sorting a Grid"
date: 2020-01-24
tags: [atcoder]
---

[D - Sorting a Grid](https://atcoder.jp/contests/agc037/tasks/agc037_d)

## 問題

$1$ から $nm$ までの整数が 1 つずつ書かれた $n \\times m$ のグリッドがある．今からこれに以下の 3 つの操作を順に行うことで， $i$ 行 $j$ 列のマスに $(i - 1) \\cdot m + j$ が書かれるようにしたい．

1. 各行の間で，数字を好きなように並び替える．
2. 各列の間で，数字を好きなように並び替える．
3. 各行の間で，数字を好きなように並び替える．

これを実現するようなある操作について，操作 1，2 の直後のグリッドの状態を求めよ．

なお，どのような初期状態についても目標を達成するような操作が存在する．

### 制約

- $1 \\leq n, m \\leq 100$

## 考察

まず操作 1, 3 で行の中の数字は自由に並べられるので，本質的には各行が保持している数字の種類だけが重要となる．

そこで $[1, m], [m + 1, 2m], \\cdots, [(n - 1)m + 1, nm]$ の各区間の数字に同じ色を割り振ることにする．すると，最終状態にて各列は全種類の色の数字を持っているので，操作 1 で各列が全種類の色を持つように移動させなければならない．

一方でそれが達成できれば，後は操作 2 で各列を上から昇順にソートして，操作 3 で各行を左から昇順にソートすれば目標を達成できる．

操作 1 後のグリッドを左端の列から決めていくことにする．もし何らかの方法で全色が左端のグリッドに並ぶように各行から数を選べたならば，左端の列に選ばれた数を無視することで再帰的にグリッドを構成できる．

そしてこの選び方は **完全二部マッチング** によって構成できる．
「行」と「色」をそれぞれ頂点集合とし， $i$ 行に色 $c$ の数字が含まれていれば「行グループ」の頂点 $i$ から「色グループ」の頂点 $c$ に辺を張る．そして辺 $(i, c)$ がマッチングに含まれていれば，行 $i$ から色 $c$ の数を 1 つ選んで左端の列に移す，とすれば左端の列に全色が揃う。これを繰り返せばいい。

## 実装例

[提出 #9700096 - AtCoder Grand Contest 037](https://atcoder.jp/contests/agc037/submissions/9700096)

```cpp
#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

template <class Cap, bool isDirect>
struct MaxFlow { ... };
struct BiMatching { ... };

template <class T>
std::vector<T> vec(int len, T elem) { ... }

void solve() {
    int n, m;
    std::cin >> n >> m;

    auto nums = vec(n, vec(n, vec(0, 0)));
    // 行iが持っている色cの数の集合
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a;
            std::cin >> a;
            nums[i][(a - 1) / m].push_back(a);
        }
    }

    auto bs = vec(n, vec(m, 0));
    for (int j = 0; j < m; ++j) {
        // 二部グラフを構築
        BiMatching bm(n, n);
        for (int i = 0; i < n; ++i) {
            for (int c = 0; c < n; ++c) {
                if (nums[i][c].empty()) continue;
                bm.span(i, c);
            }
        }

        // マッチングを元に割り付け
        auto res = bm.matching();
        for (auto p : res) {
            int i, c;
            std::tie(i, c) = p;
            bs[i][j] = nums[i][c].back();
            nums[i][c].pop_back();
        }
    }

    for (auto& v : bs) {
        for (auto b : v) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // 各行から該当する色の数を探す
            for (int k = 0; k < n; ++k) {
                if ((bs[k][j] - 1) / m == i) {
                    std::cout << bs[k][j] << " ";
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
}
```

