---
title: AtCoder Regular Contest 080 E - Young Maids
date: 2020-11-26
tags: [atcoder]
---

[E - Young Maids](https://atcoder.jp/contests/arc080/tasks/arc080_c)

## 問題

長さ $N$ の順列 $(p\_i)$ がある。これから以下の操作を $(p\_i)$ が空になるまで繰り返して、順列 $(q\_i)$ を作る。最初 $(q\_i)$ は空である。

- $(p\_i)$ の隣接する 2 要素を選ぶ(順に $x, y$ とする)。
- $x,y$ を $(p\_i)$ から削除し、 $x, y$ をこの順に $(q\_i)$ の **先頭** に挿入する。

$(q\_i)$ として考えられるもののうち、辞書順最小のものを求めよ。

### 制約

- $2 \\leq N \\leq 2 \\cdot 10\^5$
- $N$ は偶数

## 考察

辞書順最小なので、先頭の要素が決まる最後の操作から考える。

最後に選んだ要素が $p\_i, p\_j$ だったとする。
このとき、それより前に選ばれたペアは $p\_i, p\_j$ をどちらも跨いではいけない。
つまり、操作後に数列が $[0, i), [i+1, j), [j+1, N)$ の 3 つの区間に分割される、と考えられる。

各区間は長さが偶数でないと数列が作れない。
よって $i, j$ がそれぞれ(0-indexed で)偶数、奇数でないといけない。
以上より、

- $i$ が偶数
- $j$ が奇数
- $i \\lt j$

を満たす $i, j$ のうち、 $p\_i, p\_j$ が辞書順最小であるものを選ぶのが最善となる。
このような $p\_i, p\_j$ は偶数、奇数番目のみをまとめた最小値取得セグメント木で求められる。最小値の index が欲しくなるが、これは値と一緒に index を持たせればよい。

その後は区間 $[0, i), [i+1, j), [j+1, N)$ から 1 つを選び、その中のペアを同様に選ぶ。
これも貪欲に選びたいので、区間 $[l, r)$ を選べる最小の $x$ と一緒に heap で管理すれば、常に最善の区間を選べる。

## 実装例

[提出 #18402693 - AtCoder Regular Contest 080](https://atcoder.jp/contests/arc080/submissions/18402693)

```cpp
#include <atcoder/segtree>
#include <iostream>
#include <vector>
#include <queue>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using namespace std;

struct Data {
    int val, idx;
    explicit Data(int val, int idx) : val(val), idx(idx) {}

    static Data op(Data a, Data b) { return a.val <= b.val ? a : b; }
    static Data e() { return Data(1 << 30, -1); }
};

void solve() {
    int n;
    cin >> n;

    atcoder::segtree<Data, Data::op, Data::e> eseg(n), oseg(n);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        (i % 2 == 0 ? eseg : oseg).set(i, Data(p, i));
    }

    vector<int> ans;

    MinHeap<tuple<int, int, int>> heap;
    // val, [l, r)

    // 区間[l, r)を(空でなければ)最小値と共に追加
    auto push = [&](int l, int r) {
        if (r <= l) return;
        auto d = (l % 2 == 0 ? eseg : oseg).prod(l, r);
        heap.emplace(d.val, l, r);
    };

    push(0, n);
    while (!heap.empty()) {
        auto [v, l, r] = heap.top();
        heap.pop();

        auto x = (l % 2 == 0 ? eseg : oseg).prod(l, r);
        auto lr = x.idx;
        ans.push_back(x.val);

        auto y = (l % 2 == 0 ? oseg : eseg).prod(lr, r);
        auto rl = y.idx;
        ans.push_back(y.val);

        push(l, lr);
        push(lr + 1, rl);
        push(rl + 1, r);
    }

    for (auto p : ans) cout << p << " ";
    cout << "\n";
}
```

