#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int INF = 1 << 30;

int main() {
  int n, m;
  cin >> n >> m;

  // 最後にオーバーランするために、 m + 2 まで含める
  vector<int> cnt(m + 2, 0);
  while (n--) {
    int a;
    cin >> a;
    ++cnt[--a];  // 0-indexedに変換
  }

  // 前2つの枚数を持つ
  auto dp = vector(7, vector(7, -INF));
  dp[0][0] = 0;

  for (auto c : cnt) {
    auto ndp = vector(7, vector(7, -INF));

    for (int p = 0; p <= 6; ++p) {
      for (int q = 0; q <= 6; ++q) {
        // 以降のために残す枚数
        for (int r = 0; r <= min(c, 6); ++r) {
          for (int shuntsu = 0; shuntsu <= min({p, q, c - r}); ++shuntsu) {
            int kotsu = (c - r - shuntsu) / 3;  // 作れる刻子の数
            ndp[q - shuntsu][r] = max(ndp[q - shuntsu][r], dp[p][q] + shuntsu + kotsu);
          }
        }
      }
    }

    swap(dp, ndp);
  }

  cout << dp[0][0] << endl;
  return 0;
}
