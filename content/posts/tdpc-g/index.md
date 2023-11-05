---
title: "Typical DP Contest G - 辞書順"
date: 2020-01-24
tags: [atcoder]
---

[G - 辞書順](https://atcoder.jp/contests/tdpc/tasks/tdpc_lexicographical)

## 問題

文字列 $s$ の空でない部分文字列で，(存在すれば)辞書順で $k$ 番目のものを求めよ．

ただし， $s$ 上の異なる index から構成されたものでも，文字列として同じなら 1 つとして考える．

### 制約

- $1 \\leq |s| \\leq 10\^6$
- $1 \\leq k \\leq 10\^\{18\}$

## 考察

$dp\_\{i, c\} =$ 「 $s\_\{[i, n)\}$ の部分文字列で， $c$ から始まるものの個数」を求めたい．

$s\_\{[i, n)\}$ に $c$ が含まれない場合は $0$ ，そうでなければ **一番前にある** $c$ を先頭に使うと最も多くの部分文字列を作れる．よって $s\_j = c$ を満たす最小の $j \\geq i$ を取ると，

$$
dp\_\{i, c\} = 1 + \\sum\_\{d \\in \\Sigma\} dp\_\{j + 1, d\}
$$

となる． $\\Sigma$ はアルファベットの集合．先頭の $+1$ は部分文字列 $c$ の分．
これで $i$ について降順に $dp$ を埋めることができる。

後は $dp$ を参照しながら，先頭から文字を確定させていけばよい．

## 実装例

辞書順何番目は 0-indexed で考えるとやりやすい気がする(特に順列みたいに割りたいとき)．

あとなぜかこの問題は異様にメモリに厳しいので注意．`next`(次に $c$ が出てくる index)を各 index について持ったら MLE した．

[提出 #9698389 - Typical DP Contest](https://atcoder.jp/contests/tdpc/submissions/9698389)

```cpp
#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using lint = long long;
constexpr lint INF = 1LL << 60;

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    auto next = vec(26, n);
    auto dp = vec(26, vec(n + 1, 0LL));

    for (int i = n - 1; i >= 0; --i) {
        next[s[i] - 'a'] = i;

        for (int c = 0; c < 26; ++c) {
            int j = next[c];
            if (j == n) continue;

            dp[c][i] = 1;
            for (int d = 0; d < 26; ++d) {
                dp[c][i] = std::min(dp[c][i] + dp[d][j + 1], INF);
            }
        }
    }

    lint k;
    std::cin >> k;
    --k;

    int idx = 0;
    while (idx < n) {
        int c;
        for (c = 0; c < 26; ++c) {
            if (dp[c][idx] <= k) {
                // 先頭cにk番目はないのでパス
                k -= dp[c][idx];

            } else {
                std::cout << char(c + 'a');

                while (s[idx] != c + 'a') ++idx;
                ++idx;

                --k;  // empty string
                break;
            }
        }

        if (k < 0) {
            std::cout << std::endl;
            break;
        }

        if (c == 26) {
            // k番目はなし
            std::cout << "Eel" << std::endl;
            break;
        }
    }
}
```

