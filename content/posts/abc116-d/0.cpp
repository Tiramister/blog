#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using lint = long long;

int main() {
  int n, k;
  cin >> n >> k;

  vector<pair<lint, int>> ps(n);
  for (auto& [d, t] : ps) {
    cin >> t >> d;
    --t;
  }
  sort(ps.rbegin(), ps.rend());

  vector<int> cnt(n, 0);
  lint sum = 0, kind = 0;
  for (int i = 0; i < k; ++i) {
    auto [d, t] = ps[i];
    sum += d;

    if (cnt[t] == 0) ++kind;
    ++cnt[t];
  }

  lint ans = sum + kind * kind;

  int l = k - 1, r = k;
  while (true) {
    // 減らす
    bool chosen = false;
    while (l >= 0) {
      auto [d, t] = ps[l--];

      // 種類数を減らさないように
      if (cnt[t] == 1) continue;

      sum -= d;
      --cnt[t];
      chosen = true;
      break;
    }
    if (!chosen) break;

    // 増やす
    chosen = false;
    while (r < n) {
      auto [d, t] = ps[r++];

      // 種類数が増えないならスルー
      if (cnt[t] != 0) continue;

      sum += d;
      ++cnt[t];
      ++kind;
      chosen = true;
      break;
    }
    if (!chosen) break;

    ans = max(ans, sum + kind * kind);
  }

  cout << ans << endl;
  return 0;
}
