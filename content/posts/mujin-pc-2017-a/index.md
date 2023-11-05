---
title: "Mujin Programming Challenge 2017 A - Robot Racing"
date: 2019-11-14
tags: [atcoder]
---

[A - Robot Racing](https://atcoder.jp/contests/mujin-pc-2017/tasks/mujin_pc_2017_a)

## 問題

$n$ 個の石が数直線上に並んでいて，左から $i$ 番目の石は座標 $x\_i$ にある．
このとき石に以下の操作を好きな順で適用することで，数直線上から全ての石を取り除く．

- 石を 1 つ選ぶ( $i$ 番目とする)．
- $x\_i - 1, x\_i - 2$ のいずれかを選ぶ．
- そこに既に石がなければ，そこに石を移動する．
- 操作の結果座標が 0 以下になったら，その石を取り除く．

石を取り除く順序として考えられるものが何通りあるか求めよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $0 \\lt x\_1 \\lt \\cdots \\lt x\_n \\leq 10\^9$

## 考察

「 $k$ 番目の石を最初に取り除けるか？」という問題を考える．
これは「 $1 \\sim k - 1$ 番目の石を 1 つ飛ばしで配置できるか」と同値と分かる．
よって左から石を見ていって，順に座標 $1, 3, 5, \\cdots$ と配置すれば損をしない．

仮に $k$ 番目の石でこのような配置ができなくなったとする．このとき $1 \\sim k$ 番目の石は最初に取り除けるが，それ以降は全て取り除くことはできない．よって $1 \\sim k$ 番目の石のいずれか 1 つを取り除いてしまってよい．取り除く石のパターン数は $k$ 通りで，1 つ石が減ったことで $k$ 番目の石も規則通りに並べることができる．

この後も同様にシミュレーションを続ければ，2 つ目，3 つ目に取り除く石のパターン数が同様にして求まる．これらを掛け合わせて，最後に残った石の数の階乗を掛ければいい．

## 実装例

[提出 #8425050 - Mujin Programming Challenge 2017](https://atcoder.jp/contests/mujin-pc-2017/submissions/8425050)

```cpp
#include <iostream>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int n;
    std::cin >> n;

    mint ans = 1;
    int cnt = 0;  // 今並んでいる石の数
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        if (x < cnt * 2 + 1) {
            // i番目の石も取り除けることに注意
            ans *= (cnt + 1);
            --cnt;
        }
        ++cnt;
    }

    while (cnt > 0) {
        ans *= cnt;
        --cnt;
    }

    std::cout << ans << std::endl;
    return 0;
}
```

