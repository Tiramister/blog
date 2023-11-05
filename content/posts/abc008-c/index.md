---
title: "AtCoder Beginner Contest 008 C - コイン"
date: 2018-06-19
tags: [atcoder]
---

[C - コイン](https://atcoder.jp/contests/abc008/tasks/abc008_3)

## 概要

整数が書かれたコインが $N$ 枚ある。 $i$ 枚目のコインには $C\_i$ が書かれている。

最初にコインの並べ方を $N!$ 通りの中から一様ランダムに 1 つ選び、全て表にして一列に並べる。

その後、左から順にコインを見ていく。
今見ているコインに書かれた数字を $C$ とすると、そのコインより右側にあり、かつ $C$ の倍数が書かれているコインを全て裏返す。

全てのコインを見終わった時点で、表になっているコインの枚数の期待値を求めよ。

### 制約

- $1 \\leq N \\leq 100$
- $1 \\leq C\_i \\leq 10\^9$

## 解説

コイン $i$ が最終的に表になる確率を $p\_i$ とする。
すると期待値の線形性より、最終的に表になるコインの枚数の期待値は $\\sum\_\{i = 1\}\^N p\_i$ で求まる。

コイン $i$ が最終的に表になっているのは、 **$C\_i$ の約数が書かれたコインが、自分より左に偶数枚あるとき** である。
$C\_i$ の約数が書かれていないコインは、コイン $i$ の裏表に一切関与しない。よって存在を無視してしまってもよい。

$C\_i$ の約数が書かれたコインが、コイン $i$ を除いて $m\_i$ 枚あったとする。
このときの $p\_i$ の値を、図に描いて考えてみる。
色がついているのが今見ているコイン(赤なら表、青なら裏)、他の丸は全部その約数が書かれたコインである。

$m\_i = 5$ の場合は下図の通り。
一般化すると、 $m\_i$ が奇数のときは常に $p\_i = 0.5$ となる。

{{<image src="0.jpg">}}

$m\_i = 6$ の場合は下図の通り。
一般化すると、 $m\_i$ が偶数のときは $p\_i = \\dfrac\{m\_i + 2\}\{2(m\_i + 1)\}$ となる。

{{<image src="1.jpg">}}

まとめると以下の通り。

$$
p\_i =
\\begin\{cases\}
   \\frac\{1\}\{2\}                    & (m\_i \\equiv 0 \\pmod\{2\}) \\\\
   \\frac\{m\_i + 2\}\{2 (m\_i + 1)\}  & (m\_i \\equiv 1 \\pmod\{2\})
\\end\{cases\}
$$

後はこれらを足していけば答えとなる。

## 実装例

[提出 #2702996 - AtCoder Beginner Contest 008](https://atcoder.jp/contests/abc008/submissions/2702996)

```cpp
template <typename T>
using V = vector<T>;
using ll = long long;

#define DOUBLE(n) static_cast<double>(n)
#define REP(i, n) FOR(i, 0, n)

#define fcout cout << fixed << setprecision(10)

/* ---------- ここまでマクロ ---------- */

const ll INF = 1LL << 50;

int main() {
    ll N;
    cin >> N;

    V<ll> C(N);
    REP(i, N) {
        cin >> C[i];
    }
    C.pb(INF);    // 番兵

    SORT(C);

    double ans = 0;
    ll mul = 1;
    // 同じ値がダブっていたとき用

    REP(i, N) {
        if (C[i] == C[i + 1]) {
            mul++;
            continue;
            // 値被りなのでスルー
            // 何もしないとi=N-1でC[N]にアクセスしようとしてセグフォる
            // だが先に追加した番兵によってそれが防がれている
        }

        ll cnt = 0;
        // 自分の約数が書かれたコインを数える
        REP(j, i) {
            if (C[i] % C[j] == 0) cnt++;
        }

        double p;
        // 先程出した確率を実際に計算する
        if (cnt % 2 == 0) {
            p = DOUBLE(cnt / 2 + 1) / (cnt + 1);
        } else {
            p = 0.5;
        }
        ans += p * mul;

        mul = 1;
        // mulの初期化を忘れないように
    }

    fcout << ans << endl;
    return 0;
}
```

