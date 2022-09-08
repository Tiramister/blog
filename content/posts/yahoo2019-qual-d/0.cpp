#include <iostream>
#include <vector>

using namespace std;
using lint = long long;

const lint INF = 1LL << 50;

lint f(int k, lint a) {
  if (k == 2) {
    // 奇数の区間
    return (a + 1) % 2;
  } else if (k == 1 || k == 3) {
    // 偶数の区間
    // 0個は許されないことに注意
    return (a == 0 ? 2 : a % 2);
  } else {
    // 無の区間
    return a;
  }
}

int main() {
  int n;
  cin >> n;

  vector<lint> xs(n);
  for (auto& x : xs) cin >> x;

  vector<lint> dp(5, 0);
  for (auto x : xs) {
    // index を進める
    for (int k = 0; k < 5; ++k) dp[k] += f(k, x);
    // 区間変更
    for (int k = 1; k < 5; ++k) dp[k] = min(dp[k], dp[k - 1]);
  }

  cout << dp[4] << endl;
  return 0;
}
