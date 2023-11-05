---
title: "AtCoder Grand Contest 011 A - Airport Bus"
date: 2018-11-11
tags: [atcoder]
---

[A - Airport Bus](https://atcoder.jp/contests/agc011/tasks/agc011_a)

## 概要

これから空港に $N$ 人の客が来る、 $i$ 番目の客は、今から $T\_i$ 秒後に来る。

これらの客全員を、何台かのバスで運ばなければならない。
1 台のバスの定員は $C$ 人で、さらに客を到着から $K$ 秒より長く待たせることはできない。

客全員を運ぶのに必要な、最小のバスの台数を求めよ。

### 制約

- $2 \\leq N \\leq 10\^5$
- $1 \\leq C \\leq 10\^9$
- $1 \\leq K \\leq 10\^9$
- $1 \\leq T\_i \\leq 10\^9$

## 解説

バスには詰められるだけ多くの客を詰めるのが最善である。下手に残しても得はしない。
したがって、「定員と待ち時間のどちらか一方をオーバーしかけたらバスを発車させる」という貪欲で解くことができる。

## 実装例

最初に `limit = -1` としているのは、1 人目のときだけ例外処理をしなくて済むようにするためである。

[提出 #3583053 - AtCoder Grand Contest 011](https://atcoder.jp/contests/agc011/submissions/3583053)

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll N, C, K;
    cin >> N >> C >> K;

    ll T[N];
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }
    sort(T, T + N);

    ll ans = 0, limit = -1, cap = 0;
    // ans   = 発車された累計バス台数
    // limit = 先頭の客の許容時間
    // cap   = 今バスに乗ってる客数

    for (int i = 0; i < N; ++i) {
        if (cap == C || T[i] > limit) {
            // 制限オーバーなので新しいバスに乗せる
            ++ans;
            limit = T[i] + K;
            cap = 0;
        }
        ++cap;
    }

    cout << ans << endl;
    return 0;
}
```

