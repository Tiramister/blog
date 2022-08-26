#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <queue>
#include <functional>

template <int K, class T>
struct PatternsMatching { ... };

int x;
std::vector<std::string> ps;  // 禁止文字列

// 禁止文字列判定
bool judge(const std::string& t) {
    int n = t.length();
    for (int l = 0; l < n; ++l) {
        int sum = 0;
        for (int r = l; r < n; ++r) {
            sum += t[r] - '0';
            if (sum != x && x % sum == 0) return true;
        }
    }
    return false;
}

// 総和x以下の文字列を全探索
void dfs(std::string& t, int dsum) {
    if (dsum == x && !judge(t)) ps.push_back(t);

    for (int d = 1; d <= 9 && dsum + d <= x; ++d) {
        t.push_back(d + '0');
        dfs(t, dsum + d);
        t.pop_back();
    }
}

constexpr int INF = 1 << 30;

void solve() {
    std::string s;
    std::cin >> s >> x;

    // 禁止文字列列挙
    {
        std::string tmp;
        dfs(tmp, 0);
    }

    // Trieを構築
    PatternsMatching<9, char> pm('1');
    for (const auto& p : ps) pm.add(p);
    pm.build();

    int n = pm.nodes.size();

    // Trie上のindex、消した文字数
    std::vector<int> dp(n, INF);
    dp[0] = 0;

    for (char c : s) {
        std::vector<int> ndp(n, INF);

        for (int pos = 0; pos < n; ++pos) {
            ndp[pos] = std::min(ndp[pos], dp[pos] + 1);

            int npos = pm.next(pos, pm.enc(c));
            if (!pm[npos].matched) {
                ndp[npos] = std::min(ndp[npos], dp[pos]);
            }
        }

        std::swap(dp, ndp);
    }

    std::cout << *std::min_element(dp.begin(), dp.end()) << "\n";
}
