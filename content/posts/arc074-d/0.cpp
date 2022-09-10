#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

using ll = long long;
template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;

const ll INF = 1LL << 50;

int main() {
    ll N;
    cin >> N;
    ll a[N * 3 + 1];
    for (int i = 1; i <= N * 3; ++i) {
        cin >> a[i];
    }

    ll red[N * 2 + 1];
    red[0] = 0;
    // red[i] = 前半i個からN個選んだ総和の最大値

    GPQ<ll> rque;
    // 大きい方からN個を保持

    for (int i = 1; i <= N; ++i) {
        red[i] = red[i - 1] + a[i];
        rque.push(a[i]);
    }

    // ここから小さいのが切り捨てられる
    for (int i = N + 1; i <= N * 2; ++i) {
        red[i] = red[i - 1] + a[i];
        rque.push(a[i]);
        red[i] -= rque.top();
        rque.pop();
    }

    // aをひっくり返して同じことをする
    reverse(a + 1, a + N * 3 + 1);

    ll blue[N * 2 + 1];
    blue[0] = 0;
    // blue[i] = 後半i個からN個選んだ総和の最小値

    PQ<ll> bque;
    // 小さい方からN個を保持

    for (int i = 1; i <= N; ++i) {
        blue[i] = blue[i - 1] + a[i];
        bque.push(a[i]);
    }

    for (int i = N + 1; i <= N * 2; ++i) {
        blue[i] = blue[i - 1] + a[i];
        bque.push(a[i]);
        blue[i] -= bque.top();
        bque.pop();
    }

    ll ans = -INF;
    for (int i = N; i <= N * 2; ++i) {
        // 前半i個、後半3N - i個の差
        ans = max(ans, red[i] - blue[N * 3 - i]);
    }

    cout << ans << endl;
    return 0;
}
