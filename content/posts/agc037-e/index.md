---
title: "AtCoder Grand Contest 037 E - Reversing and Concatenating"
date: 2020-03-02
tags: [atcoder]
---

[E - Reversing and Concatenating](https://atcoder.jp/contests/agc037/tasks/agc037_e)

## 問題

長さ $N$ の文字列 $S$ が与えられる．今から以下の操作をちょうど $K$ 回行う．

- $S$ を反転させたものを $T$ とし， $U = S + T$ とする．
- $U$ から長さ $N$ の連続部分文字列を 1 つ選び，それで $S$ を置換する．

最終的な $S$ のうち，辞書順最小のものを求めよ．

### 制約

- $1 \\leq N \\leq 5 \\cdot 10\^3$
- $1 \\leq K \\leq 10\^9$

## 考察

まず「最初に与えられた $S$ を反転し，以降 $U = T + S$ から連続部分文字列を選ぶのを $K$ 回繰り返す」と操作を言い換える．操作の対称性から，こうしても得られる文字列の集合は変わらない．

辞書順最小にしたいので，先頭にできるだけ長く $a$ を(もしあれば)連続させたい．そう考えると，「 $S$ の先頭に $a$ を並べて，操作毎に $a$ の個数を倍にする」という操作が思いつく．先頭の $a$ の個数が指数関数的に増えるので，これより強い戦略はないだろう．

後は 1 回目の操作だけ考えれば良いが，上の戦略の元では辞書順最小のものを選ぶのが最善．よって長さ $N$ の連続部分文字列を全て見て，辞書順最小のものを持ってくればいい．これは $O(N\^2)$ でできる．

余談だが，最初の言い換えがないと「 $K-1$ 回は末尾に $a$ を連続させて，最後の操作で先頭に $a$ が連続したものを取る」みたいになって少し考えにくい．

## 実装例

[提出 #10298405 - AtCoder Grand Contest 037](https://atcoder.jp/contests/agc037/submissions/10298405)

```cpp
#include <iostream>
#include <algorithm>
#include <string>

void solve() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;

    std::string u = s;
    std::reverse(u.begin(), u.end());
    u = s + u;

    // 辞書順最小のものを選ぶ
    int si = 0;
    for (int i = 1; i < n; ++i) {
        if (u.substr(i, n) < u.substr(si, n)) si = i;
    }
    u = u.substr(si, n);

    // 先頭の文字がいくつ連続するか調べる
    int l;
    for (l = 0; l < n; ++l) {
        if (u[l] != u[0]) break;
    }
    auto back = u.substr(l);

    // 倍々にする
    --k;
    while (l < n && k > 0) {
        l = std::min(n, l * 2);
        --k;
    }

    // 先頭の文字を連結させて長さnにカット
    auto ans = std::string(l, u[0]) + back;
    ans = ans.substr(0, n);

    std::cout << ans << std::endl;
}
```

## 余談

最初 $O(N\^2)$ は無理だと思っていたが，**Suffix Array** を使えば $O(N)$ で解ける．最初の辞書順最小の連続部分文字列を選ぶパートで SA を使い， $i \\leq N$ で rank が最小の $i$ を始点にすればいい．

[提出 #10298384 - AtCoder Grand Contest 037](https://atcoder.jp/contests/agc037/submissions/10298384)

