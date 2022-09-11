#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
using GPQ = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;

#define mp make_pair
#define SORT(v) sort((v).begin(), (v).end())
#define GSORT(v) sort((v).begin(), (v).end(), greater<decltype((v).front())>())
#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)

int main() {
    // X, Y, Zを受け取る
    // N = X + Y + Z
    ll X[3], N = 0;
    FOR(j, 0, 3) {
        cin >> X[j];
        N += X[j];
    }

    // A_i, B_i, C_iを受け取る
    vector<vector<ll>> coin(N, vector<ll>(3, 0));
    FOR(i, 0, N) {
        FOR(j, 0, 3) {
            cin >> coin[i][j];
        }
    }

    // (gold - silver, index)の配列
    vector<pair<ll, ll>> gs(N);
    FOR(i, 0, N) {
        gs[i] = make_pair(coin[i][0] - coin[i][1], i);
    }

    SORT(gs);

    // silver[i] = 「K = Y + iにおける
    //              左グループのコイン枚数の最大値」
    vector<ll> silver(X[2] + 1, 0);

    // 中身は(silver - bronze, index)
    GPQ<pair<ll, ll>> sb;

    // まずは最初のY個を追加してしまう
    FOR(i, 0, X[1]) {
        ll id = gs[i].second;
        sb.push(make_pair(coin[id][1] - coin[id][2], id));
        silver[0] += coin[id][1];
    }

    // ここから銅の人が出始める
    FOR(i, 0, X[2]) {
        ll id = gs[i + X[1]].second;
        sb.push(mp(coin[id][1] - coin[id][2], id));

        silver[i + 1] = silver[i] + coin[id][1];

        // 先頭の人を銀の人から銅の人に変える
        auto p = sb.top();
        sb.pop();
        silver[i + 1] += (coin[p.second][2] - coin[p.second][1]);
    }

    // 逆順にして(gold - bronze)で全く同じことをする
    GSORT(gs);

    vector<ll> gold(X[2] + 1, 0);
    GPQ<pair<ll, ll>> gb;
    FOR(i, 0, X[0]) {
        ll id = gs[i].second;
        gb.push(mp(coin[id][0] - coin[id][2], id));
        gold[0] += coin[id][0];
    }

    FOR(i, 0, X[2]) {
        ll id = gs[i + X[0]].second;
        gb.push(mp(coin[id][0] - coin[id][2], id));

        gold[i + 1] = gold[i] + coin[id][0];

        auto p = gb.top();
        gb.pop();
        gold[i + 1] += (coin[p.second][2] - coin[p.second][0]);
    }

    ll ans = 0;
    FOR(i, 0, X[2] + 1) {
        // K = Y + iにおけるコインの合計枚数と比較
        ans = max(ans, silver[i] + gold[X[2] - i]);
    }

    cout << ans << endl;
    return 0;
}
