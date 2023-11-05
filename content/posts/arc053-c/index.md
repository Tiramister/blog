---
title: "AtCoder Regular Contest 053 C - 魔法使い高橋君"
date: 2019-10-30
tags: [atcoder]
---

[C - 魔法使い高橋君](https://atcoder.jp/contests/arc053/tasks/arc053_c)

## 問題

$n$ 個の気温を変える魔法があり， $i$ 番目の魔法は「気温を $a\_i$ 度上げてから $b\_i$ 度下げる」という効果がある．

最初気温は $0$ 度で，ここから各魔法を好きな順番で一度ずつ唱える．
このとき，途中の気温の最大値を最小化せよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $1 \\leq a\_i, b\_i \\leq 10\^9$

## 考察

座布団 DP のように，隣接する要素について「スワップしても損しない」ような条件を考える．

まず $a\_i - b\_i$ の正負，すなわち魔法を唱えた後気温が下がるかどうかに着目する．
もしも $a\_i - b\_i \\geq 0, a\_\{i + 1\} - b\_\{i + 1\} < 0$ なら，この 2 要素はスワップした方が良い．これは以下から従う。，

$$
\\begin\{aligned\}
\\max(a\_i, a\_i - b\_i + a\_\{i + 1\})
&\\geq \\max(a\_i, a\_\{i + 1\}) \\\\
&\\geq \\max(a\_\{i + 1\} - b\_\{i + 1\} + a\_i, a\_\{i + 1\})
\\end\{aligned\}
$$

よって前半に $a\_i - b\_i < 0$ のもの，後半に $a\_i - b\_i \\geq 0$ のものを詰めて良いことが分かった．後はこの中で最適な並べ方を考えればいい．

まず $a\_i - b\_i < 0$ の方から．実はこのとき，「 $a\_i$ について昇順に並べる」のが最善．これは $a\_i > a\_\{i + 1\}$ のとき以下より従う。

$$
\\begin\{aligned\}
\\max(a\_\{i + 1\}, a\_\{i + 1\} - b\_\{i + 1\} + a\_i)
&\\leq \\max(a\_i, a\_\{i + 1\})
& (\\because a\_\{i + 1\} - b\_\{i + 1\} \\leq 0) \\\\
&= a\_i \\\\
&= \\max(a\_i, a\_i - b\_i + a\_\{i + 1\})
& (\\because a\_i > a\_\{i + 1\} \\geq a\_i - b\_i + a\_\{i + 1\})
\\end\{aligned\}
$$

そして $a\_i - b\_i \\geq 0$ の方も，後ろから考えれば $b\_i - a\_i \\leq 0$ なので「後ろから $b\_i$ について昇順」，すなわち「 $b\_i$ について降順」に並べるのが最善となる．

後はこの順にソートしてシミュレーションすれば OK．

## 実装例

[提出 #8218670 - AtCoder Regular Contest 053](https://atcoder.jp/contests/arc053/submissions/8218670)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<lint, lint>> ps(n);
    for (auto& p : ps) {
        std::cin >> p.first >> p.second;
    }

    std::sort(ps.begin(), ps.end(),
              [](auto a, auto b) {
                  bool aneg = a.first < a.second,
                       bneg = b.first < b.second;
                  if (aneg != bneg) {
                      return aneg > bneg;
                  } else if (aneg) {
                      return a.first < b.first;
                  } else {
                      return a.second > b.second;
                  }
              });

    lint ans = 0, sum = 0;
    for (auto p : ps) {
        sum += p.first;
        ans = std::max(ans, sum);
        sum -= p.second;
    }

    std::cout << ans << std::endl;
    return 0;
}
```

