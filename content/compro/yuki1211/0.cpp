#include <iostream>
#include <numeric>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { ... }

using lint = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    // スキップリスト
    auto to = vec(20, vec(n, 0LL));

    lint ok = 0,
         ng = std::accumulate(xs.begin(), xs.end(), 0LL) + 1;
    while (ng - ok > 1) {
        lint mid = (ok + ng) / 2;

        {
            // 尺取法でd_iを計算
            int r = 0;
            lint sum = 0;
            for (int l = 0; l < n; ++l) {
                while (sum < mid) {
                    sum += xs[r % n];
                    ++r;
                }
                to[0][l] = r - l;
                sum -= xs[l];
            }
        }

        // スキップリストを埋める
        for (int d = 0; d + 1 < 20; ++d) {
            for (int i = 0; i < n; ++i) {
                to[d + 1][i] = to[d][i] + to[d][(i + to[d][i]) % n];
            }
        }

        bool judge = false;
        for (int s = 0; s < n; ++s) {
            // sを始点とした場合をシミュレーション
            int v = s;
            lint sum = 0;

            for (int d = 0; d < 20; ++d) {
                if ((~k >> d) & 1) continue;
                sum += to[d][v];
                (v += to[d][v]) %= n;
            }

            if (sum <= n) judge = true;
        }

        if (judge) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    std::cout << ok << "\n";
}
