---
title: AtCoder Beginner Contest 188 F - +1-1x2
date: 2021-01-11
tags: [atcoder]
---

[F - +1-1x2](https://atcoder.jp/contests/abc188/tasks/abc188_f)

## 問題

整数 $X$ がある。あなたは以下の操作を何度でも行うことができる。

- $X$ を $X+1$ に置き換える。
- $X$ を $X-1$ に置き換える。
- $X$ を $2X$ に置き換える。

最終的に $X$ を整数 $Y$ に一致させたい。そのために必要な操作回数の最小値を求めよ。

### 制約

- $1 \\leq X, Y \\leq 10^\{18\}$

## 解法

操作を逆から見ると、以下の操作で $Y$ を $X$ に一致させる問題になる。

- $Y$ を $Y+1$ に置き換える。($+1$)
- $Y$ を $Y-1$ に置き換える。($-1$)
- $Y$ を $\\frac\{Y\}\{2\}$ に置き換える。 **ただし $Y$ が偶数のときしか行えない。** ($\\div2$)

ここで重要な考察として、 $+1+1\\div2$ のような「2 回以上 $\\pm1$ をしてから $\\div2$ 」という操作は無駄である。なぜなら $+1+1\\div2$ は $\\div2+1$ と等価だからである。

よって、最適な操作は以下のようになる。2 で $\\pm1$ を一度だけしか行わないのが肝。

1. まだ $\\div2$ を行うなら 2 へ、行わないなら 4 に進む。
2. $Y$ が奇数の場合、 $\\pm1$ の好きな方を行う。
3. $\\div2$ を行い、1 に戻る。
4. $\\pm1$ を $|X-Y|$ 回行い、 $Y$ を $X$ に合わせる。

これをメモ化再帰で実装すればよい。
1 回のループで $Y$ が半減するので、再帰の深さは $O(\\log Y)$ になる。

2 で分岐が発生するので、一見するとかなり多く分岐しそうに見える。しかし下の例 ($Y=57$) から分かるように、再帰の各深さにおける $Y$ の候補は高々 2 つしかない。よって計算量も $O(\\log Y)$ となる。

$$
\\\{57\\\} \\to \\\{28, 29\\\} \\to \\\{14, 15\\\} \\to \\\{7, 8\\\} \\to \\cdots
$$

### 実装例

$1 \\xrightarrow\{+1\} 2 \\xrightarrow\{\\div2\} 1$ の無限ループに注意。

[提出 #19376744 - AtCoder Beginner Contest 188](https://atcoder.jp/contests/abc188/submissions/19376744)

```cpp
#include <iostream>
#include <map>

using namespace std;
using lint = long long;

void solve() {
    lint x, y;
    cin >> x >> y;

    map<lint, lint> dp;
    auto dfs = [&](auto&& f, lint p) -> lint {
        if (dp.count(p)) return dp[p];

        auto& ret = dp[p];

        // 2で割らない場合
        ret = abs(p - x);

        // 2で割る場合
        for (int d = -1; d <= 1; ++d) {
            lint np = p + d;
            if (np < 0 || np % 2 != 0 ||
                np / 2 >= p) continue;
            // 最後の条件は無限ループを省くのに必要

            ret = min(ret, f(f, np / 2) + abs(d) + 1);
        }
        return ret;
    };

    cout << dfs(dfs, y) << "\n";
}
```

