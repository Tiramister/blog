---
title: "Typical DP Contest I - イウィ"
date: 2020-01-23
tags: [atcoder]
---

[I - イウィ](https://atcoder.jp/contests/tdpc/tasks/tdpc_iwi)

## 問題

`i`と`w`からなる文字列 $s$ に対して，以下の操作を最大で何回行えるか求めよ．

- 連続する`iwi`を $s$ から取り除く．

### 制約

- $1 \\leq |s| \\leq 300$

## 考察

操作を後ろから考えると DP が立つ．

$i \\lt j \\lt k$ について $s\_is\_js\_k = \\text\{iwi\}$ が成り立つとき， $s\_is\_js\_k$ を操作対象にするには，これらを隣接させないといけない，つまり $s\_\{(i, j)\}, s\_\{(j, k)\}$ が操作によって空文字列に変換できなければならない．

そこで $c\_\{i, j\} =$ 「 $s\_\{[i, j]\}$ が消せるか？」という値を求めることにする。これは以下のいずれかの場合のみ真となる。

- $[i, j]$ が空集合
- ある $i \\lt k \\lt j$ が存在して， $s\_is\_ks\_j = \\text\{iwi\}$ かつ $c\_\{i + 1, k - 1\} \\land c\_\{k + 1, j - 1\}$
- ある $i \\leq k \\lt j$ が存在して， $c\_\{i, k\} \\land c\_\{k + 1, j\}$

$k$ は $O(n)$ 通りなので、 $c\_\{i, j\}$ は $O(n\^3)$ で求まる。

同様にして $dp\_\{i, j\} =$ 「 $s\_\{[i, j]\}$ に対する最大の操作回数」も以下の式で求まる。

$$
dp\_\{i, j\} =
\\begin\{cases\}
  \\frac\{j - i + 1\}\{3\} \& (c\_\{i, j\} = \top) \\\\
  \\max\_\{i \\leq k \\lt j\} \\\{ dp\_\{i, k\} + dp\_\{k + 1, j\} \\\} \& (c\_\{i, j\} = \bot)
\\end\{cases\}
$$
計算量は $c\_\{i, j\}$ と同様 $O(n\^3)$ ．

## 実装例

[提出 #9675043 - Typical DP Contest](https://atcoder.jp/contests/tdpc/submissions/9675043)

```cpp
#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    auto dp = vec(n, vec(n, 0));
    auto clean = vec(n, vec(n, false));
    for (int i = 1; i < n; ++i) {
        clean[i][i - 1] = true;
    }

    for (int l = 0; l < n; ++l) {
        for (int i = 0; i + l < n; ++i) {
            int j = i + l;

            // clean check
            // create iwi
            if (s[i] == 'i' && s[j] == 'i') {
                for (int k = i + 1; k <= j - 1; ++k) {
                    if (s[k] == 'w' &&
                        clean[i + 1][k - 1] && clean[k + 1][j - 1]) {
                        clean[i][j] = true;
                    }
                }
            }
            // separate
            for (int k = i; k + 1 <= j; ++k) {
                if (clean[i][k] && clean[k + 1][j]) clean[i][j] = true;
            }

            if (clean[i][j]) dp[i][j] = (l + 1) / 3;

            for (int k = i; k + 1 <= j; ++k) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    std::cout << dp[0][n - 1] << std::endl;
}
```

