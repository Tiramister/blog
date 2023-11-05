---
title: "AtCoder Grand Contest 018 C - Coins"
date: 2018-09-12
tags: [atcoder]
---

[C - Coins](https://atcoder.jp/contests/agc018/tasks/agc018_c)

## 概要

$X + Y + Z$ 人の人がいる。人 $i$ は金、銀、銅のコインをそれぞれ $A\_i, B\_i, C\_i$ 枚ずつ持っている。

あなたは彼らのうち $X$ 人から金のコイン、 $Y$ 人から銀のコイン、 $Z$ 人から銅のコインを全て貰うことができる。
ただし、同じ人から 2 種類以上のコインを貰うことはできない。

このとき、あなたが貰えるコインの枚数の最大値を求めよ。

### 制約

- $1 \\leq X, Y, Z$
- $X + Y + Z \\leq 10\^5$
- $1 \\leq A\_i, B\_i, C\_i \\leq 10\^9$

## 解説

銅は無視して金と銀についてだけ考えることにする。
あと冗長なので金のコインを貰う人のことを「金の人」と呼ぶことにする。銀と銅も同様。

まず、人々を(金コインの枚数)-(銀コインの枚数)で昇順にソートして左から並べる。
この中には最適解における金の人 $X$ 人と銀の人 $Y$ 人がいるわけだが、実は **最適解における金の人はすべての銀の人より右側にいる** ことが分かる。

{{<collapse summary="証明">}}
金の人の右に銀の人がいるとする。
このとき、この 2 人から貰うコインの種類を交換することで、総コイン数はより多くなる。
元金の人から銀コインを貰うことによる損を、元銀の人から金コインを貰うことによる得が上回るためである。
{{</collapse>}}

先のソートした状態にて、左から $K$ 人と右から $X + Y + Z - K$ 人の 2 グループに分ける。このとき、

- 左グループは $Y$ 人を銀の人、 $K - Y$ 人を銅の人
- 右グループは $X$ 人を金の人、 $Y + Z - K$ 人を銅の人

に分けるような最適解が存在する。各グループにおける割り振りはどうすればいいかというと、先と同じように(金 or 銀の枚数)-(銅の枚数)でソートしてやればいい。この辺はグループの人数を増やしながら priority_queue を使えばできる。

この割り振りにおけるコインの合計枚数を各 $K$ について求めれば、その最大値が答えとなる。

## 実装例

[提出 #3181196 - AtCoder Grand Contest 018](https://atcoder.jp/contests/agc018/submissions/3181196)

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;

#define mp make_pair
#define SORT(v) sort((v).begin(), (v).end())
#define GSORT(v) sort((v).begin(), (v).end(), greater<decltype((v).front())>())
#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)

int main() {
    // X, Y, Zを受け取る
    // N = X + Y + Z
    ll X[3], N = 0;
    FOR(j, 0, 3) {
        cin >> X[j];
        N += X[j];
    }

    // A_i, B_i, C_iを受け取る
    vector<vector<ll>> coin(N, vector<ll>(3, 0));
    FOR(i, 0, N) {
        FOR(j, 0, 3) {
            cin >> coin[i][j];
        }
    }

    // (gold - silver, index)の配列
    vector<pair<ll, ll>> gs(N);
    FOR(i, 0, N) {
        gs[i] = make_pair(coin[i][0] - coin[i][1], i);
    }

    SORT(gs);

    // silver[i] = 「K = Y + iにおける
    //              左グループのコイン枚数の最大値」
    vector<ll> silver(X[2] + 1, 0);

    // 中身は(silver - bronze, index)
    GPQ<pair<ll, ll>> sb;

    // まずは最初のY個を追加してしまう
    FOR(i, 0, X[1]) {
        ll id = gs[i].second;
        sb.push(make_pair(coin[id][1] - coin[id][2], id));
        silver[0] += coin[id][1];
    }

    // ここから銅の人が出始める
    FOR(i, 0, X[2]) {
        ll id = gs[i + X[1]].second;
        sb.push(mp(coin[id][1] - coin[id][2], id));

        silver[i + 1] = silver[i] + coin[id][1];

        // 先頭の人を銀の人から銅の人に変える
        auto p = sb.top();
        sb.pop();
        silver[i + 1] += (coin[p.second][2] - coin[p.second][1]);
    }

    // 逆順にして(gold - bronze)で全く同じことをする
    GSORT(gs);

    vector<ll> gold(X[2] + 1, 0);
    GPQ<pair<ll, ll>> gb;
    FOR(i, 0, X[0]) {
        ll id = gs[i].second;
        gb.push(mp(coin[id][0] - coin[id][2], id));
        gold[0] += coin[id][0];
    }

    FOR(i, 0, X[2]) {
        ll id = gs[i + X[0]].second;
        gb.push(mp(coin[id][0] - coin[id][2], id));

        gold[i + 1] = gold[i] + coin[id][0];

        auto p = gb.top();
        gb.pop();
        gold[i + 1] += (coin[p.second][2] - coin[p.second][0]);
    }

    ll ans = 0;
    FOR(i, 0, X[2] + 1) {
        // K = Y + iにおけるコインの合計枚数と比較
        ans = max(ans, silver[i] + gold[X[2] - i]);
    }

    cout << ans << endl;
    return 0;
}
```

