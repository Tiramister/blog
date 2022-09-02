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
