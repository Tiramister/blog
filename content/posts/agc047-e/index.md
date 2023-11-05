---
title: AtCoder Grand Contest 047 E - Product Simulation
date: 2020-08-10
tags: [atcoder]
---

[E - Product Simulation](https://atcoder.jp/contests/agc047/tasks/agc047_e)

## 問題

長さ $n$ の配列 $\\\{ v\_i \\\}$ がある。最初 $v\_0 = a, v\_1 = b$ で他の要素は全て $0$ である。

以下の命令を組み合わせて、最終的に $v\_2 = a \\cdot b$ となるような命令列を作れ。

- $\\mathrm\{add\}(i, j, k): \\; v\_k := v\_i + v\_j$
- $\\mathrm\{lt\}(i, j, k): \\; v\_k := v\_i \\lt v\_j$

### 制約

- $0 \\leq a, b \\leq 10^9$
- $n = 2 \\cdot 10^5$
- 総命令数は $2 \\cdot 10^5$ 以下でなくてはならない。
- 途中で配列の値が $10^\{19\}$ を超えてはならない。

## 考察

基本的な方針は以下の通り。

1.  $a, b$ を 2 進数にバラす。
2.  畳み込む。
3.  整数に戻す。

実装が全てを物語っているので、以下補足。

### 補足

$x$ を 2 進数にバラすときは、 $2^\{30\}$ から $2^0$ まで順番に $x$ を超えないように足していけばいい。

このとき「 $v\_i$ が $0$ なら何もせず、 $1$ なら $2^k$ を $v\_j$ に加える」という操作がしたくなる。
今回は条件分岐が使えないので難しく思えるが、 $v\_i$ に対して直接ダブリングを行うことでできる。

畳み込む際に bit and が欲しくなる(「 $a$ の $k$ 桁目と $b$ の $k\'$ 桁目が共に 1 なら、答えに $2^\{k + k\'\}$ を加算」という操作のため)。
やりようは色々あるが、以下の実装では $v\_i + v\_j \\gt 1$ で判定している。

## 実装例

提出リンクの方には、デバッグ用の機能の実装も残してある。

[提出 #15802059 - AtCoder Grand Contest 047](https://atcoder.jp/contests/agc047/submissions/15802059)

```cpp
#include <iostream>

void query(char c, int i, int j, int k) {
    std::cout << c << " " << i << " " << j << " " << k << "\n";
}

/* ----- several constants, functions ----- */

constexpr int A = 0, B = 1, S = 2;
constexpr int ZERO = 100, ONE = 101;
constexpr int K = 30, KB = 200;

void reset(int i) { query('+', ZERO, ZERO, i); }
void copy(int i, int j) { query('+', ZERO, i, j); }

void negate(int i) { query('<', i, ONE, i); }
void pow(int i, int k) {
    while (k--) query('+', i, i, i);
}

/* ----- main routine ----- */

void init() {
    query('+', A, B, 2);
    query('<', ZERO, 2, ONE);  // v[ZERO] = 0, v[ONE] = 1
    reset(2);

    query('+', ZERO, ONE, KB);
    for (int k = 1; k <= K; ++k) {
        query('+', KB + k - 1, KB + k - 1, KB + k);
        // v[KB + k] = 2^k
    }
}

void tobin(int xi, int l) {
    const int SB = l + K + 1;

    for (int k = K; k >= 0; --k) {
        query('+', SB, KB + k, SB + 1);
        query('<', xi, SB + 1, l + k);
        negate(l + k);  // v[l+k] = (sum + 2^k <= x)

        copy(l + k, SB + 1);
        pow(SB + 1, k);
        query('+', SB, SB + 1, SB);  // sum += (v[l+k] * 2^k)
    }
}

void multiply(int xi, int yi, int zi, int l) {
    for (int xk = 0; xk <= K; ++xk) {
        for (int yk = 0; yk <= K; ++yk) {
            query('+', xi + xk, yi + yk, l + 1);
            query('<', ONE, l + 1, l + 1);
            query('+', zi + xk + yk, l + 1, zi + xk + yk);
            // v[zi+xk+yk] += x[xk] & y[yk]
        }
    }

    for (int k = 0; k <= K * 2; ++k) {
        pow(zi + k, k);
        query('+', l, zi + k, l);
    }
}

void solve() {
    std::cout << 6048 << "\n";  // 総命令数

    init();

    constexpr int AB = 300, BB = 400, FB = 500;
    tobin(A, AB);
    tobin(B, BB);
    multiply(AB, BB, FB, S);
}
```

