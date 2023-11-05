---
title: "AtCoder Beginner Contest 130 F - Minimum Bounding Box"
date: 2019-11-29
tags: [atcoder]
---

[F - Minimum Bounding Box](https://atcoder.jp/contests/abc130/tasks/abc130_f)

## 問題

2 次元平面上に $n$ 個の点がある． $i$ 番目の点は時刻 $0$ にて座標 $(x\_i, y\_i)$ にあり，x 軸か y 軸に平行に 1(単位距離/単位時間)で等速直線運動をする．時刻 $t \\geq 0$ について，

- x 座標の最大値と最小値の差を $w\_x(t)$
- y 座標の最大値と最小値の差を $w\_y(t)$
- $s(t) = w\_x(t) w\_y(t)$

とする． $s(t)$ の最小値を求めよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $-10\^8 \\leq x\_i, y\_i \\leq 10\^8$

## 考察

まず $w\_x(t), w\_y(t)$ の傾きは $-2 \\to -1 \\to 0 \\to 1 \\to 2$ と段階的に変化していくことが分かる．この傾きの変化点でのみ $s(t)$ は最小値を取る，というのが本問の肝である．これを示す．

時刻 $[t, t + l]$ にて $w\_x(t), w\_y(t)$ の傾きがそれぞれ $d\_x, d\_y$ で不変とする．この区間で $s(t)$ が $t, t + l$ 以外で最小値を取らないことを示せば良い．

$d\_x, d\_y$ が同符号，あるいは一方が 0 である場合は $s(t)$ が単調なので OK．よって $d\_x d\_y \\lt 0$ の場合を考える． $w\_x = w\_x(t), w\_y = w\_y(t), 0 \\leq k \\leq l$ とすると，

$$
\\begin\{align*\}
s(t + k) - s(t)
&= (w\_x + k d\_x)(w\_y + k  d\_y) - w\_x w\_y \\\\
&= d\_x d\_y k\^2 + (d\_x w\_y + d\_y w\_x) k
\\end\{align*\}
$$

$d\_x d\_y \\lt 0$ よりこれは $k$ について上に凸な関数．よって $t, t + l$ 以外で最小値は取らない．以上で示された．

後は傾きの変化点を調べればよいが，これは 2 分探索で十分高速に行える．

最後に誤差についてだが，よく考えると変化点の時刻は $0.5$ の倍数であることが分かる．よって全体の座標を $2$ 倍することで，整数のまま厳密解を求めることができる．

## 実装例

[提出 #8690583 - AtCoder Beginner Contest 130](https://atcoder.jp/contests/abc130/submissions/8690583?lang=ja)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <limits>

using lint = long long;

struct Point {
    lint x, y, dx, dy;
};

const std::string dir = "RLUD";
const std::vector<lint>
    dxs{1, -1, 0, 0},
    dys{0, 0, 1, -1};

constexpr lint INF = 5e8;

int main() {
    int n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (auto& p : ps) {
        char d;
        std::cin >> p.x >> p.y >> d;
        p.x *= 2, p.y *= 2;

        for (int i = 0; i < 4; ++i) {
            if (d == dir[i]) {
                p.dx = dxs[i];
                p.dy = dys[i];
            }
        }
    }

    // wx(t), wy(t)を返す
    auto sim = [&](lint t) {
        lint xmin = INF * 2, xmax = -INF * 2,
             ymin = INF * 2, ymax = -INF * 2;

        for (const auto& p : ps) {
            lint x = p.x + p.dx * t,
                 y = p.y + p.dy * t;
            xmin = std::min(xmin, x);
            xmax = std::max(xmax, x);
            ymin = std::min(ymin, y);
            ymax = std::max(ymax, y);
        }

        return std::make_pair(xmax - xmin, ymax - ymin);
    };

    // s(t)を返す
    auto area = [&](lint t) {
        lint dx, dy;
        std::tie(dx, dy) = sim(t);
        return dx * dy;
    };

    lint ans = std::numeric_limits<lint>::max();

    for (int d = -2; d <= 2; ++d) {
        lint ok = 0, ng = INF;
        // okの左側傾き <= d

        // w_xの探索
        while (ng - ok > 1) {
            lint mid = (ok + ng) / 2;

            lint pdx, ndx;
            std::tie(pdx, std::ignore) = sim(mid - 1);
            std::tie(ndx, std::ignore) = sim(mid);

            (ndx - pdx <= d ? ok : ng) = mid;
        }
        ans = std::min(ans, area(ok));

        // w_yの探索
        ok = 0, ng = INF;
        while (ng - ok > 1) {
            lint mid = (ok + ng) / 2;

            lint pdy, ndy;
            std::tie(std::ignore, pdy) = sim(mid - 1);
            std::tie(std::ignore, ndy) = sim(mid);

            (ndy - pdy <= d ? ok : ng) = mid;
        }
        ans = std::min(ans, area(ok));
    }

    // 最後に4で割る
    std::cout << ans / 4
              << (ans % 4 == 0
                      ? ""
                      : ans % 4 == 1
                            ? ".25"
                            : ans % 4 == 2
                                  ? ".5"
                                  : ".75")
              << std::endl;
    return 0;
}
```

