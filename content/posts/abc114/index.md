---
title: "AtCoder Beginner Contest 114"
date: 2018-12-02
tags: [atcoder]
---

[AtCoder Beginner Contest 114 - AtCoder](https://atcoder.jp/contests/abc114)

## C - 755

### 概要

10 進法表記したときに $7, 5, 3$ が最低 1 回ずつ現れ、他の数字が現れないような数を **七五三数** と呼ぶことにする。

$1$ 以上 $N$ 以下の七五三数はいくつあるか求めよ。

#### 制約

- $1 \\leq N \\leq 10\^9$

### 解説

まず考えられるのは $1$ から $N$ まで全部判定する方法。しかし $N$ が大きすぎて現実的ではない。

桁 DP も考えられるが、C 問題にしては高度すぎるし何より実装したくない。

そこで逆に **七五三数を全列挙する** ことを考える。サンプル 3 を見れば分かるのだが、実は七五三数というのは結構少なくて十分全列挙できる。

ただし七五三数を全列挙するのはそこまで簡単ではない。私は以下のように実装した。

1. 桁数 $d$ を $3$ から $9$ まで回す。
2. $b$ を $0$ から $3\^d - 1$ まで回す。
3. $b$ を 3 進数表記したときの $i$ 桁目を $7, 5, 3$ に対応させて、長さ $d$ で $7, 5, 3$ のみからなる数を作る。
4. 「$7, 5, 3$ が出現したか」と「$N$ 以下か」をチェックし、両方満たすなら答えをインクリメントする。

手順 3 について補足しておく。例えば $b = 57$ のとき、 $b$ を３進数表記すると $2010\_\{(3)\}$ となるので $0 \\rightarrow 7, 1 \\rightarrow 5, 2 \\rightarrow 3$ と対応させることで $3757$ が作れる。

### 実装例

上の手順 3 なのだが、以下の実装例では $b$ を 3 進数表記して反転させたのちに変換したことになっている。どちらにせよ全列挙はできるので問題はない。

[提出 #3703479 - AtCoder Beginner Contest 114](https://atcoder.jp/contests/abc114/submissions/3703479)

```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;

// b^nを計算する関数
int mypow(int b, int n) {
    if (n == 0) return 1;
    if (n == 1) return b;
    if (n % 2 == 0) {
        return mypow(b * b, n / 2);
    } else {
        return mypow(b, n - 1) * b;
    }
}

// 012と753を変換する変数
const string i2c = "753";
const map<char, int> c2i = {{'7', 0}, {'5', 1}, {'3', 2}};

int main() {
    int N;
    cin >> N;

    int ans = 0;

    // dは桁数
    for (int d = 3; d < 10; ++d) {
        for (int b = 0; b < mypow(3, d); ++b) {
            string S;

            int cb = b;
            // 1の位から753に変換してpushしていく
            for (int i = 0; i < d; ++i) {
                S.push_back(i2c[cb % 3]);
                cb /= 3;
            }

            // 7, 5, 3の出現回数を数える
            bool cnt[3];
            fill(cnt, cnt + 3, false);

            for (char c : S) {
                cnt[c2i[c]] = true;
            }

            bool judge = true;
            for (int i = 0; i < 3; ++i) {
                if (!cnt[i]) judge = false;
            }
            if (!judge) continue;

            // N以下ならカウントする
            if (stoi(S) <= N) ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}

```

## D - 756

### 概要

正の約数をちょうど $75$ 個もつ正整数を **七五数** と呼ぶことにする。

$N!$ の約数で七五数であるものの個数を求めよ。

#### 制約

- $1 \\leq N \\leq 100$

### 解説

まずは正の約数の個数に関する知識が必要となる。

ある正整数 $N$ を素因数分解したものを $\{p\_1\}\^\{a\_1\} \{p\_2\}\^\{a\_2\} \\cdots \{p\_m\}\^\{a\_m\}$ とする。
このとき $N$ の正の約数の個数は $(a\_1 + 1) (a\_2 + 1) \\cdots (a\_m + 1)$ で求められる。この解説は偉大なる [高校数学の美しい物語](https://mathtrain.jp/numberofd) 様に投げさせていただく。

$75 = 3 \\cdot 5\^2$ を $(a\_1 + 1) (a\_2 + 1) \\cdots (a\_m + 1)$ の形で表すことを考えると、七五数は以下の 4 パターンしかない事が分かる。

- $p\^\{74\}$
- $p\^2 q\^\{24\}$
- $p\^4 q\^\{14\}$
- $p\^2 q\^4 r\^4$

したがって $N!$ を素因数分解して、 $p,q,r$ を全パターン調べると答えが分かる。
$100$ 以下の素数の数は 25 個なので、パターン数は $25\^3 = 15625$ 程度になって余裕で間に合う。

ただし $p\^2 q\^4 r\^4$ のパターンは注意が必要で、 $q$ と $r$ で重複して数えてしまうことがある。これは $q \\lt r$ とすることで防げる。

### 実装例

エラトステネスの篩を実装するのが面倒だったので、ネットから引っ張ってきた素数一覧をそのままコピペしている。

[提出 #3704475 - AtCoder Beginner Contest 114](https://atcoder.jp/contests/abc114/submissions/3704475)

```cpp
#include <iostream>

using namespace std;

// 100以下の素数一覧
const int prime[25] = {
    2, 3, 5, 7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    53, 59, 61, 67, 71,
    73, 79, 83, 89, 97};

int main() {
    int N;
    cin >> N;

    int cnt[25];
    fill(cnt, cnt + 25, 0);
    // cnt[i] = N!を素因数分解したときのp[i]の指数

    for (int n = 1; n <= N; ++n) {
        int m = n;

        // mを素因数分解する
        for (int i = 0; i < 25; ++i) {
            while (m % prime[i] == 0) {
                ++cnt[i];
                m /= prime[i];
            }
        }
    }

    int ans = 0;

    // p^74の形
    for (int p = 0; p < 25; ++p) {
        if (cnt[p] >= 74) ++ans;
    }

    // p^2 q^24とp^4 q^14の形
    for (int p = 0; p < 25; ++p) {
        for (int q = 0; q < 25; ++q) {
            if (p == q) continue;
            if (cnt[p] >= 4 && cnt[q] >= 14) ++ans;
            if (cnt[p] >= 2 && cnt[q] >= 24) ++ans;
        }
    }

    // p^2 q^4 r^4の形
    for (int p = 0; p < 25; ++p) {
        for (int q = 0; q < 25; ++q) {
            // 重複カウントを防ぐためにq < rにしている
            for (int r = q + 1; r < 25; ++r) {
                if (p == q || r == p) continue;
                if (cnt[p] >= 2 && cnt[q] >= 4 && cnt[r] >= 4) ++ans;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
```
