---
title: "ICPC 2017 国内予選 E - 論理式圧縮機"
date: 2019-06-16
tags: [icpc]
---

[1620 < ICPC Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1620?year=2017)

## 問題

以下の BNF によって定義される、 4 変数の論理式が与えられる。

```txt
<E> ::= 0 | 1 | a | b | c | d | -<E> | (<E>*<E>) | (<E>^<E>)
```

ここで`-`、`*`、`^`はそれぞれ not、and、xor に当たる。

与えられた式と同値な論理式の長さの最小値を求めよ。

### 制約

- 論理式の長さは $16$ 以下

## 考察

与えられた論理式を同値なものに圧縮する、みたいなことを考えるとどツボにハマる。

そもそも「論理式が同値」というのは「a~d にどんな真理値を割り振っても、全体の真理値が合致する」ということである。よって全ての割り振りに対して真理値を求めれば、その対応表によって論理式を表現することができる(これを真理値表と呼ぶことにする)。割り振りのパターンは $2\^4 = 16$ 通りしかないので、真理値表は $2^16 = 32,776$ 通りしか存在しない。

後は論理式の各長さに対して、実現できる真理値表を全て求めればいい。これは長さの小さい方から、

- 長さを 1 増やして not をつける
- 長さを 3 増やして、2 つの真理値表を and か xor でくっつける

という遷移によって埋めることができる。

疑問なのは計算量だが、 and と xor の追加コストが大きいため十分小さくなる。

## 実装例

以下のコードでは、実装しやすいように文法を以下のように変換している。

```txt
expr ::= term | -expr | (bin)
bin  ::= expr*expr | expr^expr
term ::= 0 | 1 | a | b | c | d
```

[Submissions < misteer < Users | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/status/users/misteer/submissions/1/1620/judge/3659639/C++14)

```cpp
constexpr int mask = (1 << 16) - 1;
constexpr int INF = 1 << 30;

/* ----- 真理値表埋め ----- */
vector<vector<int>> T(17);
// T[l] = 長さlの論理式で表せる真理値表の集合(lは最小)

vector<int> U(1 << 16, INF);
// T[t] = 真理値表tを表す最短の論理式の長さ

void init() {
    // 長さ1は0, 1, a, b, c, dのみ
    T[1] = {0b0000000000000000,
            0b1111111111111111,
            0b1010101010101010,
            0b1100110011001100,
            0b1111000011110000,
            0b1111111100000000};
    for (auto t : T[1]) U[t] = 1;

    for (int k = 2; k <= 16; ++k) {
        for (auto t : T[k - 1]) {
            int v = mask ^ t;  // notを合成
            if (U[v] == INF) {
                U[v] = k;
                T[k].push_back(v);
            }
        }

        for (int i = 1; i <= k - 3 - i; ++i) {
            // 長さの和がk-3になる組を全て試す
            for (auto t1 : T[i]) {
                for (auto t2 : T[k - 3 - i]) {
                    int v = t1 & t2;  // andを合成
                    if (U[v] == INF) {
                        U[v] = k;
                        T[k].push_back(v);
                    }

                    v = t1 ^ t2;  // xorを合成
                    if (U[v] == INF) {
                        U[v] = k;
                        T[k].push_back(v);
                    }
                }
            }
        }
    }
}

/* ----- 構文解析 ----- */
string S;
int pat;  // a, b, c, dの割り振り

bool expr(int&);

// expr^expr, expr*expr
bool bin(int& i) {
    bool ret = expr(i);
    if (S[i] == '*') {
        ++i;
        ret = expr(i) && ret;
    } else if (S[i] == '^') {
        ++i;
        ret = expr(i) != ret;
    }
    return ret;
}

// 0, 1, a, b, c, d
bool term(int& i) {
    bool ret;
    if ('0' <= S[i] && S[i] <= '1') {
        ret = S[i] - '0';
    } else if ('a' <= S[i] && S[i] <= 'd') {
        ret = (pat >> (S[i] - 'a')) & 1;
    }
    ++i;
    return ret;
}

// term, -expr, (bin)
bool expr(int& i) {
    bool ret;
    if (S[i] == '(') {
        ++i;
        ret = bin(i);
        ++i;
    } else if (S[i] == '-') {
        ++i;
        ret = !expr(i);
    } else {
        ret = term(i);
    }
    return ret;
}

/* ----- main ----- */
bool solve() {
    cin >> S;

    // 真理値表を計算
    int i, tab = 0;
    for (pat = 0; pat < (1 << 4); ++pat) {
        i = 0;
        tab += expr(i) << pat;
    }

    // 前計算で得たテーブルを参照
    cout << U[tab] << endl;
    return true;
}
```

構文解析にて 1 つ大きな注意点がある。
`bin`内の`ret = expr(i) && ret;`だが、これは順番を逆にすると短絡評価によって`expr(i)`が評価されないことがある。
一番確実なのは変数に格納することである。

