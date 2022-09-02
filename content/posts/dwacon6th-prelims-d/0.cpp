#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), cnt(n, 0);
    for (auto& x : xs) {
        std::cin >> x;
        ++cnt[--x];
    }

    std::set<int> ss;
    for (int x = 0; x < n; ++x) ss.insert(x);
  	// まだ決まっていない数の集合

    std::vector<int> ans;
    ans.reserve(n);

    int out = -1;  // 直前の数に指されている数
    while (ss.size() > 3) {
        int x = *ss.begin();
        if (x == out) {
          	// 指されていたら次へ
            if (ss.size() == 1) {
                std::cout << -1 << std::endl;
                return 0;
            } else {
                x = *(++ss.begin());
            }
        }

        int k = ss.size();
        int y = xs[x];
        if (ss.count(y) && cnt[y] == k - 1) x = y;
      	// y以外がyを指している場合

        ss.erase(x);
        ans.push_back(x);
        --cnt[xs[x]];
        out = xs[x];
    }

  	// 最後の全探索
    std::vector<int> rem(ss.begin(), ss.end());
    do {
        auto tmpans = ans;
        for (auto x : rem) ans.push_back(x);

        bool ok = true;
        for (int i = 0; i < n - 1; ++i) {
            if (ans[i + 1] == xs[ans[i]]) ok = false;
        }

        if (ok) {
            for (auto x : ans) std::cout << x + 1 << " ";
            std::cout << std::endl;
            return 0;
        }

        ans = tmpans;
    } while (std::next_permutation(rem.begin(), rem.end()));

    std::cout << -1 << std::endl;
    return 0;
}
