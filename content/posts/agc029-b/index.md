---
title: "AtCoder Grand Contest 029 B - Powers of two"
date: 2018-12-23
tags: [atcoder]
---

[B - Powers of two](https://atcoder.jp/contests/agc029/tasks/agc029_b)

## 概要

整数が書かれた $N$ 個のボールがある。 $i$ 個目のボールには $A\_i$ が書かれている。

これらのボールからいくつかのペアを作り、各ペアに書かれた整数の和が 2 べきとなるようにしたい。最大でいくつのペアを作れるか求めよ。

### 制約

- $1 \\leq N \\leq 2 \\times 10\^5$
- $1 \\leq A\_i \\leq 10\^9$

## 考察

ボールに書かれた最大の整数 $X$ に注目する。実は、 **$X$ とペアにできる整数は高々 1 つしか存在しない** ことが示せる。

{{<collapse summary="証明">}}
$X \\lt 2\^p$ を満たす最小の整数 $p$ を取る。このとき $2\^p - X$ は $X$ のペアの(唯一の)候補となる。

他のペア候補は $p$ より大きい整数 $q$ によって $2\^q - X$ と表される。このとき、

$$
2\^q - X \\geq 2\^\{p + 1\} - X = 2\^p + (2\^p - X) \\gt 2\^p \\gt X
$$

より $2\^q - X \\gt X$ となる。そして $X$ の最大性より、 $2\^q - X$ が書かれたボールは存在しない。$\\square$
{{</collapse>}}

もし $X$ の唯一のペア候補が書かれたボールが存在しなければ、このボールは使えないので無視していい。

一方で $X$ とペアになれるボール $i$ が存在すれば、それと組むのが最善となる。
最適解でボール $i$ がペアを組んでいる場合、このペアを解除して $X$ が書かれたボールとペアにすれば、再び最適解が得られるためである。

## 実装例

[提出 #3853555 - AtCoder Grand Contest 029](https://atcoder.jp/contests/agc029/submissions/3853555)

```cpp
#include <iostream>
#include <map>

using namespace std;

int mypow(int b, int n) {
  if (n == 0) return 1;
  if (n == 1) return b;
  if (n % 2 == 0) {
    return mypow(b * b, n / 2);
  } else {
    return mypow(b, n - 1) * b;
  }
}

// n < 2^kなる最小の2^kを返す
int minbeki(int n) {
  int ret = 1;
  while (n >= ret) {
    ret *= 2;
  }
  return ret;
}

int main() {
  int N;
  cin >> N;

  map<int, int> cnt;
  // key = 書かれた整数, value = ボールの個数

  for (int i = 0; i < N; ++i) {
    int a;
    cin >> a;
    if (cnt.find(a) == cnt.end()) cnt[a] = 0;
    ++cnt[a];
  }

  int ans = 0;

  // cntをkeyが大きい方から見ていく
  for (auto itr = cnt.rbegin(); itr != cnt.rend(); ++itr) {
    int b = itr->first;
    if (cnt[b] == 0) continue;

    int a = minbeki(b) - b;
    // bとペアになりうる整数aを求める

    if (a == b) {
      // bと書かれたボール同士でペアを作る
      ans += cnt[b] / 2;
    } else {
      if (cnt.find(a) == cnt.end()) continue;
      // aと書かれたボールが存在しなければ次へ

      // 少ない方に合わせてペアを作る
      ans += min(cnt[a], cnt[b]);
      cnt[a] -= min(cnt[a], cnt[b]);
    }
  }

  cout << ans << endl;
  return 0;
}
```

