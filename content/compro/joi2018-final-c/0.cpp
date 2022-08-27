#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

constexpr int INF = 1 << 30;

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> ss(n);
    for (auto& s : ss) std::cin >> s;

    // (x, y)から(t ? 横 : 縦)に取れるか判定
    auto judge = [&](int x, int y, int t) {
        if (t == 0) {
            for (int dx = 0; dx < 3; ++dx) {
                int nx = x + dx,
                    ny = y;
                if (nx < 0 || n <= nx || ny < 0 || m <= ny ||
                    ss[nx][ny] != "RGW"[dx]) return false;
            }
        } else {
            for (int dy = 0; dy < 3; ++dy) {
                int nx = x,
                    ny = y + dy;
                if (nx < 0 || n <= nx || ny < 0 || m <= ny ||
                    ss[nx][ny] != "RGW"[dy]) return false;
            }
        }
        return true;
    };

    int ans = 0;
    auto dp = vec(2, vec(2, 0));
    auto ndp = dp;

    // (sx, 0)から斜め上に見る
    for (int sx = 0; sx < n + m; ++sx) {
        for (int t1 = 0; t1 <= 1; ++t1) {
            for (int t2 = 0; t2 <= 1; ++t2) {
                dp[t1][t2] = -INF;
            }
        }
        dp[0][0] = 0;

        for (int y = 0; y <= m + 1; ++y) {
            int x = sx - y;

            for (int t1 = 0; t1 <= 1; ++t1) {
                for (int t2 = 0; t2 <= 1; ++t2) {
                    ndp[t1][t2] = -INF;
                }
            }

            for (int t1 = 0; t1 <= 1; ++t1) {
                for (int t2 = 0; t2 <= 1; ++t2) {
                    // 取らない
                    ndp[t2][0] = std::max(ndp[t2][0], dp[t1][t2]);

                    // 縦に取る
                    if (!t1 && !t2 && judge(x, y, 0)) {
                        ndp[t2][0] = std::max(ndp[t2][0], dp[t1][t2] + 1);
                    }

                    // 横に取る
                    if (judge(x, y, 1)) {
                        ndp[t2][1] = std::max(ndp[t2][1], dp[t1][t2] + 1);
                    }
                }
            }
            std::swap(dp, ndp);
        }
        ans += dp[0][0];  // yを2だけ余分にカウントすることでdp[0][0]に集約している
    }
    std::cout << ans << std::endl;
}
