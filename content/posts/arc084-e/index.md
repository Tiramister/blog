---
title: AtCoder Regular Contest 084 E - Finite Encyclopedia of Integer Sequences
date: 2020-11-28
tags: [atcoder]
---

[E - Finite Encyclopedia of Integer Sequences](https://atcoder.jp/contests/arc084/tasks/arc084_c)

## 問題

$1$ 以上 $K$ 以下の整数からなる長さ $1$ 以上 $N$ 以下の整数列のうち、辞書順で $\\lceil \\frac\{X\}\{2\} \\rceil$ 番目のものを求めよ。ここで $X$ は整数列の個数とする。

### 制約

- $1 \\leq N, K \\leq 3 \\cdot 10^5$

## 考察

「大体真ん中にいるのはどの数列か？」を考える。

$K$ が偶数の場合は簡単で、 $(\\frac\{K\}\{2\}, K, K, \\cdots)$ と $(\\frac\{K\}\{2\}+1, 1, 1, \\cdots)$ の間がちょうど真ん中であることが分かる。
これは先頭が $\\frac\{K\}\{2\}$ 以下のものと $\\frac\{K\}\{2\}+1$ 以上のものが同数のためである。
よって答えは $(\\frac\{K\}\{2\}, K, K, \\cdots)$ となる。

$K$ が奇数の場合、長さ $N$ の数列 $(P\_i)\_i = (\\lceil \\frac\{K\}\{2\} \\rceil, \\lceil \\frac\{K\}\{2\} \\rceil, \\cdots)$ が大体真ん中になる。
$\\lceil \\frac\{K\}\{2\} \\rceil$ 以外の要素を含む数列 $(A\_i)\_i$ について、 $(K + 1 - A\_i)\_i$ という数列と対応させる。すると、一方は $(P\_i)\_i$ より前、もう一方は後にあるので、前後に同数あることが分かる。

この対応で例外となるのが $\\lceil \\frac\{K\}\{2\} \\rceil$ しか含まない数列 $N-1$ 個で、これらは $(P\_i)\_i$ より前にある。
つまり $(P\_i)\_i$ の前にある数列は後にある数列より $N-1$ 個多い。よって辞書順で $(P\_i)\_i$ の $\\lfloor \\frac\{N-1\}\{2\} \\rfloor$ 個前にある数列が答えになる。

そのためには「辞書順で $(A\_i)\_i$ の 1 つ前にある数列」を求められればよい。これは以下のアルゴリズムで求められる。

- $(A\_i)\_i$ の末尾が $1$ の場合、末尾を取り除く。
- そうでない場合、末尾を $1$ 減らし、長さが $N$ になるまで $K$ を追加する。

## 実装例

[提出 #18417837 - AtCoder Regular Contest 084](https://atcoder.jp/contests/arc084/submissions/18417837)

```cpp
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int k, n;
    cin >> k >> n;

    if (k % 2 == 0) {
        cout << k / 2 << " ";
        for (int i = 0; i < n - 1; ++i) cout << k << " ";
        cout << "\n";

    } else {
        vector<int> ans(n, (k + 1) / 2);  // 真ん中からスタート
        int front = n;                    // ansより前が後よりいくつ多いか

        while (front > 1) {
            // 1つ前に戻す
            if (--ans.back() == 0) {
                ans.pop_back();
            } else {
                // 後ろにkを補充
                ans.resize(n, k);
            }
            front -= 2;
        }

        for (auto x : ans) cout << x << " ";
        cout << "\n";
    }
}
```

