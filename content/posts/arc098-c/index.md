---
title: "AtCoder Regular Contest 098 C - Attention"
date: 2018-09-21
tags: [atcoder]
---

[C - Attention](https://atcoder.jp/contests/arc098/tasks/arc098_a)

## 概要

$N$ 人の人が東西方向に一直線に並んでいる。西から $i$ 番目の人は東か西の方角を向いている。

今から $N$ 人のうち誰か 1 人をリーダーにする。すると、リーダー以外の全員はリーダーのいる方角を向く。
向きを変える人数の最小値を求めよ。

### 制約

- $2 \\leq N \\leq 3 \\times 10\^5$

## 解説

まず向きを変えるのは、以下の条件を満たす人々である。

- リーダーより西にいて、西を向いている人。
- リーダーより東にいて、東を向いている人。

これを全パターンに対して愚直に数え上げていると、計算量が $O(N\^2)$ で間に合わない。
そこで、 **累積和** によってこれを高速化する。

具体的には、数列 $c$ を以下のように定める。

$$
c\_i = \\text\{$i$ 人目より西にいて、西を向いている人の数\}
$$

すると、 $i$ 人目をリーダーにしたときに振り向く人数は以下で求まる。
$i$ 人目(リーダー)を含めないので、添字が紛らわしいことになっている。

- リーダーより西にいて、西を向いている人が $c\_\{i\}$ 人
- リーダーより東にいて、東を向いている人が $(N - (i + 1)) - (c\_N - c\_\{i + 1\})$ 人

これなら累積和を求めるのに $O(N)$ 、解を求めるのに $O(N)$ で余裕で間に合う。

## 実装例

[提出 #3232780 - AtCoder Regular Contest 098](https://atcoder.jp/contests/arc098/submissions/3232780)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    string S;
    cin >> N >> S;

    int cnt[N + 1];
    // i文字目までにWがいくつあるか(1-indexed)

    // 累積和テーブルを埋めていく
    cnt[0] = 0;
    for (int i = 0; i < N; ++i) {
        cnt[i + 1] = cnt[i];
        if (S[i] == 'W') ++cnt[i + 1];
    }

    int ans = N;
    for (int i = 1; i <= N; ++i) {
        // 自分より西にいて西を向いている人が
        //  cnt[i-1]人
        // 自分より東にいて東を向いている人が
        //  (N-i)-(cnt[N]-cnt[i])人
        ans = min(ans, cnt[i - 1] + (N - i) - (cnt[N] - cnt[i]));
    }
    cout << ans << endl;
    return 0;
}
```

