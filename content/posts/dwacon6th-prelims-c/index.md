---
title: "第 6 回 ドワンゴからの挑戦状 予選 C - Cookie Distribution"
date: 2020-01-12
tags: [atcoder]
---

[C - Cookie Distribution](https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_c)

## 問題

$n$ 人の子供に， $k$ 日に渡って飴を配る．
$i$ 日目には，各子供が高々 1 つの飴を貰うように，合計 $a\_i$ 個の飴を配る．

最終的に $j$ 番目の子供が合計 $c\_j$ 個の飴を貰ったとき， $\\prod c\_j$ を「嬉しさ」と定義する．

全ての配り方 $\\prod \\binom\{n\}\{a\_i\}$ 通りについて嬉しさを求めたとき，その合計を求めよ．

### 制約

- $1 \\leq n \\leq 10\^3$
- $1 \\leq k \\leq 20$
- $1 \\leq a\_i \\leq n$

## 考察

求めるものは本質的には期待値なのだが，「積の期待値」は線形性が使えないので求めにくい．そこでこれを「和の期待値」に変形する．

まず $b\_\{i, j\}$ を「 $i$ 日目に子供 $j$ が貰った飴の数」とする．すると，嬉しさの総和は以下の式で表せる．

$$
\\sum\_\{\\sum\_j b\_\{1, j\} = a\_1\} \\cdots
\\sum\_\{\\sum\_j b\_\{k, j\} = a\_k\}
\\prod\_j \\left( \\sum\_i b\_\{i, j\} \\right)
$$

さらに一番後ろの $\\prod \\sum$ は展開できる．

$$
\\sum\_\{\\sum\_j b\_\{1, j\} = a\_1\} \\cdots
\\sum\_\{\\sum\_j b\_\{k, j\} = a\_k\}
\\sum\_\{1 \\leq d\_1 \\leq k\} \\cdots
\\sum\_\{1 \\leq d\_n \\leq k\}
\\prod\_j b\_\{d\_j, j\}
$$

最後に $\\sum$ の順番を変える．

$$
\\sum\_\{1 \\leq d\_1 \\leq k\} \\cdots
\\sum\_\{1 \\leq d\_n \\leq k\}
\\sum\_\{\\sum\_j b\_\{1, j\} = a\_1\} \\cdots
\\sum\_\{\\sum\_j b\_\{k, j\} = a\_k\}
\\prod\_j b\_\{d\_j, j\}
$$

これによって，「 $1 \\leq d\_i \\leq k$ を満たすタプル $(d\_1, \\cdots, d\_n)$ に対し， $b\_\{d\_j, j\} = 1$ を全て満たす $b$ は何通りあるか？」を全てのタプルに対し足し合わせる，と変形できた．
意味的には，「子供 $j$ が $d\_j$ 日目に飴を貰うような配り方は何通りか？」となる．

1 つタプル $(d\_1, \\cdots, d\_n)$ を固定して考える．ここで $d\_j = i$ を満たす $j$ が $x\_i$ 個あったとする．つまり $i$ 日目に飴を貰う子供が $x\_i$ 人いるということである．
これを満たす配り方の総数は，指定されている子供たちへの配り方を考慮すると以下の式で表せる．

$$
\\prod\_i \\binom\{n - x\_i\}\{a\_i - x\_i\}
$$

この値は $d\_j$ に依存しないので， $x\_i$ が同じになるような $d\_j$ をまとめて考えると以下のようになる．

$$
\\prod\_i \\binom\{m\_i\}\{x\_i\}\\binom\{n - x\_i\}\{a\_i - x\_i\}
$$

ここで $m\_i$ は $i$ 日目の時点でまだ飴を貰っていない子供の数．

これを $\\sum x\_i = n$ を満たす全ての $\\\{ x\_i \\\}$ について足し上げればよい．
これは $dp\_\{i, m\} =$ 「 $i$ 日目で $m$ 人が飴を貰っていない場合の総和」とすれば，遷移 $O(n)$ の全体で $O(n\^2 k)$ で埋められる．

## 実装例

[提出 #9427889 - 第6回 ドワンゴからの挑戦状 予選](https://atcoder.jp/contests/dwacon6th-prelims/submissions/9427889)

```cpp
#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T>
struct Combination { ... };

const Combination<mint> C(10000);

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }


int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> xs(k);
    for (auto& x : xs) std::cin >> x;

    auto dp = vec(k + 1, vec(n + 1, mint(0)));
    dp[k][0] = 1;
    for (int d = k - 1; d >= 0; --d) {
        for (int m = n; m >= 0; --m) {
            for (int l = 0; l <= m; ++l) {
                dp[d][m] += dp[d + 1][m - l] * C.comb(m, l) * C.comb(n - l, xs[d] - l);
            }
        }
    }

    std::cout << dp[0][n] << std::endl;
    return 0;
}
```

