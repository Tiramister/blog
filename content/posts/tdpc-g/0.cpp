#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using lint = long long;
constexpr lint INF = 1LL << 60;

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    auto next = vec(26, n);
    auto dp = vec(26, vec(n + 1, 0LL));

    for (int i = n - 1; i >= 0; --i) {
        next[s[i] - 'a'] = i;

        for (int c = 0; c < 26; ++c) {
            int j = next[c];
            if (j == n) continue;

            dp[c][i] = 1;
            for (int d = 0; d < 26; ++d) {
                dp[c][i] = std::min(dp[c][i] + dp[d][j + 1], INF);
            }
        }
    }

    lint k;
    std::cin >> k;
    --k;

    int idx = 0;
    while (idx < n) {
        int c;
        for (c = 0; c < 26; ++c) {
            if (dp[c][idx] <= k) {
                // 先頭cにk番目はないのでパス
                k -= dp[c][idx];

            } else {
                std::cout << char(c + 'a');

                while (s[idx] != c + 'a') ++idx;
                ++idx;

                --k;  // empty string
                break;
            }
        }

        if (k < 0) {
            std::cout << std::endl;
            break;
        }

        if (c == 26) {
            // k番目はなし
            std::cout << "Eel" << std::endl;
            break;
        }
    }
}
