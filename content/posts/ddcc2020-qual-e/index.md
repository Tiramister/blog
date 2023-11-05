---
title: "DDCC 2020 予選 E - Majority of Balls"
date: 2019-11-24
tags: [atcoder]
---

[E - Majority of Balls](https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_e)

## 問題

赤いカード $n$ 枚と青いカード $n$ 枚が伏せた(つまり色が分からない)状態で置かれている．
今から 210 回まで以下の質問をすることで，各カードの色を特定せよ．

- $2n$ 枚のうち， $n$ 枚のカードを指定する．
- 指定したカードのうち，赤いカードと青いカードのどちらが過半数かが返ってくる．

### 制約

- $1 \\leq n \\leq 99$
- $n$ は奇数

## 考察

3 つのステップがいる発想問題．

まず $[0, n)$ に対してクエリを投げる．青が過半数だったとすると， $[n, 2n)$ は赤が過半数なので $[0, n)$ は赤が過半数として一般性を失わない．

$[0, n)$ と $[n, 2n)$ の結果が違うことが本質的で， $[i, n + i)$ に対するクエリの結果を $f(i)$ とすると， $f(i)$ が赤で $f(i + 1)$ が青であるような $0 \\leq i \\lt n$ が存在する．
考えてみると，このとき $i$ 枚目が赤で $i + n$ 枚目が青と分かる．

全体をスライドして， $i = 0$ とする．このとき先の考察の延長として， $[1, n - 1]$ と $[n + 1, 2n - 1]$ の各 $n - 1$ 枚には赤と青が同数含まれることが分かる．

そして $1 \\leq j \\leq n - 1$ について $0, 1, \\cdots, j - 1, j + 1, \\cdots, n$ でクエリを投げると，「赤が過半数」と「 $j$ 枚目が青」が同値であることが分かる．これは $[0, n]$ に赤と青が同数含まれることから従う． $n + 1 \\leq j \\leq 2n - 1$ についても $j$ 枚目の色が同様に求まる．

以上で $3n$ 回程度のクエリでこの問題が解けたが，これではまだ間に合わない．
そこで最後の発想として，前者の探索を 2 分法で行えることに気づく必要がある．これでクエリ数は $2n + \\log n$ に落ちて間に合う．

## 実装例

[提出 #8583931 - DISCO presents ディスカバリーチャンネル コードコンテスト2020 予選](https://atcoder.jp/contests/ddcc2020-qual/submissions/8583931)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

enum Color { red,
             blue };

Color query(const std::vector<int>& v) {
    std::cout << '?';
    for (auto& x : v) {
        std::cout << ' ' << x + 1;
    }
    std::cout << std::endl;

    std::string s;
    std::cin >> s;
    if (s == "Red") return red;
    if (s == "Blue") return blue;
    std::exit(0);
}

void answer(const std::string& s) {
    std::cout << '!' << ' ' << s << std::endl;
    std::exit(0);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> idx(n * 2);
    std::iota(idx.begin(), idx.end(), 0);

    // send query of [l, l + n - 1]
    auto rquery = [&](int l) {
        std::vector<int> v;
        for (int i = 0; i < n; ++i) {
            v.push_back(idx[l + i]);
        }
        return query(v);
    };

    Color c = rquery(0);
    if (c == blue) {
        std::rotate(idx.begin(), idx.begin() + n, idx.end());
    }

    // [0, n-1]: red, [n, 2n-1]: blue
    // search border of query
    int ok = 0, ng = n;
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        c = rquery(mid);
        (c == red ? ok : ng) = mid;
    }

    std::rotate(idx.begin(), idx.begin() + ok, idx.end());
    // [0, n): red, [1, n]: blue

    std::string preans(n * 2, '*');
    preans[0] = 'R';
    preans[n] = 'B';

    // solve former
    for (int i = 1; i < n; ++i) {
        std::vector<int> v{idx[0], idx[n]};
        for (int j = 1; j < n; ++j) {
            if (j == i) continue;
            v.push_back(idx[j]);
        }
        c = query(v);
        preans[i] = (c == red ? 'B' : 'R');
    }

    // solve later
    for (int i = 1; i < n; ++i) {
        std::vector<int> v{idx[0], idx[n]};
        for (int j = 1; j < n; ++j) {
            if (j == i) continue;
            v.push_back(idx[n + j]);
        }
        c = query(v);
        preans[n + i] = (c == red ? 'B' : 'R');
    }

    // convert to answer
    std::string ans(n * 2, '*');
    for (int i = 0; i < n * 2; ++i) {
        ans[idx[i]] = preans[i];
    }

    answer(ans);
    return 0;
}
```

