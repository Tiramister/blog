#include <algorithm>
#include <iostream>

using namespace std;

using ll = long long;

ll N;
ll A[200010], sum[200010];
// 入力の数列と、その累積和(1-indexed)

// (A_b, ..., A_e)を大体半分にカットし、前半と後半の総和を返す
pair<ll, ll> divide(ll b, ll e) {
    ll ok = b, ng = e;
    ll ds = sum[e] - sum[b - 1];

    // 二分探索で真ん中ちょい手前を探る
    while (ng - ok > 1) {
        ll mid = (ok + ng) / 2;
        ll ps = sum[mid] - sum[b - 1];
        if (ps * 2 <= ds) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    // ちょっと手前で切った場合の値
    pair<ll, ll> former = make_pair(sum[ok] - sum[b - 1], sum[e] - sum[ok]);

    // ちょっと後ろで切った場合の値
    pair<ll, ll> later = make_pair(sum[ok + 1] - sum[b - 1], sum[e] - sum[ok + 1]);

    // より差の小さい方を選ぶ
    if (abs(former.first - former.second) < abs(later.first - later.second)) {
        return former;
    } else {
        return later;
    }
}

// Aを[0, itr]と(itr, N)で切ったときの解を返す
ll cut(ll itr) {
    pair<ll, ll> res[2] = {divide(1, itr), divide(itr + 1, N)};

    ll elem[4];
    for (ll i = 0; i < 2; ++i) {
        elem[i * 2] = res[i].first;
        elem[i * 2 + 1] = res[i].second;
    }

    sort(elem, elem + 4);
    return elem[3] - elem[0];
}

int main() {
    cin >> N;
    sum[0] = 0;
    for (ll i = 1; i <= N; ++i) {
        cin >> A[i];
        sum[i] = sum[i - 1] + A[i];
    }

    ll ans = sum[N];
    for (ll i = 2; i < N; ++i) {
        ans = min(ans, cut(i));
    }

    cout << ans << endl;
    return 0;
}
