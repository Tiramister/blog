#include <iostream>
#include <map>

using namespace std;
using ll = long long;

const ll MOD = 1000000007;

map<ll, ll> dp;

// v=0,1,...,Mにおける解の合計
ll rec(ll M) {
    if (M == 0) return 1;
    if (dp.count(M)) return dp[M];

    dp[M] = rec((M - 1) / 2);            // 奇数
    dp[M] += rec(M / 2);                 // 偶数 繰り上がり無
    if (M > 1) dp[M] += rec(M / 2 - 1);  // 偶数 繰り上がり有
    return dp[M] %= MOD;
}

int main() {
    ll N;
    cin >> N;
    cout << rec(N) << endl;
    return 0;
}
