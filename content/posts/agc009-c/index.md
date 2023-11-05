---
title: "AtCoder Grand Contest 009 C - Division into Two"
date: 2019-10-25
tags: [atcoder]
links:
  - label: Problem link
    url: 
  - label: My Submission
    url: 
---

[C - Division into Two](https://atcoder.jp/contests/agc009/tasks/agc009_c)

## 問題

大きさ $n$ の整数からなる集合 $\\\{ s\_1, \\cdots, s\_n \\\}$ が与えられる．
これを以下の条件を満たすように 2 つの集合 $X, Y$ に分割する方法の数を求めよ．

- $X$ に属する任意の異なる 2 要素について，その差の絶対値は $a$ 以上．
- $Y$ に属する任意の異なる 2 要素について，その差の絶対値は $b$ 以上．

### 制約

- $1 \\leq n \\leq 10\^5$
- $1 \\leq a, b \\leq 10\^\{18\}$
- $0 \\leq s\_1 \\lt \\cdots \\lt s\_n \\leq 10\^\{18\}$

## 考察

以下 $a \\geq b$ として一般性を失わない．

$dp\_i =$ 「 $\\\{ s\_1, \\cdots, s\_i \\\}$ を $s\_i$ が $X$ に属するように分割する場合の数」とする．
これを直前に $X$ に属する要素 $j$ によって場合分けして求める．

まずこの $j$ が満たすべき条件として以下の 2 つがある．

- $s\_i - s\_j \\geq a$
- $s\_\{k + 1\} - s\_\{k\} \\geq b$ $(j \\lt k, k + 1 \\lt i)$

前者を満たさ **ない** 最小の $j$ を $r$ ，後者を満たす最小の $j$ を $l$ とする．前者は`upper_bound()`を使って，後者は前計算で前から求めていくことで十分高速に求まる．

このとき **基本的に** $j \\in [l, r)$ を直前に $X$ に属する要素として選べる．
強調したように，上の 2 つは十分条件ではない．
実際，唯一の反例として $s\_j \\in X$ で $s\_\{j + 1\} - s\_\{j - 1\} \\lt b$ のケースがある．

ただ「基本的に」といったように， $j \\in (l, r)$ ならこのようなことは起こらない ($\\because s\_\{j + 1\} - s\_\{j - 1\} \\geq s\_\{j + 1\} - s\_j \\geq b$)．

よって $j = l$ のときを考える．
$s\_\{l + 1\} - s\_\{l - 1\} \\lt b$ のとき， $s\_l \\in X$ なら $s\_\{l - 1\} \\not \\in X$ となる $(\\because s\_l - s\_\{l - 1\} \\lt s\_\{l + 1\} - s\_\{l - 1\} \\lt b \\leq a)$ ．
ここから，「 $s\_\{l + 1\} - s\_\{l - 1\} \\lt b$ 」と「 $j = l$ とできるか」が同値となる．

これで $j$ として選べる値の範囲が分かったので， $dp\_i = \\sum\_\{j = l\}\^\{r - 1\} dp\_j$ と更新すればいい．
これはセグ木か累積和で十分高速にできる．

最後に答えだが，「 $X$ に属する一番最後の値になりうる範囲」は上の $l$ を求めるのと全く同じ要領でできるので，そこから後ろの和を出力すればいい．

## 実装例

初期条件を真面目に考えたり全部 $Y$ に入っているケースがあったりして，考察を詰め切るのが結構難しい．

[提出 #8119505 - AtCoder Grand Contest 009](https://atcoder.jp/contests/agc009/submissions/8119505)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <limits>

template <int MOD>
class ModInt { ... };
template <class Data, class Operator>
class SegmentTree { ... };

using lint = long long;

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int n;
    lint a, b;
    std::cin >> n >> a >> b;
    if (a < b) std::swap(a, b);
    // a >= b

    std::vector<lint> s(n);
    for (auto& x : s) std::cin >> x;

    std::vector<int> prevb(n);
    // [j, i]の任意の要素の差がb以上な最小のj
    prevb[0] = 0;
    for (int i = 1; i < n; ++i) {
        prevb[i] = (s[i] - s[i - 1] >= b ? prevb[i - 1] : i);
    }

    SegmentTree<mint, mint> seg(
        n, 0,
        [](mint a, mint b) { return a + b; },
        [](mint e, mint a) { return a + e; });
    // iがXに属する場合の数

    seg.update(0, 1);
    for (int i = 1; i < n; ++i) {
        int l = prevb[i - 1];
        int r = std::upper_bound(s.begin(), s.end(), s[i] - a) - s.begin();
        if (l - 2 < 0 || s[l] - s[l - 2] >= b) --l;
        // [l, r)を直前のXに属する要素として選択可能
        seg.update(i, seg.query(l, r));

        if (prevb[i - 1] == 0) {
            // [0, i)を全部Yに，iをXに入れられる
            seg.update(i, 1);
        }
    }

    // 最後のAに属する要素が置かれうる範囲
    int l = prevb[n - 1];
    if (l - 2 < 0 || s[l] - s[l - 2] >= b) --l;
    mint ans = seg.query(l, n);

    // 全部Yに入るケース
    if (l < 0) ++ans;

    std::cout << ans << std::endl;
    return 0;
}

```
