---
title: "AtCoder Grand Contest 010 A - Addition"
date: 2018-11-10
tags: [atcoder]
---

[A - Addition](https://atcoder.jp/contests/agc010/tasks/agc010_a)

## 概要

長さ $N$ の数列 $\\\{A\_i\\\}$ が与えられる。
以下の操作を繰り返すことで、 $\\\{A\_i\\\}$ の長さを 1 にできるか判定せよ。

1. $A\_i, A\_j$ の偶奇が一致しているような、相違なる $i, j$ を選ぶ。
2. $A\_i, A\_j$ を $\\\{A\_i\\\}$ から消す。
3. $A\_i + A\_j$ を $\\\{A\_i\\\}$ の末尾に挿入する。

### 制約

- $2 \\leq N \\leq 10\^5$
- $1 \\leq A\_i \\leq 10\^9$

## 解説

操作で注目しているは偶奇のみなので、 $A\_i$ の代わりに、その偶奇のみを持てばいい。
さらに index もどうでもいいため、数列中の偶数と奇数の個数だけを持てばいい。

操作前後で偶数と奇数の個数はどう変化するだろうか。考えられるのは以下の 2 通り。

1. $A\_i, A\_j$ がともに偶数の場合。  
   $A\_i + A\_j$ は偶数なので、偶数が 1 個減る

2. $A\_i, A\_j$ がともに奇数の場合。  
   $A\_i + A\_j$ は偶数なので、奇数が 2 個減り、偶数が 1 個増える

以上より、偶数は 1 個ずつ減らすことができる一方で、奇数は 2 個ずつしか減らすことができない。
よって「$\\\{A\_i\\\}$ の長さを 1 にできる」ことの必要十分条件は、「**$\\\{A\_i\\\}$ に奇数が偶数個含まれる**」こととなる。

## 実装例

[提出 #4780154 - AtCoder Grand Contest 010](https://atcoder.jp/contests/agc010/submissions/4780154)

```cpp
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int oddcnt = 0;
    for (int i = 0; i < N; ++i) {
        int A;
        cin >> A;

        // 2で割った余りを足すことで、奇数の場合のみ1を加算
        oddcnt += A % 2;
    }

    cout << (oddcnt % 2 == 0 ? "YES" : "NO") << endl;
    return 0;
}
```

