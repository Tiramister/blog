#include <atcoder/modint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using mint = atcoder::modint998244353;

int main() {
  string s;
  cin >> s;
  int n = s.length();

  // 各ボールの個数の累積和
  vector<int> rsum(n * 2 + 1), bsum(n * 2 + 1);
  rsum[0] = bsum[0] = 0;

  for (int i = 0; i < n; ++i) {
    int b = s[i] - '0';
    rsum[i + 1] = rsum[i] + 2 - b;
    bsum[i + 1] = bsum[i] + b;
  }
  for (int i = n; i < n * 2; ++i) {
    rsum[i + 1] = rsum[i];
    bsum[i + 1] = bsum[i];
  }

  auto dp = vector(rsum[n] + 1, vector(bsum[n] + 1, mint(0)));
  dp[0][0] = 1;
  for (int r = 0; r <= rsum[n]; ++r) {
    for (int b = 0; b <= bsum[n]; ++b) {
      if (r + b == n * 2) continue;

      // 赤ボールを置けるか？
      if (rsum[r + b + 1] > r) dp[r + 1][b] += dp[r][b];
      // 青ボールを置けるか？
      if (bsum[r + b + 1] > b) dp[r][b + 1] += dp[r][b];
    }
  }

  cout << dp[rsum[n]][bsum[n]].val() << "\n";
  return 0;
}
