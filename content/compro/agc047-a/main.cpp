#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    auto cnt = vec(19, vec(19, 0LL));
    // cnt[t][f] = 2^t 5^fで割り切れるものの個数
    // ただしt, f > 18のときはt, f = 18として扱う

    while (n--) {
        std::string s;
        std::cin >> s;

        std::string g;  // 小数点以下を取り出したもの
        if (std::count(s.begin(), s.end(), '.') != 0) {
            while (s.back() != '.') {
                g.push_back(s.back());
                s.pop_back();
            }
            s.pop_back();
            std::reverse(g.begin(), g.end());
        }
        while ((int)g.length() < 9) g.push_back('0');

        // 整数に変換
        lint x = std::stoi(s) * 1000000000LL + std::stoi(g);

        // t, fを求める
        int t = 0;
        while (x % 2 == 0 && t < 18) {
            x /= 2;
            ++t;
        }

        int f = 0;
        while (x % 5 == 0 && f < 18) {
            x /= 5;
            ++f;
        }

        ++cnt[t][f];
    }

    lint ans = 0;
    for (int t1 = 0; t1 <= 18; ++t1) {
        for (int f1 = 0; f1 <= 18; ++f1) {
            for (int t2 = 0; t2 <= 18; ++t2) {
                for (int f2 = 0; f2 <= 18; ++f2) {
                    // 条件チェック
                    if (t1 + t2 < 18 || f1 + f2 < 18) continue;

                    if (t1 == t2 && f1 == f2) {
                        ans += cnt[t1][f1] * (cnt[t1][f1] - 1);
                    } else {
                        ans += cnt[t1][f1] * cnt[t2][f2];
                    }
                }
            }
        }
    }

    // ダブりを除く
    ans /= 2;
    std::cout << ans << "\n";
}
