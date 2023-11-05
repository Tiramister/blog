---
title: "ICPC 2017 国内予選 D - 弁当作り"
date: 2019-06-16
tags: [icpc]
---

[1619 < ICPC Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1619?year=2017)

## 問題

長さ $M$ の bit 列が $N$ 個与えられる。
全体の XOR が $0$ となるような部分集合の、要素数の最大値を求めよ。

### 制約

- $1 \\leq N, M \\leq 500$
- $1 \\leq NM \\leq 500$

## 考察

この問題の肝は「 $1 \\leq NM \\leq 500$ 」という制約で、ここから「 $N \\leq 23$ と $M \\leq 23$ のいずれかが成立する」ことが分かる。
したがって、 **常に $N$ か $M$ のいずれかで bit 全探索ができる** 。

まず $N \\leq 23$ のとき。
これは bit 列の集合を全探索して $0$ になるか判定すればいい。
ただし最大で $M = 500$ になるので、bitset で入力を持つと良いだろう。

次に $M \\leq 23$ のとき。
これは $dp\_b =$ 「全体の XOR が $b$ となるような部分集合の、要素数の最大値」という bitDP で解ける。 $N$ 個配列を取るとメモリ不足が怖いので、DP テーブルを使い回すのが良いと思われる。

## 実装例

[Run #3659593 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/1619/review/3659593/misteer/C++14)

```cpp
using bits = bitset<500>;
constexpr int INF = 1 << 30;

void solve() {
    /* ----- 入力 ----- */
    int N, M;
    cin >> N >> M;

    int ans = 0;
    if (N <= 23) {
        /* ----- Nが小さいとき ----- */
        vector<bits> B(N);
        for (auto& b : B) cin >> b;

        // 部分集合を全列挙
        for (int b = 0; b < (1 << N); ++b) {
            bits pat(0);
            for (int i = 0; i < N; ++i) {
                if ((b >> i) & 1) pat ^= B[i];
            }

            // xorが0なら要素数で更新
            if (pat.none()) {
                ans = max(ans, __builtin_popcount(b));
            }
        }
    } else {
        /* ----- Mが小さいとき ----- */
        vector<int> dp(1 << M, -INF);
        dp[0] = 0;

        for (int i = 0; i < N; ++i) {
            bits s;
            cin >> s;
            int b = s.to_ulong();  // 入力を整数に変換

            vector<int> ndp = dp;
            for (int p = 0; p < (1 << M); ++p) {
                ndp[b ^ p] = max(ndp[b ^ p], dp[p] + 1);
                // bを使う場合で更新
            }
            swap(dp, ndp);
        }
        ans = dp[0];
    }
    cout << ans << endl;
}
```

