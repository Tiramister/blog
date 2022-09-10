#include <iostream>
using namespace std;
using ll = long long;
const ll INF = 1LL << 60;

int main() {
    ll N, X;
    cin >> N >> X;

    ll sum[N + 1];
    sum[0] = 0;
    for (int i = 1; i <= N; ++i) {
        ll x;
        cin >> x;
        sum[i] = sum[i - 1] + x;
    }

    ll ans = INF;
    for (ll t = 1; t <= N; ++t) {
        // ゴミ捨てとゴミ拾いに消費するエネルギー
        ll cost = (N + t) * X;

        ll now = N;  // 右端

        cost += sum[now] * 5;
        now -= t * 2;
        while (now > 0) {
            cost += sum[now] * 2;
            now -= t;

            // オーバーフロー対策
            if (cost < 0) {
                cost = INF;
                break;
            }
        }
        ans = min(ans, cost);
    }

    cout << ans << endl;
    return 0;
}
