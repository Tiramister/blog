---
title: "yukicoder No.1268 - Fruit Rush 2"
date: 2020-10-24
tags: [yukicoder]
---

[No.1268 Fruit Rush 2 - yukicoder](https://yukicoder.me/problems/no/1268)

## 問題

フィボナッチ数列 $(F\_i)$ を以下のように定める。

- $F\_0 = F\_1 = 1$
- $F\_i = F\_\{i-1\} + F\_\{i-2\} \\quad (i \\geq 2)$

また $(F\_i)$ に出現する整数をフィボナッチ数ということにする。

全ての要素が異なる長さ $N$ の正整数列 $(A\_i)$ が与えられる。
$S \\subseteq \\\{1, \\cdots, N\\\}$ で以下を満たすものの個数を求めよ。

- $S \\neq \\emptyset$
- $\\sum\_\{i \\in S\} F\_\{A\_i\}$ がフィボナッチ数である。

### 制約

- $1 \\leq N \\leq 2 \\cdot 10\^5$
- $1 \\leq A\_i \\leq 10\^\{18\}$
- $i \\neq j \\implies A\_i \\neq A\_j$

## 考察

総和が $F\_k$ になるような選び方を数え上げる。
まず考えられるのは $k = A\_i$ なる $i$ を選ぶ方法で、このとき他のものは選べないので高々 1 通り。

そうでない場合、実は $F\_\{k-1\}$ を必ず選ばなくてはならない。
これは $F\_\{k\} \\gt \\sum\_\{i=1\}\^\{k-2\} F\_i$ が成り立つことから従う(証明は帰納法)。
$F\_\{k-1\}$ を選んだ後は、 $F\_k - F\_\{k-1\} = F\_\{k-2\}$ より総和が $F\_\{k-2\}$ になる選び方の数え上げに帰着される。

以上の考察から、 $k$ として考えるべきなのは $\\bigcup\_\{i\} \\\{ A\_i, A\_i + 1 \\\}$ の元に限定されることが分かる。
後は set や map を使うことで、上の場合分けをそのままシミュレートすることができる。

## 実装例

[#570750 (C++17) No.1268 Fruit Rush 2 - yukicoder](https://yukicoder.me/submissions/570750)

```cpp
#include <iostream>
#include <set>
#include <map>

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::set<lint> xs, ks;
    while (n--) {
        lint x;
        std::cin >> x;

        xs.insert(x);
        ks.insert(x);
        ks.insert(x + 1);
    }

    lint ans = 0;
    std::map<lint, lint> dp;  // sumがF_kになる選び方の総数

    for (auto k : ks) {
        auto& pat = dp[k];
        pat = 0;

        // F_k単体
        if (xs.count(k)) ++pat;

        // F_{k-1}を使いF_{k-2}に帰着
        if (xs.count(k - 1) &&
            dp.count(k - 2)) pat += dp[k - 2];

        ans += pat;
    }

    std::cout << ans << "\n";
}
```

