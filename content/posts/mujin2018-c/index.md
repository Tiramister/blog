---
title: "Mujin Programming Challenge 2018 C - 右折"
date: 2018-08-05
tags: [atcoder]
---

[C - 右折](https://atcoder.jp/contests/mujin-pc-2018/tasks/mujin_pc_2018_c)

## 概要

所々壁になっている $N \\times M$ の盤面が与えられる。

このとき、始点から 1 マス以上直進して中継点で右に 90 度ターンし、また 1 マス以上直進して終点へ着く、という経路が存在する始点と終点の組は全部で何通り考えられるか。

## 制約

- $2 \\leq N, M \\leq 2 \\times 10\^3$
- $s\_\{ij\}$ はマス $(i, j)$ が壁なら `#` 、何もないなら `.`

### 解説

超簡単に言えば、「 `#` を通らない L 字は盤面上にいくつあるか？」ということである。

ここで注目すべきは、始点でも終点でもなく **中継点** である。

{{<image src="0.png">}}

上のように、「中継点」と「方向」さえ決めれば、突き当たりまでのマス数の積で経路数が求められる。
具体的には、上下左右の突き当たりまでのマス数をそれぞれ $U, D, L, R$ とすると、そのマスを中継点とする経路の総数は以下で求められる。

$$
UL + LD + DR + RU = (U + D)(L + R)
$$

後は各マスについて $U, D, L, R$ を求めればいいのだが、愚直に突き当たるまで探索すると $O(NM(N + M))$ くらいの計算量になってしまう。
この計算量削減には色々な方法があるが、私はメモ化することで再計算を防ぐことにした。

## 解答例

[提出 #2946983 - Mujin Programming Challenge 2018](https://atcoder.jp/contests/mujin-pc-2018/submissions/2946983)

```cpp
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
```

