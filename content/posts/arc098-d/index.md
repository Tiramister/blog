---
title: "AtCoder Regular Contest 098 D - Xor Sum 2"
date: 2018-11-08
tags: [atcoder]
---

[D - Xor Sum 2](https://atcoder.jp/contests/arc098/tasks/arc098_b)

## 概要

長さ $N$ の数列 $A\_i$ が与えられる。以下を満たす $(l, r)$ の組の数を求めよ。
ここで、 $\\oplus$ は bitwise xor を表す。

$$
A\_l + A\_\{l + 1\} + \\cdots + A\_r =
A\_l \\oplus A\_\{l + 1\} \\oplus \\cdots \\oplus A\_r
$$


### 制約

- $1 \\leq N \\leq 2 \\times 10\^5$
- $0 \\leq A\_i \\leq 2\^\{20\}$

## 解説

まず、和と xor の間には、以下の恒等式が成り立つ。
ここで、 $\\land$ は bitwise and を表す。

$$
A + B = A \\oplus B + 2(A \\land B)
$$

この恒等式から、以下が成り立つ。

$$
\\begin\{aligned\}
A \\land B = 0 &\\implies A + B = A \\oplus B \\\\
A \\land B \\neq 0 &\\implies A + B \\gt A \\oplus B
\\end\{aligned\}
$$

これを拡張すると、以下が成り立つ。

$$
\\begin\{aligned\}
&
A\_l + A\_\{l + 1\} + \\cdots + A\_r =
A\_l \\oplus A\_\{l + 1\} \\oplus \\cdots \\oplus A\_r \\\\
\\iff&
A\_l \\land A\_\{l + 1\} \\land \\cdots \\land A\_r = 0
\\end\{aligned\}
$$

後は、これを満たす $(l, r)$ を数え上げればいい。

$l$ を固定したとき、and の性質から上の条件は $r$ について単調性を持つ。
すなわち、「 $l\\leq r \\leq r\_0$ なら常に $(l, r)$ は条件を満たし、逆に $r \\gt r\_0$ なら常に $(l, r)$ は条件を満たさない」という境界値 $r\_0$ が存在する。このとき条件を満たす組の数は $r\_0 - l + 1$ 個となる。これを各 $1 \\leq l \\leq N$ について全部求めて、足し合わせればいい。
この $r\_0$ は尺取り法なら $O(N)$、二分探索なら $O(N \\log N)$ で全て求められる。

なお $(l, r)$ が条件を満たすかの判定は、問題文通りに累積和と累積 xor を使って判定するといい。
and は不可逆なので、累積 and は使えない。

## 実装例

答えの最大値は $10\^\{10\}$ 程度になるため、地味に int ではオーバーフローすることに注意(1 敗)。

[提出 #34713207 - AtCoder Regular Contest 098](https://atcoder.jp/contests/arc098/submissions/34713207)

```cpp
#include <iostream>

using namespace std;

using ll = long long;

int main() {
    int N;
    cin >> N;

    ll A[N + 1];
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    ll sum[N + 1], xorsum[N + 1];
    sum[0] = xorsum[0] = 0;
    // 累積和と累積xor どちらも1-indexed

    for (int i = 1; i <= N; ++i) {
        sum[i] = sum[i - 1] + A[i];
        xorsum[i] = (xorsum[i - 1] ^ A[i]);
    }

    ll ans = 0;
    for (int l = 1; l <= N; ++l) {
        int ok = l, ng = N + 1;
        // (l, ok)は条件を満たし、(l, ng)は条件を満たさない
        // このokとngの距離を縮めていくことで境界値r0を求める

        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (sum[mid] - sum[l - 1] == (xorsum[mid] ^ xorsum[l - 1])) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        // 最終的なokが境界値r0となる
        ans += ok - l + 1;
    }

    cout << ans << endl;
    return 0;
}
```

