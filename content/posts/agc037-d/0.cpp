#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

template <class Cap, bool isDirect>
struct MaxFlow { ... };
struct BiMatching { ... };

template <class T>
std::vector<T> vec(int len, T elem) { ... }

void solve() {
    int n, m;
    std::cin >> n >> m;

    auto nums = vec(n, vec(n, vec(0, 0)));
    // 行iが持っている色cの数の集合
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a;
            std::cin >> a;
            nums[i][(a - 1) / m].push_back(a);
        }
    }

    auto bs = vec(n, vec(m, 0));
    for (int j = 0; j < m; ++j) {
        // 二部グラフを構築
        BiMatching bm(n, n);
        for (int i = 0; i < n; ++i) {
            for (int c = 0; c < n; ++c) {
                if (nums[i][c].empty()) continue;
                bm.span(i, c);
            }
        }

        // マッチングを元に割り付け
        auto res = bm.matching();
        for (auto p : res) {
            int i, c;
            std::tie(i, c) = p;
            bs[i][j] = nums[i][c].back();
            nums[i][c].pop_back();
        }
    }

    for (auto& v : bs) {
        for (auto b : v) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // 各行から該当する色の数を探す
            for (int k = 0; k < n; ++k) {
                if ((bs[k][j] - 1) / m == i) {
                    std::cout << bs[k][j] << " ";
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
}
