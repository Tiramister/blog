#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    auto dp = vec(n, vec(n, 0));
    auto clean = vec(n, vec(n, false));
    for (int i = 1; i < n; ++i) {
        clean[i][i - 1] = true;
    }

    for (int l = 0; l < n; ++l) {
        for (int i = 0; i + l < n; ++i) {
            int j = i + l;

            // clean check
            // create iwi
            if (s[i] == 'i' && s[j] == 'i') {
                for (int k = i + 1; k <= j - 1; ++k) {
                    if (s[k] == 'w' &&
                        clean[i + 1][k - 1] && clean[k + 1][j - 1]) {
                        clean[i][j] = true;
                    }
                }
            }
            // separate
            for (int k = i; k + 1 <= j; ++k) {
                if (clean[i][k] && clean[k + 1][j]) clean[i][j] = true;
            }

            if (clean[i][j]) dp[i][j] = (l + 1) / 3;

            for (int k = i; k + 1 <= j; ++k) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    std::cout << dp[0][n - 1] << std::endl;
}
