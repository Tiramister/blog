---
title: "HUPC 2020 day3 J - Proper Instructions"
date: 2020-09-17
tags: [voluntary]
---

[3181 < VPC CVPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/CVPC/3181)

## 問題

数直線上の座標 $0$ にコマが置かれている。また開始時点での時刻を $0$ とする。
あなたはこのコマを時刻 $1$ 毎に距離 $1$ だけ動かすことができる(動かさなくてもよい)。

指示が $N$ 個与えられる。 $i$ 番目の指示は「時刻 $T\_i$ にコマが区間 $[L\_i, R\_i]$ にあるようにせよ」というものである。

指示の部分集合であって、適切にコマを動かすことで全ての指示を満たせるようなものの個数を求めよ。

### 制約

- $1 \\leq N \\leq 300$
- $1 \\leq T\_1 \\lt T\_2 \\lt \\cdots \\lt T\_N \\leq 10\^9$
- $-10\^9 \\leq L\_i \\leq R\_i \\leq 10\^9$

## 考察

まず「最初にコマが座標 $0$ にある」というのは「 $T\_0 = 0, L\_0 = 0, R\_0 = 0$ という指示がある」という風に言い換えられる。

指示を前から順番に見ていく DP を考える。このとき持つ状態として「この指示の前の時点で、コマを $[L, R]$ の好きな位置に置くことができる」というのが考えられる。
遷移は時刻によって $[L, R]$ を左右に引き伸ばし、(指示を守るなら)指示との共通部分を取るだけでよい。空区間になったら不可能となる。

一見すると、この DP は状態数が莫大なので成り立つように思えない。しかし実は、 $i$ 個の指示を処理した時点で、 $L, R$ として考えられるのはそれぞれ高々 $i$ 通りなのである。
つまり状態数が $O(N\^2)$ なので、この DP は $O(N\^3)$ で動く(map を使うと $O(N\^3 \\log N)$ )。

なぜ $L, R$ が高々 $i$ 個になるのかだが、簡単に言うと「 $L$ として考えられるのは、過去のいずれかの命令 $L\_i\'$ を左に引き伸ばしたものだから」という理由である。

## 実装例

[Run #4849519 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3181/review/4849519/misteer/C++17)

```cpp
#include <iostream>
#include <map>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

void solve() {
    int n;
    std::cin >> n;

    // [L, R]に自由に移動できるときの通り数
    std::map<std::pair<int, int>, mint> dp;
    dp[std::make_pair(0, 0)] = 1;

    int pt = 0;  // 前の命令の時刻
    while (n--) {
        int t, l, r;
        std::cin >> t >> l >> r;

        std::map<std::pair<int, int>, mint> ndp;
        for (auto [p, v] : dp) {
            auto [pl, pr] = p;

            // 左右に引き伸ばす
            pl -= t - pt;
            pr += t - pt;

            {
                // 守らない場合
                auto q = std::make_pair(pl, pr);
                if (!ndp.count(q)) ndp[q] = 0;
                ndp[q] += v;
            }

            // 守る場合
            pl = std::max(pl, l);
            pr = std::min(pr, r);
            if (pr < pl) continue;

            {
                auto q = std::make_pair(pl, pr);
                if (!ndp.count(q)) ndp[q] = 0;
                ndp[q] += v;
            }
        }

        std::swap(dp, ndp);
        pt = t;
    }

    mint ans = 0;
    for (auto [p, v] : dp) ans += v;
    std::cout << ans - 1 << "\n";  // 空集合を引く
}
```

