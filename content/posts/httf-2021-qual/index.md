---
title: HACK TO THE FUTURE 2021 予選
date: 2020-11-08
tags: [atcoder, marathon]
---

[A - カードの回収](https://atcoder.jp/contests/future-contest-2021-qual/tasks/future_contest_2021_qual_a)

## 問題

$20 \times 20$ のグリッド上に、 $0 \sim 99$ が書かれたカードが 1 枚ずつ置かれている。

この上をロボットが移動する。ロボットはカードスタックを 1 つ持っており、以下のいずれかを毎ターン行える。

- 上下左右に隣接するマスへ移動する。
- 今いるマスにカードが置かれている場合、そのカードを拾う。
- 今いるマスにカードが置かれていない場合、カードスタックの一番上のカードをそのマスに置く。

最初ロボットは左上隅のマスにいて、カードスタックは空である。
底から $0 \sim 99$ の順番でカードスタックにカードが並ぶようにするとき、ロボットの移動回数を最小化せよ。

## 考察

### 基本方針

最初に考えていた方針が以下の 3 つ。

1.  $0 \sim 99$ の順に回収する。
2.  全回収してからカードを $10 \times 10$ にまとめて置き、順番に回収し直す。
3.  全回収 → 並べ直し → 再回収を $10$ 枚ずつ行う。

1 は期待値 $2000$ くらいなので却下、3 も 10 枚が散り散りだと最悪で実装も面倒そうなので却下。
というわけで、以降 2 の方針で突き進むことになる。

後は 2 のまとめて置くときの置き方だが、これはシンプルに蛇腹折りで固定した。
これには実装が簡単なこと以外にもう 1 つ理由があるが、それは後ほど述べる。

### 山登り法

2 に対して山登り法を用いるのだが、近傍状態は **回収順序の 2 点 swap** とした。
なぜこの近傍を選んだかと言うと、差分が爆速で計算できるためである。
というのも、差分を計算するためには選ばれたカードの前後しか見なくてよい。
先程蛇腹折りを採用したのも、差分計算を簡単にするためである。

ループ内の実装は以下のような感じで、差分計算に 10 行しか要していない。

```cpp
// don't choose 0 or N-1
int i = (rng.next() % (N - 2)) + 1,
    j = (rng.next() % (N - 2)) + 1;
if (i == j) continue;
if (vs[i] == 0 || vs[i] == N - 1 || vs[j] == 0 || vs[j] == N - 1) continue;

// calculate difference
int cost = 0;
cost -= dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
cost -= dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
cost -= dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
cost -= dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

std::swap(qs[vs[i]], qs[vs[j]]);
std::swap(vs[i], vs[j]);

cost += dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
cost += dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
cost += dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
cost += dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

if (cost > 0) {
    // reject
    std::swap(vs[i], vs[j]);
    std::swap(qs[vs[i]], qs[vs[j]]);
}
```

この方針で山登り法を実装すると、158,098 点が得られた(平均 838 ムーブ、95 位相当)。

### 焼きなまし法

この山登り法を焼きなまし法に変更するのだが、あいにく焼きなまし法をちゃんと実装したことがない。
時間は十分あったので調べた結果、 [この記事](http://gasin.hatenadiary.jp/entry/2019/09/03/162613) の実装を丸パクリすることにした。かなり分かりやすく実装が説明されていて助かった(ありがとうございます)。

そして焼きなまし法を実装した結果、162,838 点に伸びた(平均 743 ムーブ、46 位相当)。焼きなまし法すげー。

### ちょっと改善

最後に、全部回収する必要はないことに気づく。つまり最後に並べ直す領域を $[10, 19] \times [10, 19]$ とすると、この領域に最初から入っているカードは拾わなくても良い。

この改善を施して、初期解や温度を色々とイジってみた結果、最終的に 164,514 点まで伸びた(平均 710 ムーブ、24 位)。

## 実装

[提出 #17924564 - HACK TO THE FUTURE 2021 予選](https://atcoder.jp/contests/future-contest-2021-qual/submissions/17924564)

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <chrono>

using ldouble = float;

// ライブラリは割愛

constexpr int TL = 2980;
Timer timer;
Random rng;

constexpr int N = 100;
std::vector<std::pair<int, int>> ps(N);

int dist(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int score;
void move(int& x, int& y, int nx, int ny, bool output) {
    score += std::abs(x - nx) + std::abs(y - ny);
    if (!output) {
        x = nx, y = ny;
        return;
    }

    while (x < nx) {
        std::cout << 'D';
        ++x;
    }
    while (x > nx) {
        std::cout << 'U';
        --x;
    }
    while (y < ny) {
        std::cout << 'R';
        ++y;
    }
    while (y > ny) {
        std::cout << 'L';
        --y;
    }
}

std::vector<std::pair<int, int>> qs(N);

void output(const std::vector<int>& vs, bool output) {
    int x = 0, y = 0;
    std::vector<int> pile;

    for (auto v : vs) {
        auto [nx, ny] = ps[v];
        move(x, y, nx, ny, output);

        if (output) std::cout << 'I';
        pile.push_back(v);
    }

    move(x, y, 10, 10, output);

    auto next = [&]() {
        if (y % 2 == 0) {
            if (x < 19) {
                move(x, y, x + 1, y, output);
            } else {
                move(x, y, x, y + 1, output);
            }
        } else {
            if (x > 10) {
                move(x, y, x - 1, y, output);
            } else {
                move(x, y, x, y + 1, output);
            }
        }
    };

    std::vector<std::vector<bool>> grid(20, std::vector<bool>(20, false));
    for (auto [x, y] : ps) {
        if (x >= 10 && y >= 10) grid[x][y] = true;
    }

    while (!pile.empty()) {
        int v = pile.back();
        pile.pop_back();
        while (grid[x][y]) next();

        if (output) std::cout << 'O';
        qs[v] = {x, y};
        grid[x][y] = true;
    }

    int i = 0;
    for (auto [nx, ny] : qs) {
        if (nx == 0 && ny == 0) {
            std::cerr << i << "\n";
        }
        ++i;
        move(x, y, nx, ny, output);
        if (output) std::cout << 'I';
    }
}

// greedy
std::vector<int> initial() {
    std::vector<int> vs;
    std::vector<bool> used(N, false);

    int rem = N;
    for (int i = 0; i < N; ++i) {
        auto [x, y] = ps[i];
        if (x >= 10 && y >= 10) {
            used[i] = true;
            qs[i] = {x, y};
            --rem;
        }
    }

    std::pair<int, int> prev(0, 0);

    while (rem--) {
        int nxt = -1;
        for (int u = 0; u < N; ++u) {
            if (used[u]) continue;

            nxt = u;
            break;

            if (nxt == -1 || dist(prev, ps[u]) < dist(prev, ps[nxt])) {
                nxt = u;
            }
        }

        vs.push_back(nxt);
        used[nxt] = true;
        prev = ps[nxt];
    }

    return vs;
}

constexpr ldouble INIT_TEMP = 3;

void solve() {
    for (auto& [x, y] : ps) std::cin >> x >> y;

    auto vs = initial();
    int n = vs.size();

    // calculate score and qs
    score = 0;
    output(vs, false);
    int cur = score;

    int mincur = cur;
    auto minvs = vs;

    // simulated annealing
    int time = 0, mod = 0, sim = 0;
    auto temp = INIT_TEMP;

    while (time < TL) {
        if (++sim, ++mod == 100000) {
            time = timer.get_ms();
            temp = INIT_TEMP * (TL - time) / TL;
            mod = 0;
        }

        // don't choose 0 or n-1
        int i = (rng.next() % (n - 2)) + 1,
            j = (rng.next() % (n - 2)) + 1;
        if (vs[i] == 0 || vs[i] == N - 1 || vs[j] == 0 || vs[j] == N - 1) continue;
        if (i == j) continue;

        // calculate difference
        int cost = 0;
        cost -= dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
        cost -= dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
        cost -= dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
        cost -= dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

        std::swap(qs[vs[i]], qs[vs[j]]);
        std::swap(vs[i], vs[j]);

        cost += dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
        cost += dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
        cost += dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
        cost += dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

        if (rng.nextFloat() > std::exp(-cost / temp)) {
            // reject
            std::swap(vs[i], vs[j]);
            std::swap(qs[vs[i]], qs[vs[j]]);

        } else {
            cur += cost;
            if (cost == 0) continue;

            if (cur < mincur) {
                mincur = cur;
                minvs = vs;
            }
        }
    }

    output(minvs, true);
}
```

