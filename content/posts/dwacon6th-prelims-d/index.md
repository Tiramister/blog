---
title: "第 6 回 ドワンゴからの挑戦状 予選 D - Arrangement"
date: 2020-01-12
tags: [atcoder]
---

[D - Arrangement](https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_d)

## 問題

長さ $n$ の順列 $\\\{ p\_i \\\}$ で，以下を満たすものが存在するか判定し，存在するなら 1 つ出力せよ．

- 任意の $1 \\leq i \\leq n$ に対し， $i$ の次は(存在すれば) $a\_i$ ではない．

### 制約

- $2 \\leq n \\leq 10\^5$
- $1 \\leq a\_i \\leq n$
- $a\_i \\neq i$

## 考察

後ろから決めることを考えると，「 $K$ 以外全部 $K$ を指している」ようなケースがまずいことに気づく．このとき $K$ 以外の値を先頭にすると，それ以降 $K$ が置けなくなってしまうからだ．

そこで，以下のような貪欲アルゴリズムを考えた．

- まだ決まっていないかつ直前に指されていない，最も小さい値を $x$ とする．
  - そのような値がない場合は NO．
- $a\_x$ がまだ決まっていないかつ， $a\_x$ 以外の決まっていない数が全て $a\_x$ を指していた場合， $x$ を $a\_x$ に変える．
- これは各値の指されている数を保持すれば判定できる．
- $x$ を解の末尾に追加し，カウント等を更新する．

これで概ね良いのだが，愚直解と突き合わせると $\\\{ 3, 1, 1, 1, 6, 5 \\\}$ のように最後 2 つが指し合っているケースなどで NO と判定してしまうことが分かる．このときの答えは $\\\{ 1, 2, 3, 5, 4, 6 \\\}$ で，最後 3 つでやりくりすると上手くいく．

これらを最後まで詰めるのは流石に厳しいと思い，「最後 $6$ 要素を全探索する」としたら通った．

## 実装例

最後の全探索は 3 要素でも通る．

[提出 #9474639 - 第6回 ドワンゴからの挑戦状 予選](https://atcoder.jp/contests/dwacon6th-prelims/submissions/9474639)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), cnt(n, 0);
    for (auto& x : xs) {
        std::cin >> x;
        ++cnt[--x];
    }

    std::set<int> ss;
    for (int x = 0; x < n; ++x) ss.insert(x);
  	// まだ決まっていない数の集合

    std::vector<int> ans;
    ans.reserve(n);

    int out = -1;  // 直前の数に指されている数
    while (ss.size() > 3) {
        int x = *ss.begin();
        if (x == out) {
          	// 指されていたら次へ
            if (ss.size() == 1) {
                std::cout << -1 << std::endl;
                return 0;
            } else {
                x = *(++ss.begin());
            }
        }

        int k = ss.size();
        int y = xs[x];
        if (ss.count(y) && cnt[y] == k - 1) x = y;
      	// y以外がyを指している場合

        ss.erase(x);
        ans.push_back(x);
        --cnt[xs[x]];
        out = xs[x];
    }

  	// 最後の全探索
    std::vector<int> rem(ss.begin(), ss.end());
    do {
        auto tmpans = ans;
        for (auto x : rem) ans.push_back(x);

        bool ok = true;
        for (int i = 0; i < n - 1; ++i) {
            if (ans[i + 1] == xs[ans[i]]) ok = false;
        }

        if (ok) {
            for (auto x : ans) std::cout << x + 1 << " ";
            std::cout << std::endl;
            return 0;
        }

        ans = tmpans;
    } while (std::next_permutation(rem.begin(), rem.end()));

    std::cout << -1 << std::endl;
    return 0;
}
```

