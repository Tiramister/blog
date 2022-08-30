#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;

void solve() {
    int n, k;
    lint m;
    std::cin >> n >> k >> m;

    // (a_i, i)
    std::vector<std::pair<int, int>> ps(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> ps[i].first;
        ps[i].second = i;
    }

    // ソートして座圧
    std::sort(ps.begin(), ps.end());
    std::vector<int> ord(n);
    for (int j = 0; j < n; ++j) {
        ord[ps[j].second] = j;
    }

    int ok = n, ng = 0;
    // ok以下がk番目になる部分列の個数>=m
    while (ok - ng > 1) {
        int mid = (ok + ng) / 2;

        lint sum = 0;
        int cnt = 0, r = -1;
        // 尺取り法 区間[l, r]を見ている
        for (int l = 0; l < n; ++l) {
            while (r < n && cnt < k) {
                ++r;
                if (r < n && ord[r] <= mid) ++cnt;
            }
            sum += n - r;
            if (ord[l] <= mid) --cnt;
        }

        (sum >= m ? ok : ng) = mid;
    }

    std::cout << ps[ok].first << std::endl;
}
