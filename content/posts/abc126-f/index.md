---
title: "AtCoder Beginner Contest 126 F - XOR Matching"
date: 2019-05-20
tags: [atcoder]
---

[F - XOR Matching](https://atcoder.jp/contests/abc126/tasks/abc126_f)

## 問題

以下の条件を満たす長さ $2\^\{M+1\}$ の数列 $\\\{a\_i\\\}$ を、存在するならば 1 つ構成せよ。

- $0, 1, \\cdots, 2\^M - 1$ がそれぞれ丁度 2 回ずつ現れる。
- $a\_i = a\_j$ なる任意の $i, j \\, (i \\lt j)$ について、 $a\_i \\oplus a\_\{i + 1\} \\oplus \\cdots \\oplus a\_j = K$ 。

ここで $\\oplus$ は bitwise xor を表す。

### 制約

- $0 \\leq M \\leq 17$
- $0 \\leq K \\leq 10\^9$

## 考察

これといって良いアイデアが浮かばなかったので、とりあえず以下のコードで実験することにした。


```cpp
int main() {
    int M;
    cin >> M;

    int S = 1 << M;
    vector<int> A(S * 2);  // {0, 0, 1, 1, ..., 2^M-1, 2^M-1}
    for (int i = 0; i < S; ++i) {
        A[i * 2] = A[i * 2 + 1] = i;
    }

    // next_permutationで全パターンを調べる
    do {
        vector<int> acc(S * 2 + 1, 0);  // 累積xor
        for (int i = 0; i < S * 2; ++i) {
            acc[i + 1] = acc[i] ^ A[i];
        }

        // 上の式で区間xorを計算
        set<int> B;
        for (int i = 0; i < S * 2; ++i) {
            for (int j = i + 1; j < S * 2; ++j) {
                if (A[i] == A[j]) B.insert(acc[i] ^ acc[j] ^ A[i]);
            }
        }

        // 区間xorの値が1種類なら条件成立
        if (B.size() == 1) {
            cout << *B.begin() << ":" << A << endl;
            // setの出力はテンプレでwrapしてある
        }
    } while (next_permutation(A.begin(), A.end()));

    return 0;
}
```

$M = 2, K = 1$ の解を求めると以下の通り。

```
...
0:[0,0,3,3,2,2,1,1,]
1:[0,1,0,2,3,1,3,2,]
1:[0,1,0,3,2,1,2,3,]
0:[0,1,1,0,2,2,3,3,]
...

```

`1:[0,1,0,3,2,1,2,3,]` がとても好例で、ここから $a, b, c, \\cdots, c, b, a$ のように配置をすると $a\_i = a, b, c$ の場合に値が一致することに気づく。この $\\cdots$ の部分が $K$ になるようにすればいい。というか $K$ 単体をそこに置けばいい。

これで $a\_i \\neq K$ なる $i$ については条件が満たされたが、 $a\_i = K$ ではどうだろうか。何とも都合のいいことに、 **$M \\geq 2$ では**

$$
0 \\oplus 1 \\oplus \\cdots K - 1 \\oplus K + 1 \\oplus \\cdots \\oplus 2\^M - 1 = K
$$

が成立する。これは $i \\equiv 3 \\pmod\{4\}$ で $0 \\oplus 1 \\oplus \\cdots \\oplus i = 0$ となることから従う。
よって $M \\geq 2$ かつ $K \\lt 2\^M$ では、

$$
\\\{0, 1, \\cdots, K - 1, K + 1, \\cdots, 2\^M - 1, K, \\\\
2\^M - 1, \\cdots, K + 1, K - 1, \\cdots, 1, 0, K\\\}
$$

が解となる。 $K \\geq 2\^M$ ではそもそも $K$ が作れないので解なし。

そしてコーナーケースである $M \\leq 1$ 。 $M = 0$ では $K = 0$ のみ解あり ($\\\{0, 0\\\}$) で、 $M = 1$ ではサンプルに答えがある。

## 実装例

[提出 #5484245 - AtCoder Beginner Contest 126](https://atcoder.jp/contests/abc126/submissions/5484245)

```cpp
#include <iostream>

using namespace std;

int main() {
    int M, K;
    cin >> M >> K;

    // コーナーケース
    // M=0は下とまとめて良い
    if (M == 1) {
        if (K >= 1) {
            cout << -1 << endl;
        } else {
            cout << "0 0 1 1" << endl;
        }
        return 0;
    }

    // 可能性判定
    if (K >= (1 << M)) {
        cout << -1 << endl;
        return 0;
    }

    // 前半の出力
    for (int i = 0; i < (1 << M); ++i) {
        if (i != K) {
            cout << i << " ";
        }
    }
    cout << K << " ";

    // 後半の出力(逆順にするだけ)
    for (int i = (1 << M) - 1; i >= 0; --i) {
        if (i != K) {
            cout << i << " ";
        }
    }
    cout << K << " " << endl;

    return 0;
}
```
