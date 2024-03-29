---
title: "JOI2018 予選 F - L 番目の K 番目の数 (LthKthNumber)"
date: 2020-01-26
tags: [joi]
---

[0646 < JOI Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/JOI/Prelim/0646)

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる．

この数列の全ての長さ $k$ 以上の連続部分列に対し， $k$ 番目に小さい値を紙に書き出す．

紙に書かれた値のうち， $l$ 番目に小さい値を求めよ．

### 制約

- $1 \\leq n \\leq 2 \\times 10\^5$
- $1 \\leq k \\leq n$
- $1 \\leq a\_i \\leq n$
- $1 \\leq l$
- 常に紙には $l$ 個以上の値が書かれることが保証される．

## 考察

まず数列中の同じ値に対して「左側の方が小さい」と順序付けることで，数列の要素は全て異なると考えることができる．

二分探索を軸に考える．「 $a$ が $l$ 番目以降」というのは「 $a$ 以下の値が $l$ 個以上紙に書かれた」と同値なので，「 $a$ 以下の値がいくつ紙に書かれたか？」，すなわち「小さい方から $k$ 番目の値が $a$ 以下である連続部分列はいくつあるか？」という問題を考える．

「数列の小さい方から $k$ 番目の値が $a$ 以下」というのは「数列に $a$ 以下の値が $k$ 個以上含まれる」と同値．そこで各 $i$ について「区間 $[i, j]$ が $a$ 以下の値を $k$ 個以上含むような最小の $j$ 」を取れば， $i$ を左端とし条件を満たす連続部分列の個数は $n + 1 - j$ 個となる．そして $a$ 以下の個数を保持しながら尺取り法を行うことで， $O(n)$ で全ての $i$ に対する $j$ が求まる．

よって二分探索と合わせると， $O(n \\log n)$ でこの問題が解けた．

## 実装例

[Run #4131812 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/0646/review/4131812/misteer/C++14)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;

void solve() {
    int n, k;
    lint m;
    std::cin >> n >> k >> m;

    // (a_i, i)
    std::vector<std::pair<int, int>> ps(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> ps[i].first;
        ps[i].second = i;
    }

    // ソートして座圧
    std::sort(ps.begin(), ps.end());
    std::vector<int> ord(n);
    for (int j = 0; j < n; ++j) {
        ord[ps[j].second] = j;
    }

    int ok = n, ng = 0;
    // ok以下がk番目になる部分列の個数>=m
    while (ok - ng > 1) {
        int mid = (ok + ng) / 2;

        lint sum = 0;
        int cnt = 0, r = -1;
        // 尺取り法 区間[l, r]を見ている
        for (int l = 0; l < n; ++l) {
            while (r < n && cnt < k) {
                ++r;
                if (r < n && ord[r] <= mid) ++cnt;
            }
            sum += n - r;
            if (ord[l] <= mid) --cnt;
        }

        (sum >= m ? ok : ng) = mid;
    }

    std::cout << ps[ok].first << std::endl;
}
```

