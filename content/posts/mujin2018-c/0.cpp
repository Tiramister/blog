#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
using V = vector<T>;
using ll = long long;

#define FOR(i, a, b) for (ll i = (a); i <= (b); i++)

/* ---------- ここまでマクロ ---------- */

const ll dx[4] = {0, -1, 0, 1};
const ll dy[4] = {-1, 0, 1, 0};
const ll MAX = 2018;

ll N, M;
V<string> S(MAX);
V<V<V<ll>>> dp(MAX, V<V<ll>>(MAX, V<ll>(4, -1)));
// dp[x][y][i] = (x, y)中心で(dx[i], dy[i])方向の
//               突き当たりまでのマス数
// (x, y)が未探索or壁なら-1

// (x, y)を始点として、方向(dx[i], dy[i])に突き進む
ll dfs(ll x, ll y, ll i) {

    // 再探索防止
    if (dp[x][y][i] >= 0) return dp[x][y][i];

    // 1つ進んだマス(nx, ny)を探索
    ll nx = x + dx[i];
    ll ny = y + dy[i];

    if (nx < 0 || nx >= N || ny < 0 || ny >= M || S[nx][ny] != '.') {
        // (nx, ny)は突き当たりなのでマス数は0
        dp[x][y][i] = 0;
    } else {
        // 探索続行
        dp[x][y][i] = dfs(nx, ny, i) + 1;
    }

    return dp[x][y][i];
}


int main() {
    // 初期化
    cin >> N >> M;
    FOR(i, 0, N - 1) {
        cin >> S[i];
    }

    // 方向(dx[i], dy[i])、中継点(x, y)
    FOR(i, 0, 3) {
        FOR(x, 0, N - 1) {
            FOR(y, 0, M - 1) {
                if (S[x][y] == '.') {
                    // (x, y)を起点にdpテーブルを埋める
                    dfs(x, y, i);
                }
            }
        }
    }

    // 探索結果を集計
    ll ans = 0;
    FOR(x, 0, N - 1) {
        FOR(y, 0, M - 1) {
            if (S[x][y] == '.') {
                // (U + D) * (L + R)を加算
                ans += (dp[x][y][0] + dp[x][y][2]) * (dp[x][y][1] + dp[x][y][3]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
