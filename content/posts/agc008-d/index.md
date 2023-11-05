---
title: "AtCoder Grand Contest 008 D - K-th K"
date: 2018-09-15
tags: [atcoder]
---

[D - K-th K](https://atcoder.jp/contests/agc008/tasks/agc008_d)

## 概要

整数 $N$ と長さ $N$ の数列 $x\_i$ が与えられる。

以下の条件を満たす長さ $N\^2$ の数列を存在すれば構築せよ。

- $1 \\sim N$ がそれぞれちょうど $N$ 個ずつ含まれている。
- $i$ 番目の $i$ は数列全体の左から $x\_i$ 番目に位置する。

### 制約

- $1 \\leq N \\leq 500$
- $x\_i$ は全て異なる。

## 解説

各 $i$ について $x\_i$ より前に $i$ を $i - 1$ 個埋めなければいけないので、これはできるだけ左側に埋めるべきとなる。

しかし $x\_i \\gt x\_j$ のとき、 $i$ を先に埋めてしまったせいで $j$ の埋める場所がない (ただし $i$ は $(x\_j, x\_i)$ にも埋められる) という事態が発生する可能性がある。
これを防ぐには予め $x\_i$ についてソートして、貪欲に左から埋めていけばいい。

さて、仮に全部矛盾なく埋められたとして残りの $N - i$ 個の $i$ は適当に埋めればいいか、というとそうではない(1 敗)。
これらは逆に $x\_i$ より右側に埋めなければならないため、先程の操作を再び大小反転して行う必要がある。

## 実装例

[提出 #3196456 - AtCoder Grand Contest 008](https://atcoder.jp/contests/agc008/submissions/3196456)

```cpp
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    int N;
    cin >> N;

    pair<int, int> x[N];
    // (x_n, n)を保持

    for (int i = 0; i < N; ++i) {
        cin >> x[i].first;
        x[i].second = i + 1;
    }
    sort(x, x + N);
    // x_nでソート

    int a[N * N + 1], now = 0;
    fill(a, a + N * N + 1, -1);
    // aは1-indexed 埋まってなければ-1
    // 今a[now]まで埋まっている

    // x_nの小さい方から埋めていく
    for (int i = 0; i < N; ++i) {
        int idx, n;
        tie(idx, n) = x[i];
        a[idx] = n;

        // -1の箇所にnを左から詰めていく
        for (int j = 0; j < n - 1; ++j) {
            while (true) {
                if (a[++now] < 0) {
                    a[now] = n;
                    break;
                }
            }
        }

        // idxより左側にn-1個埋められなかったらアウト
        if (now > idx) {
            cout << "No" << endl;
            return 0;
        }
    }

    // 大小反転して同じことをする
    now = N * N + 1;
    for (int i = N - 1; i >= 0; --i) {
        int idx, n;
        tie(idx, n) = x[i];

        for (int j = n; j < N; ++j) {
            while (true) {
                if (a[--now] < 0) {
                    a[now] = n;
                    break;
                }
            }
        }

        if (now < idx) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    for (int i = 1; i <= N * N; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
```

