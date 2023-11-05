---
title: "Codeforces Round 613 F - Classical?"
date: 2020-01-16
tags: [codeforces]
---

{{< hidden >}}
$\\gdef\\lcm\{\\operatorname\{lcm\}\}\\lcm$
{{< / hidden >}}

[Problem - F - Codeforces](https://codeforces.com/contest/1285/problem/F)

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる． $\\max\_\{i \\neq j\} \\lcm (a\_i, a\_j)$ を求めよ．

### 制約

- $2 \\leq n \\leq 10\^5$
- $1 \\leq a\_i \\leq 10\^5 (= X)$

## 考察

LCM なので例によって $\\lcm(x, y) = \\dfrac\{xy\}\{\\gcd(x, y)\}$ と変形する．そこで GCD によって分類する，つまり $g$ を固定して GCD が $g$ のものについて考える．

$g$ の倍数しか考えなくていいので， $\\\{ a\_i \\\}$ から $g$ の倍数を抽出し，全て $g$ で割ったものを $\\\{ b\_i \\\}$ とする．この中で，互いに素なペアの積の最大値が求めるものである．

ここで最大値しか要らないことから， **スライド最大値** に似たテクニックを使う．まず $\\\{ b\_i \\\}$ を降順にソートし，前から順にスタックに入れていく．

途中で $b\_i$ と互いに素な要素がスタック内に存在すれば，それらが全て取り出されるまで **スタックから捨て続けていい** ，というのが肝．これは，スタックから捨てられた要素は $b\_i$ によって作られるペアより大きい積を作れないことから従う(スタックには上から **小さい** 要素が入っていて，数列の残りは $b\_i$ 以下であることに注意)．

後は「スタック内に $b\_i$ と互いに素なものが存在するか」を判定できればよいが，ここで [この記事](/blog/posts/mobius/) で説明したテクニックを使う．

## 実装例

[Submission #68893805 - Codeforces](https://codeforces.com/contest/1285/submission/68893805)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
T gcd(T n, T m) { ... }

using lint = long long;
constexpr int X = 100000;

int main() {
    std::vector<std::vector<int>> pss(X + 1);
    // set of x's factors
    for (int p = 1; p <= X; ++p) {
        for (int x = p; x <= X; x += p) {
            pss[x].push_back(p);
        }
    }

    std::vector<int> f(X + 1, 0);
    // mobius function
    f[1] = 1;
    for (int d = 2; d <= X; ++d) {
        for (int p : pss[d]) {
            if (p < d) f[d] -= f[p];
        }
    }

    // main process
    int n;
    std::cin >> n;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;
    std::sort(xs.rbegin(), xs.rend());

    std::vector<std::vector<int>> yss(X + 1);
    // x's multipliers
    for (auto x : xs) {
        for (auto p : pss[x]) {
            yss[p].push_back(x / p);
        }
    }

    lint ans = 0;
    std::vector<int> cnt(X + 1, 0), stk;

    for (int d = 1; d <= X; ++d) {
        const auto& ys = yss[d];

        for (auto y : ys) {
            while (true) {
                int c = 0;
                // number of elements coprime to x in the stack
                for (auto p : pss[y]) c += cnt[p] * f[p];
                if (c == 0) break;

                auto x = stk.back();
                if (gcd(x, y) == 1) {
                    ans = std::max(ans, (lint)x * y * d);
                }

                // delete x from the stack
                for (auto p : pss[x]) --cnt[p];
                stk.pop_back();
            }

            // add y to the stack
            for (auto p : pss[y]) ++cnt[p];
            stk.push_back(y);
        }

        // clear the stack and cnt
        while (!stk.empty()) {
            auto x = stk.back();
            for (auto p : pss[x]) --cnt[p];
            stk.pop_back();
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
```

