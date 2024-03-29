---
title: "diverta 2019 Programming Contest 2 E - Balanced Piles"
date: 2019-06-16
tags: [atcoder]
---

[E - Balanced Piles](https://atcoder.jp/contests/diverta2019-2/tasks/diverta2019_2_e)

## 問題

$N$ 個の何も置かれていないマスがある。
以下の操作を繰り返すことで、全てのマスに $H$ 個のブロックが
積まれているようにしたい。

- 積まれているブロック数の最大値を $M$ 、最小値を $m$ とする。
- $m$ 個のブロックが積まれているマスを 1 つ選び、 $M$ 個以上 $M + D$ 個以下になるように正の数だけブロックを積む。

このような積み方の総数を求めよ。

### 制約

- $1 \\leq N \\leq 10\^6$
- $1 \\leq D \\leq H \\leq 10\^6$

## 考察

※ 以下を読む前に、pekempey さんのブログがとても分かりやすいので
そちらを先に読むことをオススメします。
[diverta 2019 Programming Contest\. E \- Balanced Piles \- pekempey's blog](https://pekempey.hatenablog.com/entry/2019/06/16/002247)

本番では「ブロック数の最大値が鍵なんだろうなぁ」と思いながら何とかして状態をまとめようとしたが、「最小の山の数」を使うのにどうしても全ブロックを持つ必要があって行き詰まってしまった。

実は発想自体は近いというか逆で、操作を「最小の山から 1 つ選んで積む」のではなく、「最小の山に積んだ後、 **最大の山のうちどこに挿れるか選ぶ** 」と見る、というものだった。
つまり、積んでしまった時点で後で選ぶときの優先順位を決めてしまうのである。
これなら保持するべきは「最大の山の数」になり、全ブロックを持つ必要がなくなる。

まず、操作中に一度は積まれることになるブロック数の集合を $A$ ($0, H \\in A$ , 0-indexed)とし、 $K = |A|$ とする。
この $K$ 種類の数は、間隔が $D$ 以下でないといけない。
そして $dp\'\_\{k, l\}$ を「ブロック数の最大値が $A\_k$ で、そのような山の数が $l$ 個となるような操作数」とする( $1 \\leq k \\leq K - 1, 1 \\leq l \\leq N$ )。
この数列の漸化式を考えると、以下のようになる。

$$
\\begin\{aligned\}
dp\'\_\{k + 1, 1\} &= \\sum\_\{l = 1\}\^\{N\} dp\'\_\{k, l\}  \\\\
dp\'\_\{k, l + 1\} &= (l + 1) dp\'\_\{k, l\}
\\end\{aligned\}
$$

これを整理すると、 $dp\'\_\{k + 1, 1\} = dp\'\_\{k, 1\} \\sum\_\{l = 1\}\^\{N\} l!$ という式が得られる。以降 $F = \\sum\_\{l = 1\}\^\{N\} l!$ とする。

次に、 $dp\_\{h\}$ の定義を「ブロック数の最大値が $h$ で、そのような山の数が 1 個となるような操作数」とする。上の漸化式を利用すると、以下のような漸化式が求まる。

$$
dp\_h = F \\sum\_\{i = \\max(0, h - D)\}\^\{h - 1\} dp\_i
$$

これは $dp$ の累積和を持つことで $O(H)$ で埋められる。

最終的な優先順位は区別しないことから、解は $dp\_H$ となる(個数 $H$ の山が 1 つできたら、優先順位の高い順に $H$ にしていくのみ)。

最後にずっと放置していた初期条件について。
最初の優先順位は自由に決められることから $dp\_0 = N!$ としたくなる。
しかし、 $dp\_0$ から $dp\_h$ に遷移するときは上の漸化式の係数がつかない(「0 個になるように積む」という操作はできないため)。
これは $dp\_0 = N! \\cdot F\^\{-1\}$ とすることで打ち消されていい感じになる。

## 実装例

[提出 #5942337 - diverta 2019 Programming Contest 2](https://atcoder.jp/contests/diverta2019-2/submissions/5942337)

```cpp
template <int MOD> class ModInt { ... }
template <int MOD> class Combination { ... }

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;
const Combination<MOD> C(1 << 20);

int main() {
    /* ----- 入力 ----- */
    int N, H, D;
    cin >> N >> H >> D;

    /* ----- 1! + ... + N! ----- */
    mint fsum = 0;
    for (int l = 1; l <= N; ++l) {
        fsum += C.fact(l);
    }

    /* ----- DP ----- */
    vector<mint> dp(H + 1, 0), dpsum(H + 1, 0);
    dp[0] = dpsum[0] = C.fact(N) / fsum;
    // dp[h] = ブロック数の最大値がhで、そのような山の数が1個となるような操作数

    for (int h = 1; h <= H; ++h) {
        dp[h] = fsum * (dpsum[h - 1] -
                        (h - D - 1 >= 0 ? dpsum[h - D - 1] : 0));
        dpsum[h] = dpsum[h - 1] + dp[h];
    }

    cout << dp[H] << endl;
    return 0;
}
```

