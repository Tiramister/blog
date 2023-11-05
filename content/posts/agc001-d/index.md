---
title: "AtCoder Grand Contest 001 D - Arrays and Palindrome"
date: 2018-09-15
tags: [atcoder]
---

[D - Arrays and Palindrome](https://atcoder.jp/contests/agc001/tasks/agc001_d)

## 概要

総和 $N$ 、長さ $M$ の数列 $A$ が与えられる。 正整数列 $a, b$ で以下を満たすようなものが存在すれば、それらを 1 つ出力せよ。

- $a$ は $A$ を並び替えたものである。
- $b$ の総和は $N$ である。
- 以下の 2 つを同時に満たす長さ $N$ の任意の文字列は、全て同じ文字からなる。
  - 先頭から $a\_1$ 文字、 $a\_2$ 文字、...... と区切ったとき、各部分文字列は全て回文である。
  - 先頭から $b\_1$ 文字、 $b\_2$ 文字、...... と区切ったとき、各部分文字列は全て回文である。

### 制約

- $1 \\leq N \\leq 10\^5$
- $1 \\leq M \\leq 100$

## 解説

まず、回文という条件は「対称の位置にある文字が同じである」という制約と見ることができる。
そこで「文字を頂点として、同じ文字同士に辺が張られたグラフ」を考えると、「全ての文字が同じ」というのは「グラフが連結である」ことと同値になる。

{{<image src="0.png">}}

これで Union-Find なり使えばジャッジはできるようになったが、今回は構築の方なのでもっと深く考える必要がある。

まず $M = 1$ のときを考えてみる。このとき、以下のように $b = (N - 1, 1)$ とすれば上手いこと連結になる。

{{<image src="1.png">}}

この発想は $M \\gt 1$ でも使える。というのも、右端の余った 1 頂点を使って隣に繋げればいい。

以下に隣の回文領域の頂点数が偶数の場合と奇数の場合を示す。見ての通り、偶数の場合は上手くいくのだが奇数の場合は上手くいかない。

{{<image src="2.png">}}

実は両端以外に奇数長の回文領域がある場合、全体を連結にできない。というのも、全体を連結にするには辺の数が足りないのだ。

というわけで、奇数が 3 つ以上なら不可能となり、そうでなければ奇数要素を両端に移動させて、上の構築方法を実行すればいい。

## 実装例

上では複雑な話をしたが、要は `a` の先頭を 1 減らして末尾を 1 増やすだけで構築できてしまう。実装自体は非常に軽い。

[提出 #3197276 - AtCoder Grand Contest 001](https://atcoder.jp/contests/agc001/submissions/3197276)

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int a[M], odd = 0;
    for (int i = 0; i < M; ++i) {
        cin >> a[i];
        odd += a[i] % 2;
    }

    if (M == 1) {
        cout << a[0] << endl;
        if (a[0] == 1) {
            cout << 1 << endl;
            cout << a[0] << endl;
        } else {
            cout << 2 << endl;
            cout << a[0] - 1 << " " << 1 << endl;
        }
        return 0;
    }

    // 可能性判定
    if (odd > 2) {
        cout << "Impossible" << endl;
        return 0;
    }

    // 奇数要素を両端に持っていく
    odd = 0;
    for (int i = 0; i < M; ++i) {
        if (a[i] % 2 == 1) {
            ++odd;
            if (odd == 1) {
                swap(a[i], a[0]);
            } else if (odd == 2) {
                swap(a[i], a[M - 1]);
            }
        }
    }

    // 数列aを出力
    for (int i = 0; i < M; ++i) {
        if (a[i] > 0) {
            cout << a[i] << " ";
        }
    }
    cout << endl;

    // 数列bを構築
    vector<int> b;

    --a[0];
    ++a[M - 1];
    for (int i = 0; i < M; ++i) {
        // 0を出力してはいけないことに注意
        if (a[i] > 0) b.push_back(a[i]);
    }

    // 数列bを出力
    cout << b.size() << endl;
    for (int c : b) {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}
```

