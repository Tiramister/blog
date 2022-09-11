#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> path[100010];
int d[100010];
// 各頂点を0と1で塗り分ける

// 二部グラフならtrue
bool dfs(ll v, ll t) {
    if (d[v] >= 0) {
        return t == d[v];
    }

    d[v] = t;
    bool ret = true;
    for (ll sv : path[v]) {
        ret &= dfs(sv, 1 - t);
    }

    return ret;
}

int main() {
    ll N, M;
    cin >> N >> M;

    for (ll i = 0; i < M; ++i) {
        ll a, b;
        cin >> a >> b;
        --a;
        --b;
        path[a].push_back(b);
        path[b].push_back(a);
    }

    // 未探索なら-1
    fill(d, d + N, -1);

    ll even = 0, odd = 0, one = 0;
    // 二部グラフ、二部グラフでない連結成分と孤立点の数

    for (ll v = 0; v < N; ++v) {
        // 探索済みならパス
        if (d[v] >= 0) continue;

        // 孤立点判定
        if (path[v].empty()) {
            ++one;
            continue;
        }

        // 二部グラフ判定
        if (dfs(v, 0)) {
            ++even;
        } else {
            ++odd;
        }
    }

    cout << N * N - (N - one) * (N - one) + (odd + even) * (odd + even) + even * even << endl;
    return 0;
}
