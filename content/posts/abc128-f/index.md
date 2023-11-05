---
title: "AtCoder Beginner Contest 128 F - Frog Jump"
date: 2019-11-29
tags: [atcoder]
---

[F - Frog Jump](https://atcoder.jp/contests/abc128/tasks/abc128_f)

## 問題

$n$ 個のマスがあり，マス $i$ にはスコア $s\_i$ が割り当てられている．
今からこのマスとコマを使ってゲームをする．

まず正整数 $a, b$ を決め，コマをマス $0$ に置く．
そしてコマを右に $a$ マス，左に $b$ マス，右に $a$ マス...と動かしていく．
これをコマが範囲外に出るかマス $n - 1$ に着くまで繰り返す．

移動中にコマが範囲外に出たり，同じマスに二度停まったら失格となる．そうでない場合，訪れたマスに割り当てられたスコアの総和が得点となる．

$a, b$ を上手く決めることで，スコアを最大化せよ．

### 制約

- $3 \\leq n \\leq 10\^5$
- $- 10\^9 \\leq s\_i \\leq 10\^9$

## 考察

ガチャガチャと言い換えると，以下のゲームと同値と分かる．

{{<framed>}}
まず正整数 $d$ を決め，赤いコマをマス $0$ ，青いコマをマス $n - 1$ に置く．
そして赤いコマを右に $d$ マス，青いコマを左に $d$ マス同時に動かす，というのを好きな回数だけ繰り返す．
途中で一方のコマがもう一方が既に訪れたマスに移動したり， **青いコマの座標が $d$ 以下になったら** 失格．そうでない場合，2 つのコマが訪れたマスに(ry
{{</framed>}}

上のゲームで $k$ 回の移動が行われたとする．
このとき $a = n - 1 - kd, b = a - d$ とすれば全く同じ移動ができることが分かるだろう．
マス $a$ が最後に青いコマがいるマスと対応するのだが． $b \\gt 0$ から太字の制約は来ている．

これを全ての $d$ について愚直にシミュレーションすればいい．計算量は調和級数で $O(n \\log n)$ ．

## 実装例

[提出 #8689054 - AtCoder Beginner Contest 128](https://atcoder.jp/contests/abc128/submissions/8689054)

```cpp
#include <iostream>
#include <vector>

using lint = long long;

int main() {
    int n;
    std::cin >> n;

    std::vector<lint> ss(n);
    for (auto& s : ss) std::cin >> s;

    lint ans = 0;
    for (int k = 1; k < n; ++k) {
        int l = 0, r = n - 1;
        lint sum = 0;

        while (r > k && (r > l || r % k != 0)) {
            sum += ss[l] + ss[r];
            ans = std::max(ans, sum);
            l += k;
            r -= k;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
```
