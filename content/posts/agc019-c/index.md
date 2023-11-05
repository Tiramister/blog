---
title: "AtCoder Grand Contest 019 C - Fountain Walk"
date: 2018-09-12
tags: [atcoder]
---

[C - Fountain Walk](https://atcoder.jp/contests/agc019/tasks/agc019_c)

## 概要

x 軸方向と y 軸方向にそれぞれ $10\^8$ 本の道が $100m$ 間隔で直交するように通っている(要は $100m$ 間隔のだだっ広いグリッドがある)。

この道の交差点上に $N$ 個の噴水がそれぞれ $(X\_i, Y\_i)$ に置かれている。噴水は半径 $10m$ の円形をしていて、その外周に道が通っている。また **1 つの道上に 2 つ以上の噴水が置かれていることはない** 。

このとき、 $(x\_1, y\_1)$ から $(x\_2, y\_2)$ へ移動するための最短距離を求めよ。

{{<image src="0.png" width="50%">}}

### 制約

- $0 \\leq x\_1, y\_1, x\_2, y\_2, X\_i, Y\_i \\lt 10\^8$
- $1 \\leq N \\leq 2 \\times 10\^5$
- $i \\neq j$ のとき、 $X\_i \\neq X\_j$ **かつ** $Y\_i \\neq Y\_j$
- スタートとゴールに噴水は置かれていない

## 解説

適当に上下左右判定することで、 $x\_1 \\leq x\_2$ かつ $y\_1 \\leq y\_2$ のケースに帰着できる。

最短経路ということで、まず x 正方向と y 正方向に移動することだけ考えればいい。
よって $(x\_1, y\_1)$ と $(x\_2, y\_2)$ を対頂角とする長方形に入っていない噴水は無視していい。

そういったルートの中で、できるだけ多く噴水で曲がるようなルートを探すことを考える。
1 つのルートで 2 つの噴水 $i, j$ で曲がることができる条件は、 $X\_i < X\_j$ かつ $Y\_i < Y\_j$ が成立することである。
つまり任意の 2 つがこれを満たす最大の噴水の集合を見つければいい。
そしてこれは、 $X\_i$ について昇順にソートすれば、 $Y\_i$ の **最長増加部分列** となる。
有名問題なので解き方は割愛。

最後に、この問題にはコーナーケースが存在する。それが「曲がる回数が長方形の幅と同じケース」である。

{{<image src="1.png">}}

この場合、必ず 1 回は噴水を突っ切る必要があるため、その分のロスが生じる。

## 実装例

[提出 #3179466 - AtCoder Grand Contest 019](https://atcoder.jp/contests/agc019/submissions/3179466)

```cpp
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <vector>
using namespace std;

template <typename T>
using V = vector<T>;
using ll = long long;

#define SIZE(v) (static_cast<ll>((v).size()))
#define ALL(v) (v).begin(), (v).end()
#define SORT(v) sort(ALL(v))

const double PI = acos(-1);


// BITオブジェクト、Range Maximum Queryバージョン
class BIT {
public:
    explicit BIT(ll N, ll v) : V_NUM(N) {
        data.resize(N);
        fill(ALL(data), v);
    }

    ll query(ll i) {
        ll ret = 0;
        while (i > 0) {
            ret = max(ret, data[i]);
            i -= (i & -i);
        }
        return ret;
    }

    void update(ll i, ll v) {
        while (i < V_NUM) {
            data[i] = max(data[i], v);
            i += (i & -i);
        }
    }

    ll V_NUM;
    V<ll> data;
};

// 座標(coordinate)を保持する構造体
struct coo {
    coo(ll _x = 0, ll _y = 0) : x(_x), y(_y){};
    ll x;
    ll y;

    // ソートするために比較演算子をオーバーロードする
    bool operator<(const coo& r) const {
        return x == r.x ? y < r.y : x < r.x;
    }
};

// Y座標で座圧をする
map<ll, ll> compress(const V<coo>& a) {
    set<ll> sety;
    for (coo c : a) {
        sety.insert(c.y);
    }

    map<ll, ll> ret;
    ll idx = 1;
    for (ll y : sety) {
        ret[y] = idx;
        ++idx;
    }

    return ret;
}

int main() {
    cout << fixed << setprecision(12);

    // startとgoal
    coo s, g;
    cin >> s.x >> s.y >> g.x >> g.y;

    // startの方が下にくるようにする
    if (s.y > g.y) swap(s, g);

    ll N;
    cin >> N;
    V<coo> a;
    // 長方形領域内にある噴水のみを記録する

    for (ll i = 0; i < N; ++i) {
        ll x, y;
        cin >> x >> y;
        if (y < s.y || g.y < y) continue;

        if (s.x < g.x) {
            if (s.x <= x && x <= g.x) {
                a.push_back(coo(x - s.x, y - s.y));
            }
        } else {
            // startとgoalのX座標が逆の場合はこっちも左右反転する
            if (g.x <= x && x <= s.x) {
                a.push_back(coo(s.x - x, y - g.y));
            }
        }
    }

    SORT(a);
    map<ll, ll> com = compress(a);

    BIT bit(SIZE(com) + 1, 0);

    for (coo c : a) {
        ll y = com[c.y];
        bit.update(y, bit.query(y) + 1);
        // bit.query(y)でy以下の最大値を求める
        // それに1加えた値で更新
    }

    // BIT全体の最大値が答え
    ll turn = bit.query(SIZE(com));

    double ans = (abs(g.x - s.x) + abs(g.y - s.y)) * 100;
    // 噴水を無視した場合の距離
    ans -= (20 - PI * 5) * turn;
    // 曲がる分だけ削れる

    // コーナーケース
    if (turn == abs(g.y - s.y) + 1 || turn == abs(g.x - s.x) + 1) ans += PI * 5;

    cout << ans << endl;
    return 0;
}
```

