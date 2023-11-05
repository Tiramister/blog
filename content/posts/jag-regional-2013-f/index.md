---
title: JAG 模擬地区 2013 F - Shipura
date: 2020-11-14
tags: [icpc]
---

[2570 < JAG Regional < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2570?year=2013)

## 問題

以下の BNF で表される言語を考える。

```text
expr ::= term | expr sp ">>" sp term
term ::= number | "S" sp "<" sp expr sp ">"
```

ここで`sp`は 0 個以上のスペースからなる文字列、`number`は $0$ 以上 $10\^9$ 以下の整数を表す。

言語の評価規則は以下の通り。

- `x>>y`は $\\left\\lfloor \\frac\{x\}\{2\^y\} \\right\\rfloor$ と評価される。
- `S<x>`は $x\^2 \\bmod\{10\^9 + 7\}$ と評価される。

`expr`で表現可能な文字列が与えられるので、それを評価した結果を求めよ。

### 制約

- 文字列の長さは $2 \\cdot 10\^6$ 以下

## 考察

何も考えずに実装すると、入力例にある`S<S<S<S<S<2>>>>>`でパースエラーになる。
これは「`S<x>`中の`>`が 2 つ連なったもの」と、「`x>>y`中の`>>`」が区別できないためである。

これを区別するために、何らかのアドホックな処理が必要になる。
以下の実装では、「`S<S<x>>`のような項の直後に`term`は来ない」ことを利用して、「`>>`の後に`S`か数字が来るかどうか」で判定をしている。

## 実装例

C++11 以降のコンパイラって偉いな〜というお気持ちになる。

[Run #4990718 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/2570/review/4990718/misteer/C++17)

```cpp
#include <iostream>
#include <string>
#include <cassert>

using lint = long long;
constexpr lint MOD = 1000000007;

struct Parser {
    std::string s;
    int i;
    Parser(const std::string& s) : s(s), i(0) {}

    void sp() {
        while (s[i] == ' ') ++i;
    }

    lint term() {
        if (s[i] == 'S') {
            // S<x>
            ++i;
            sp();
            assert(s[i] == '<');
            ++i;
            sp();
            auto e = expr();
            sp();
            assert(s[i] == '>');
            ++i;

            return e * e % MOD;

        } else {
            // number
            assert(std::isdigit(s[i]));

            lint ret = 0;
            while (std::isdigit(s[i])) {
                ret = ret * 10 + s[i] - '0';
                ++i;
            }
            return ret;
        }
    }

    lint expr() {
        auto ret = term();
        sp();

        while (s.substr(i, 2) == ">>") {
            // iのバックアップ(j)を用意
            int j = i;
            i += 2;
            sp();

            // >>の先がtermでないなら、shiftではないので復元する
            if (s[i] != 'S' && !std::isdigit(s[i])) {
                i = j;
                break;
            }

            // shift
            auto t = term();
            if (t > 30) {
                ret = 0;
            } else {
                ret >>= t;
            }
            sp();
        }

        return ret;
    }
};

bool solve() {
    std::string s;
    std::getline(std::cin, s);
    if (s == "#") return false;

    Parser parser(s);
    std::cout << parser.expr() << "\n";
    return true;
}
```

