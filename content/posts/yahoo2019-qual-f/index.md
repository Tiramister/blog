---
title: "みんなのプロコン 2019 予選 F - Pass"
date: 2019-02-10
tags: [atcoder]
---

[F - Pass](https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_f)

## 概要

$1$ から $N$ の番号が振られた $N$ 人が一列に並んでいる。最初、人 $i$ は赤いボールを $x\_i$ 個、青いボールを $2 - x\_i$ 個持っている。

これから、以下の操作を $2N$ 回繰り返すことでボール列を作る。最初、ボール列は空である。

- 各 $i = 2, \\dots, N$ について、 人 $i$ は持っているボールのうち 1 つを人 $i - 1$ に渡す。ただしボールを持っていなければ何もしない。
- 人 $1$ は、持っているボールのうち 1 つをボール列の末尾に置く。

なお、これらのボールの受け渡しは同時に行われる。

こうして作られたボール列として考えうるものの数を求めよ。

### 制約

- $1 \\leq N \\leq 2,000$

## 考察

1 回目は 人 1 が持っていたボールしか置けないが、2 回目は人 2 が持っていたボールも好きに置けるようになる(最初の操作で、置きたいボールを人 2 に渡して貰えばいい)。これと同様の理屈で、 **$i$ 回目での操作では、 $i$ 人目までのボールを好きに選べる** という事実が成り立つ。

そこで、以下の DP を考える。

$$
\\begin\{aligned\}
dp\_\{r, b\} =& \\; \\text\{$r + b$ 回目の操作終了時点における、\} \\\\
  &\\text\{赤いボール $r$ 個、青いボール $b$ 個からなるボール列の数\}
\\end\{aligned\}
$$

赤いボールが $r$ 個、青いボールが $b$ 個並んだ状態を考える。次の操作は $r + b + 1$ 回目なので、 $r + b + 1$ 人目までの赤いボールの個数が $r$ を上回っていれば赤いボールを置くことができる。よってこのとき $dp\_\{r + 1, b\} \\mathrel{+}= dp\_\{r, b\}$ という遷移ができる。青いボールも同様。

## 実装例

[提出 #34682408 - 「みんなのプロコン 2019」](https://atcoder.jp/contests/yahoo-procon2019-qual/submissions/34682408)

```cpp
#include <atcoder/modint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using mint = atcoder::modint998244353;

int main() {
  string s;
  cin >> s;
  int n = s.length();

  // 各ボールの個数の累積和
  vector<int> rsum(n * 2 + 1), bsum(n * 2 + 1);
  rsum[0] = bsum[0] = 0;

  for (int i = 0; i < n; ++i) {
    int b = s[i] - '0';
    rsum[i + 1] = rsum[i] + 2 - b;
    bsum[i + 1] = bsum[i] + b;
  }
  for (int i = n; i < n * 2; ++i) {
    rsum[i + 1] = rsum[i];
    bsum[i + 1] = bsum[i];
  }

  auto dp = vector(rsum[n] + 1, vector(bsum[n] + 1, mint(0)));
  dp[0][0] = 1;
  for (int r = 0; r <= rsum[n]; ++r) {
    for (int b = 0; b <= bsum[n]; ++b) {
      if (r + b == n * 2) continue;

      // 赤ボールを置けるか？
      if (rsum[r + b + 1] > r) dp[r + 1][b] += dp[r][b];
      // 青ボールを置けるか？
      if (bsum[r + b + 1] > b) dp[r][b + 1] += dp[r][b];
    }
  }

  cout << dp[rsum[n]][bsum[n]].val() << "\n";
  return 0;
}
```

