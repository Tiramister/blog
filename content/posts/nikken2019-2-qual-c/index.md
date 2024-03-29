---
title: "第二回全国統一プログラミング王決定戦予選 C - Swaps"
date: 2019-11-10
tags: [atcoder]
---

[C - Swaps](https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_c)

## 問題

長さ $n$ の数列 $(a\_i), (b\_i)$ が与えられる．
$(a\_i)$ に対して 2 点スワップを $n - 2$ 回まで行うことで，任意の $i$ について $a\_i \\leq b\_i$ とできるか判定せよ．

### 制約

- $2 \\leq n \\leq 10\^5$
- $1 \\leq a\_i, b\_i \\leq 10\^9$

## 考察

まず適当に並び替えることで， $(b\_i)$ を昇順としてよい．

ここで $(a\_i)$ を昇順にしたものを $(a\'\_i)$ としたとき， $a\'\_i \\gt b\_i$ なる $i$ が存在すればどれだけスワップしても条件は満たせない．

そうでない場合， $n - 1$ 回スワップすれば $(a\_i)$ をソートできるため，条件は満たせる．
これと同様に， $n - 2$ 回の 2 点スワップによって $n - 2$ 要素をソート済みにする(つまり $a\_i = a\'\_i$ にする)ことが必ずできる．
そこで $b\_i \\leq a\'\_\{i + 1\}$ なる $i$ が存在すれば， $a\'\_i$ と $a\'\_\{i + 1\}$ はソートする必要がない．よってこのときは OK となる．

そうでない場合，必ず $(a\_i)$ は昇順にソートしなくてはならない．さらに上の条件から， $(a\_i)$ は全要素異なる．
よって「長さ $n$ の順列を $n - 2$ 回の 2 点スワップでソートできるか？」という問題に帰着できる．

色々考えてみると，「頂点数 - **順列グラフの強連結成分数** 」回の 2 点スワップで順列はソートできることが分かる．
よって UnionFind などを使えば簡単に判定できる．

ちなみに「必要な 2 点スワップの回数の最小値」は(揃える順番に依らず)貪欲に揃えていった場合と同じになるので，シミュレーションで判定することもできる．本番はそうしていた．

## 実装例

[提出 #8374236 - 第二回全国統一プログラミング王決定戦予選](https://atcoder.jp/contests/nikkei2019-2-qual/submissions/8374236)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

struct UnionFind { ... };

void fail() { ... }
void succ() { ... }

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (auto& x : a) std::cin >> x;
    for (auto& x : b) std::cin >> x;

    {
        // bを昇順にする
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(),
                  [&](int i, int j) { return b[i] < b[j]; });

        auto oa = a, ob = b;
        for (int i = 0; i < n; ++i) {
            a[i] = oa[idx[i]];
            b[i] = ob[idx[i]];
        }
    }

    // そもそも達成可能か
    auto sa = a;
    std::sort(sa.begin(), sa.end());
    for (int i = 0; i < n; ++i) {
        if (sa[i] > b[i]) fail();
    }

    // 全体をソートしなくて良いか
    for (int i = 0; i + 1 < n; ++i) {
        if (sa[i + 1] <= b[i]) succ();
    }

    // 座圧して順列に変換
    std::map<int, int> reva;
    for (int i = 0; i < n; ++i) reva[sa[i]] = i;
    for (auto& x : a) x = reva[x];

    // 連結成分数でスワップ回数を判定
    UnionFind uf(n);
    for (int i = 0; i < n; ++i) uf.unite(i, a[i]);

    if (uf.gnum > 1) {
        succ();
    } else {
        fail();
    }
    return 0;
}
```

