---
title: AtCoder Grand Contest 046 C - Shift
date: 2020-11-28
tags: [atcoder]
---

[C - Shift](https://atcoder.jp/contests/agc046/tasks/agc046_c)

## 問題

$0, 1$ からなる長さ $N$ の文字列 $S$ が与えられる。 $S$ に以下の操作を $K$ 回以下行ってできる文字列の数を求めよ。

- $S\_i = 0, S\_j = 1$ かつ $i \\lt j$ なる $i, j$ を選ぶ。
- $S\_j$ を削除し、 $S\_i$ の前に $1$ を挿入する。

### 制約

- $1 \\leq N \\leq 300$
- $0 \\leq K \\leq 10^9$

## 考察

文字列 $T$ が与えられたときに、 $S$ から $T$ へ(可能ならば)最小何回の操作で変換できるかを求めることを考える。
これは以下のようなアルゴリズムで求められる。

今 $S\_i$ と $T\_j$ に注目しているとする。ただし $T\_\{N\}=0$ とする。もしどちらかが先に終点にいる、つまり

- $i = N$ かつ $j \\lt N$
- $i \\lt N$ かつ $j=N+1$

の少なくとも一方が成り立つならアウト。

そうでない場合、以下のように遷移をする。

- $S\_i = T\_j$ のとき。 $i$ と $j$ を 1 つ進める。
- $S\_i = 0, T\_j = 1$ のとき。操作によって先のどこかから $1$ を持ってくる必要があるので、 $1$ を \*_前借り_ \*することにして $j$ を 1 つ進める。
- $S\_i = 1, T\_j = 0$ のとき。 $S\_i$ を消す必要があるので、前借りを 1 つ減らして(前借りしていなければアウト)、 $i$ を 1 つ進める。

最終的に前借りが $0$ なら OK で、合計の前借りの回数が操作回数の最小値となる。

これをそのまま数え上げの DP に落とし込めばよい。必要なのは以下の 4 つの状態。

- $T$ の今見ている値($T\_j$)
- $S$ の今見ている index
- 今残っている前借りの数
- 前借りの合計回数(つまり操作回数)

「$T$ の今見ている値」は、 $S\_i = 1, T\_j = 0$ のときに $j$ が進まないので必要となる。

## 実装例

[提出 #18440335 - AtCoder Grand Contest 046](https://atcoder.jp/contests/agc046/submissions/18440335)

```cpp
#include <atcoder/modint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using mint = atcoder::modint998244353;

void solve() {
    string s;
    int m;
    cin >> s >> m;
    int n = s.length();

    auto dp = vector(2, vector(n + 1, vector(n + 1, vector(n + 1, mint(0)))));
    // Tの次の文字, Sの今見てるindex, 1の前借り数, 操作回数
    dp[0][0][0][0] = dp[1][0][0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k) {
                if (s[i] == '0') {
                    // 0-0: スキップ
                    if (i < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i + 1][j][k] += dp[0][i][j][k];
                        }
                    }

                    // 0-1: 1を貰う
                    if (j < n && k < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i][j + 1][k + 1] += dp[1][i][j][k];
                        }
                    }
                } else {
                    // 1-0: 1を消す
                    // このときだけ相手の文字は0のまま
                    if (i < n && j > 0) {
                        dp[0][i + 1][j - 1][k] += dp[0][i][j][k];
                    }

                    // 1-1: スキップ
                    if (i < n) {
                        for (int nc = 0; nc < 2; ++nc) {
                            dp[nc][i + 1][j][k] += dp[1][i][j][k];
                        }
                    }
                }
            }
        }
    }

    mint ans = 0;
    for (int k = 0; k <= n && k <= m; ++k) {
        ans += dp[0][n][0][k];
    }
    cout << ans.val() << "\n";
}
```

