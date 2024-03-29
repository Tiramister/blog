---
title: "HUPC 2020 day3 G - Katsusando"
date: 2020-09-17
tags: [voluntary]
---

[3178 < VPC CVPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/CVPC/3178)

## 問題

数直線上に $N$ 個の玉が落ちている。 $i$ 番目の玉は座標 $X\_i$ にあり、その重さは $W\_i$ である。

これからあなたは 2 台のロボットを使って、以下の手順で全ての玉を回収する。

1. 2 台のロボットを数直線上の好きな整数座標に置く。このときコストが $1$ かかる。もしロボットが置かれた位置に玉があれば、ロボットは玉を回収する。
2. 2 台のロボットが同じ座標になければ、片方のロボットを 1 動かす。もし移動先に玉があれば、ロボットは玉を回収する。このときかかるコストは、移動するロボットが持っている玉の総重量 $+1$ となる。
3. 2 台のロボットが同じ座標にあれば、あなたは数直線上から 2 台のロボットを回収し、ロボットが持っている玉を回収する。このときコストが $K$ かかる。
4. もし数直線上に玉が残っていれば 1 に戻り、なければ終了する。

全ての玉を回収するのにかかる総コストの最小値を求めよ。

### 制約

- $1 \\leq N \\leq 2 \\cdot 10\^3$
- $1 \\leq K \\leq 10\^9$
- $1 \\leq X\_1 \\lt X\_2 \\lt \\cdots \\lt X\_N \\leq 10\^5$
- $1 \\leq W\_i \\leq 10\^5$

## 考察

まずロボットの動かし方として、「玉のある座標に 2 台を置いてから、その間のいずれかの玉に向けて移動させる」というのが最善である。
つまり「区間を選択して、その区間の玉を全部回収する」という操作を繰り返していることになる。

さらに「選択された区間同士が交わるのは損である」ことが分かる。
包含関係にある場合は包含されている方の操作が不要で、そうでない場合も一方の区間を共通部分の分だけ縮められるからだ。

すると結局、「 $[1, N]$ をいくつかの連続区間に分割する」ような区間の選び方が最善となる。
イメージとしては以下の通り。

{{<image src="0.png">}}

ここで、上の図における「青い線」と「赤い線」を終端として、2 つの DP テーブルを考える。すなわち

- $bdp\_\{i\} = [1, i]$ を回収しきったときの最小コスト。
- $rdp\_\{i\} = [1, i]$ を**左側のロボット**で回収したときの最小コスト。

といった具合。答えは $bdp\_N$ となり、更新式は以下のようになる。

- $bdp\_\{i\} = \\min\_\{1 \\leq j \\leq i\} \\\{ adp\_j + rcost\_\{i, j\} + 1 \\\}$
- $rdp\_\{i\} = \\min\_\{0 \\leq j \\lt i\} \\\{ bdp\_j + lcost\_\{j + 1, i\} + K \\\}$

ここで $lcost\_\{l, r\}$ は「区間 $[l, r]$ を左から右へ移動して回収するときのコスト」とする。これは $l$ を固定して $r$ を右に伸ばしていくことで、 $\\Theta(N\^2)$ で前計算できる。
$rcost$ も左右が逆なだけで同様。

## 実装例

[Run #4849435 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3178/review/4849435/misteer/C++17)

```cpp
#include <iostream>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using lint = long long;
constexpr lint INF = 1LL << 60;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<lint> xs(n + 1), ws(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> xs[i] >> ws[i];

    // [i, j]を左から右へ移動するときのコスト
    auto lcost = vec(n + 1, vec(n + 1, 0LL));
    for (int l = 1; l <= n; ++l) {
        lint sum = ws[l] + 1;
        for (int r = l + 1; r <= n; ++r) {
            lcost[l][r] = lcost[l][r - 1] + sum * (xs[r] - xs[r - 1]);
            sum += ws[r];
        }
    }

    // [i, j]を右から左へ移動するときのコスト
    auto rcost = vec(n + 1, vec(n + 1, 0LL));
    for (int r = 1; r <= n; ++r) {
        lint sum = ws[r] + 1;
        for (int l = r - 1; l >= 1; --l) {
            rcost[l][r] = rcost[l + 1][r] + sum * (xs[l + 1] - xs[l]);
            sum += ws[l];
        }
    }

    std::vector<lint> bdp(n + 1, INF), rdp(n + 1, INF);
    // 文章中で定義したDPテーブル2つ
    bdp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int l = 0; l < i; ++l) {
            rdp[i] = std::min(rdp[i], bdp[l] + 1 + lcost[l + 1][i]);
        }

        for (int l = 1; l <= i; ++l) {
            bdp[i] = std::min(bdp[i], rdp[l] + rcost[l][i] + k);
        }
    }

    std::cout << bdp[n] << "\n";
}
```

