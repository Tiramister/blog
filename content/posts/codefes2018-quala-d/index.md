---
title: "CODE FESTIVAL 2018 qual A D - 通勤"
date: 2019-10-25
tags: [atcoder]
---

[D - 通勤](https://atcoder.jp/contests/code-festival-2018-quala/tasks/code_festival_2018_quala_d)

## 問題

数直線状の道路があり，座標 $0$ に車が停まっている．
車のガソリンタンクの容量は $f$ で，1 進む毎にガソリンを 1 消費する．
なお車は負方向に走ったり，走る以外の方法でガソリンを消費することはできない．

また道路上にはガソリンスタンドが $n$ 箇所あり， $i$ 番目のガソリンスタンドは座標 $x\_i$ にある．

ガソリンが満タンの状態からこの車は正方向に移動するが，ガソリンスタンドのある座標に着く度に以下のルールに則ってガソリンを補給する．

- ガソリンの残量が $t$ 以上なら補給しない．
- そうでなければガソリンを満タンまで補給する．

ガソリンスタンドの部分集合で，それら全てを潰しても車がガソリンを切らすことなく $d$ に着けるようなものの個数を求めよ．

### 制約

- $0 \\lt t \\leq f \\leq 10\^9$
- $1 \\leq n \\leq 10\^5$
- $0 \\lt x\_1 \\lt \\cdots \\lt x\_n \\lt d \\leq 10\^9$

## 考察

$dp\_i =$ 「$i$ 番目のガソリンスタンドでガソリンが満タンのとき， $d$ まで到達できるような $i + 1$ 番目以降の潰し方の数」とする．ここで，

$$
\\begin\{aligned\}
   j &= \\min \\\{j\' \\mid x\_i + (f - t) \\lt x\_\{j\'\} \\\} \\\\
   k &= \\min \\\{k\' \\mid x\_i + f \\lt x\_\{k\'\} \\\}
\\end\{aligned\}
$$

とする．すると，

- $(i, j)$ はスルーするので潰すか否かを自由に選べる．
- $[j, k)$ は少なくとも 1 つは残さないといけず，残した中で一番前にあるものにてガソリンが満タンになる．

となる．後者で一番前に残ったものがどれかで場合分けすると，

$$
dp\_i = 2\^\{j - i - 2\} \\sum\_\{k\' = j\}\^\{k-1\} dp\_\{k\'\}
$$

となる． $j, k$ は`upper_bound()`で求められて，DP テーブルは後ろから埋めていけば区間和にセグ木を使うことで十分高速に更新できる．

後は $d$ の扱いが厄介．普通はガソリンスタンドとみなして，距離 $f - t$ 以内にあるときは(潰すか否かを自由に選べないので)除外するみたいな工夫が要る．

## 実装例

[提出 #8114412 - CODE FESTIVAL 2018 qual A](https://atcoder.jp/contests/code-festival-2018-quala/submissions/8114412)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

template <int MOD>
class ModInt { ... };

template <class Data, class Operator>
class SegmentTree { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int d, f, t, n;
    std::cin >> d >> f >> t >> n;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;
    xs.insert(xs.begin(), 0);
    xs.push_back(d);

    SegmentTree<mint, mint> seg(
        n + 2, 0,
        [](mint a, mint b) { return a + b; },
        [](mint e, mint a) { return e; });

    seg.update(n + 1, 1);
    for (int i = n; i >= 0; --i) {
        int x = xs[i];
        int j = std::upper_bound(xs.begin(), xs.end(), x + f - t) - xs.begin();
        // (i, j): arbitrary chosen

        if (j == n + 2) {
            seg.update(i, (mint(2) ^ (j - i - 2)));
            continue;
        }

        int k = std::upper_bound(xs.begin(), xs.end(), x + f) - xs.begin();
        // [j, k): either of them is chosen

        seg.update(i, (mint(2) ^ (j - i - 1)) * seg.query(j, k));
    }

    std::cout << seg.query(0, 1) << std::endl;
    return 0;
}
```

