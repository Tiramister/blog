#include <atcoder/modint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using mint = atcoder::modint998244353;

void solve() {
    string s;
    int m;
    cin >> s >> m;
    int n = s.length();

    auto dp = vector(2, vector(n + 1, vector(n + 1, vector(n + 1, mint(0)))));
    // Tの次の文字, Sの今見てるindex, 1の前借り数, 操作回数
    dp[0][0][0][0] = dp[1][0][0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k) {
                if (s[i] == '0') {
                    // 0-0: スキップ
                    if (i < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i + 1][j][k] += dp[0][i][j][k];
                        }
                    }

                    // 0-1: 1を貰う
                    if (j < n && k < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i][j + 1][k + 1] += dp[1][i][j][k];
                        }
                    }
                } else {
                    // 1-0: 1を消す
                    // このときだけ相手の文字は0のまま
                    if (i < n && j > 0) {
                        dp[0][i + 1][j - 1][k] += dp[0][i][j][k];
                    }

                    // 1-1: スキップ
                    if (i < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i + 1][j][k] += dp[1][i][j][k];
                        }
                    }
                }
            }
        }
    }

    mint ans = 0;
    for (int k = 0; k <= n && k <= m; ++k) {
        ans += dp[0][n][0][k];
    }
    cout << ans.val() << "\n";
}
