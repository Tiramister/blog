---
title: "AtCoder Regular Contest 012 C - 五目並べチェッカー"
date: 2019-10-28
tags: [atcoder]
---

[C - 五目並べチェッカー](https://atcoder.jp/contests/arc012/tasks/arc012_3)

## 問題

$19 \\times 19$ の黒石と白石が置かれた盤面が与えられるので，
それが五目並べの盤面として妥当か判定せよ．
ただし黒石が先手とする．

## 考察

極力実装が楽なように問題の条件を言い換えた結果，以下のような判定方法にたどり着いた．

- まず石の個数の差から，その盤面が valid かどうか判定する．
  - valid かつ、どちらも五目揃っていなければ対戦中なので OK．
- どちらかが揃っている場合， **その一手前では揃っていない** ．よって全ての碁石に対して，それを取り除いた盤面が対戦中のものか調べる。
  - もしそのような石がなければ，揃った上でもう一手打っているので NG．

## 実装例

[提出 #8186625 - AtCoder Regular Contest 012](https://atcoder.jp/contests/arc012/submissions/8186625)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>

// 離脱用関数
void fail() {
    std::cout << "NO" << std::endl;
    std::exit(0);
}

void success() {
    std::cout << "YES" << std::endl;
    std::exit(0);
}

using Board = std::vector<std::string>;
constexpr int N = 19;

bool inrange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

constexpr int D = 8;
constexpr std::array<int, D>
    dx{-1, -1, -1, 0, 0, 1, 1, 1},
    dy{-1, 0, 1, -1, 1, -1, 0, 1};

// 石の個数を数える
std::pair<int, int> count(const Board& brd) {
    auto ret = std::make_pair(0, 0);
    for (const auto& s : brd) {
        ret.first += std::count(s.begin(), s.end(), 'o');
        ret.second += std::count(s.begin(), s.end(), 'x');
    }
    return ret;
}

// 石の個数がvalidか判定
bool valid(const Board& brd) {
    auto cnt = count(brd);
    return (cnt.second <= cnt.first && cnt.first <= cnt.second + 1);
}

// 五目揃っているか判定
bool finished(const Board& brd) {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            char c = brd[x][y];
            if (c == '.') continue;

            for (int d = 0; d < D; ++d) {
                int chain = 0;
                int nx = x, ny = y;

                while (inrange(nx, ny) && brd[nx][ny] == c) {
                    ++chain;
                    nx += dx[d];
                    ny += dy[d];
                }

                if (chain >= 5) return true;
            }
        }
    }
    return false;
}

int main() {
    Board brd(N);
    for (auto& b : brd) std::cin >> b;

    if (!valid(brd)) fail();
    if (!finished(brd)) success();

    for (auto& s : brd) {
        for (auto& c : s) {
            char prev = c;
            c = '.';

            if (valid(brd) && !finished(brd)) success();
            c = prev;
        }
    }

    fail();
    return 0;
}
```

