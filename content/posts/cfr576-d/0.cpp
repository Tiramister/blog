#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

int n;
std::vector<std::vector<std::vector<bool>>> remp, cemp;

int dfs(int lx, int ly, int rx, int ry) {
    if (rx < lx || ry < ly) return 0;

    static auto dp = vec(n, vec(n, vec(n, vec(n, -1))));
    auto& ret = dp[lx][ly][rx][ry];
    if (ret >= 0) return ret;

    ret = std::max(rx - lx + 1, ry - ly + 1);

    // 行で分割
    for (int x = lx; x <= rx; ++x) {
        if (!remp[x][ly][ry]) continue;
        int sum = dfs(lx, ly, x - 1, ry) +
                  dfs(x + 1, ly, rx, ry);
        ret = std::min(ret, sum);
    }

    // 列で分割
    for (int y = ly; y <= ry; ++y) {
        if (!cemp[lx][rx][y]) continue;
        int sum = dfs(lx, ly, rx, y - 1) +
                  dfs(lx, y + 1, rx, ry);
        ret = std::min(ret, sum);
    }

    return ret;
};

void solve() {
    std::cin >> n;

    std::vector<std::string> ss(n);
    for (auto& s : ss) std::cin >> s;

    // 白行の判定
    remp = vec(n, vec(n, vec(n, false)));
    for (int x = 0; x < n; ++x) {
        for (int ly = 0; ly < n; ++ly) {
            remp[x][ly][ly] = (ss[x][ly] == '.');
            for (int ry = ly + 1; ry < n; ++ry) {
                remp[x][ly][ry] =
                    remp[x][ly][ry - 1] && (ss[x][ry] == '.');
            }
        }
    }

    // 白列の判定
    cemp = remp;
    for (int y = 0; y < n; ++y) {
        for (int lx = 0; lx < n; ++lx) {
            cemp[lx][lx][y] = (ss[lx][y] == '.');
            for (int rx = lx + 1; rx < n; ++rx) {
                cemp[lx][rx][y] =
                    cemp[lx][rx - 1][y] && (ss[rx][y] == '.');
            }
        }
    }

    std::cout << dfs(0, 0, n - 1, n - 1) << std::endl;
}
