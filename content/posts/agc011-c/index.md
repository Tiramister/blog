---
title: "AtCoder Grand Contest 011 C - Squared Graph"
date: 2018-09-15
tags: [atcoder]
---

[C - Squared Graph](https://atcoder.jp/contests/agc011/tasks/agc011_c)

## 概要

各頂点に $1 \\sim N$ の番号が振られた $N$ 頂点 $M$ 辺の単純無向グラフが与えられる。

これを元に、 $(1, 1) \\sim (N, N)$ まで番号の振られた $N\^2$ 頂点からなるグラフを、以下の規則に基づいて作る。

- 元のグラフにおいて $a, a\'$ 間にも $b, b\'$ 間にも辺が存在する場合、またその場合にのみ $(a, b), (a\', b\')$ 間に辺を張る。

こうして作られたグラフの連結成分の数を求めよ。

### 制約

- $1 \\leq N \\leq 10\^5$
- $0 \\leq M \\leq 2 \\times 10\^5$

## 解説

作られたグラフを具体的にイメージするのが非常に難しい。こういうときは多少手間でも手を動かすのが大事である。

実はサンプル 2 が非常に大きなヒントになっている。このサンプルで与えられるグラフの連結成分は以下の 3 パターンに分類できる。

- 2 色に塗り分けられるもの、つまり二部グラフ $(1, 2, 6)$
- 2 色で塗り分けられないもの $(3, 4, 5)$
- 1 頂点からなるもの、つまり孤立点 $(7)$

与えられたグラフにこれらの連結成分がそれぞれ $A, B, C$ 個あったとしよう。
このとき、答えは $(A + B)\^2 + A\^2 + N\^2 - (N - C)\^2$ で与えられる。

なぜこれが成立するのかを説明するには私では力不足なので割愛。 [解説放送](https://www.youtube.com/watch?v=cJ-WjtA34GQ) の石の説明がとてもわかり易いのでそちらを見るといいかと。

なお二部グラフ判定は多少面倒だが DFS で実装できる。

## 実装例

[提出 #3195404 - AtCoder Grand Contest 011](https://atcoder.jp/contests/agc011/submissions/3195404)

```cpp
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> path[100010];
int d[100010];
// 各頂点を0と1で塗り分ける

// 二部グラフならtrue
bool dfs(ll v, ll t) {
    if (d[v] >= 0) {
        return t == d[v];
    }

    d[v] = t;
    bool ret = true;
    for (ll sv : path[v]) {
        ret &= dfs(sv, 1 - t);
    }

    return ret;
}

int main() {
    ll N, M;
    cin >> N >> M;

    for (ll i = 0; i < M; ++i) {
        ll a, b;
        cin >> a >> b;
        --a;
        --b;
        path[a].push_back(b);
        path[b].push_back(a);
    }

    // 未探索なら-1
    fill(d, d + N, -1);

    ll even = 0, odd = 0, one = 0;
    // 二部グラフ、二部グラフでない連結成分と孤立点の数

    for (ll v = 0; v < N; ++v) {
        // 探索済みならパス
        if (d[v] >= 0) continue;

        // 孤立点判定
        if (path[v].empty()) {
            ++one;
            continue;
        }

        // 二部グラフ判定
        if (dfs(v, 0)) {
            ++even;
        } else {
            ++odd;
        }
    }

    cout << N * N - (N - one) * (N - one) + (odd + even) * (odd + even) + even * even << endl;
    return 0;
}
```

