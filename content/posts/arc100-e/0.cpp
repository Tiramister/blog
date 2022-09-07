#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> xs(1 << n);
  for (auto& x : xs) cin >> x;

  vector<vector<int>> dp(1 << n);
  int ans = 0;
  for (int s = 1; s < (1 << n); ++s) {
    auto& cands = dp[s];
    cands.push_back(0);
    cands.push_back(s);

    for (int i = 0; i < n; ++i) {
      if ((s >> i) & 1) {
        const auto& childs = dp[s ^ (1 << i)];
        cands.insert(cands.end(), childs.begin(), childs.end());
      }
    }

    // 重複を弾いてから2つに絞る
    sort(cands.begin(), cands.end(), [&](int i, int j){ return xs[i] > xs[j]; });
    cands.erase(unique(cands.begin(), cands.end()), cands.end());
    cands.resize(2);

    ans = max(ans, xs[cands[0]] + xs[cands[1]]);
    cout << ans << "\n";
  }

  return 0;
}
