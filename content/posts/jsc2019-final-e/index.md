---
title: "第一回日本最強プログラマー学生選手権決勝 E - Nearest String"
date: 2020-10-22
tags: [atcoder]
---

[E - Nearest String](https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_e)

## 問題

文字列に対する以下の 2 種類の操作を考える。

- 先頭または末尾から 1 文字削除する。このときコストが $X$ かかる。
- 末尾に任意の文字を 1 文字追加する。このときコストが $Y$ かかる。

$N$ 個の文字列 $\\\{ S\_i \\\}$ が与えられる。以下の形式のクエリを $Q$ 個処理せよ。

$j$ 番目のクエリでは文字列 $T\_j$ が与えられる。
$T\_j$ に上の 2 種類の操作を施すことでいずれかの $S\_i$ と一致させるとき、かかるコストの最小値を求めよ。

### 制約

- $1 \\leq N, Q \\leq 10\^5$
- $1 \\leq X, Y \\leq 10\^9$
- $\\sum |S\_i|, \\sum |T\_j| \\leq 5 \\cdot 10\^5$

## 考察

### $N=1$ の場合

まずは文字列 $T$ を $S$ に一致させるのにかかるコストの求め方を考える。
編集距離の DP と似たような考え方により、操作は実質的に以下の 2 種類と同等となる。

- $S$ の末尾から 1 文字削除する。このときコストが $Y$ かかる。
- $T$ の先頭または末尾から 1 文字削除する。このときコストが $X$ かかる。

よって $S\'$ を $S$ の接頭辞としたとき、 $S\'$ が $T$ に部分文字列として出現するなら一致させることができる。このときのコストは以下で求まる。

$$
\\begin\{align*\}
& Y(|S| - |S\'|) + X(|T| - |S\'|) \\\\
=& X|T| + Y|S| - (X + Y) |S\'|
\\end\{align*\}
$$

「 $S\'$ が $T$ に部分文字列として出現する」というのはパターンマッチングに他ならない。
よって $|S\'|$ の最大値は KMP 法により $\\Theta(|T|)$ で求められる。これで $N=1$ のケースは解くことができた。

### 一般の $N$ の場合

これを一般の $N$ へ拡張すると、パターンが複数に増える。
ということで複数パターンのマッチングが行える**Aho-Corasick 法**が使える。

$X|T| + Y|S| - (X + Y) |S\'|$ をよく見ると、 $T$ に依存する項と $S\'$ に依存する項が分離されている。よって Trie の各ノードに $Y|S| - (X + Y) |S\'|$ の最小値を持たせてやればよい。

## 実装例

Aho-Corasick 法をライブラリとして持っていれば、実装はちょっと中身を弄るだけで済む。

[提出 #17571411 - 第一回日本最強プログラマー学生選手権決勝](https://atcoder.jp/contests/jsc2019-final/submissions/17571411)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <queue>
#include <functional>

using lint = long long;
constexpr lint INF = 1LL << 60;
lint x, y;

template <int K, class T>
struct PatternsMatching {
    struct Node {
        std::array<int, K> nxt;
        int fail;
        lint cost;  // ノードに対応するprefixのうち、コストの最小値

        explicit Node() : fail(0), cost(INF) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;

    explicit PatternsMatching(T base) {
        nodes.emplace_back();
        enc = [=](T c) { return c - base; };
    }

    template <class Container>
    void add(const Container& s) {
        int pos = 0;
        lint cost = s.size() * y;

        for (T ci : s) {
            nodes[pos].cost = std::min(nodes[pos].cost, cost);
            cost -= x + y;  // prefixが1長くなるとコストはx+y減る

            int c = enc(ci);
            int npos = nodes[pos].nxt[c];

            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[c] = npos;
                nodes.emplace_back();
            }
            pos = npos;
        }

        nodes[pos].cost = std::min(nodes[pos].cost, cost);
    }

    void build() {
        std::queue<int> que;
        for (int& pos : nodes[0].nxt) {
            if (pos == -1) {
                pos = 0;
            } else {
                que.push(pos);
            }
        }

        while (!que.empty()) {
            int pos = que.front();
            que.pop();

            for (int c = 0; c < K; ++c) {
                int npos = nodes[pos].nxt[c];
                if (npos == -1) continue;

                int p = nodes[pos].fail;
                while (nodes[p].nxt[c] == -1) p = nodes[p].fail;
                int fpos = next(nodes[pos].fail, c);

                nodes[npos].fail = fpos;
                nodes[npos].cost = std::min(nodes[npos].cost, nodes[fpos].cost);
                // suffix linkとのminを取ることに注意
                que.push(npos);
            }
        }
    }

    int next(int pos, int c) const {
        while (nodes[pos].nxt[c] == -1) pos = nodes[pos].fail;
        return nodes[pos].nxt[c];
    }

    template <class Container>
    lint matching(const Container& s) const {
        int pos = 0;
        lint ret = nodes[0].cost;  // コストの最小値

        for (int i = 0; i < (int)s.size(); ++i) {
            pos = next(pos, enc(s[i]));
            ret = std::min(ret, nodes[pos].cost);
        }
        return ret;
    }
};

void solve() {
    int n, q;
    std::cin >> n >> q >> x >> y;

    PatternsMatching<26, char> pm('a');
    while (n--) {
        std::string s;
        std::cin >> s;
        pm.add(s);
    }
    pm.build();

    while (q--) {
        std::string t;
        std::cin >> t;
        std::cout << x * t.size() + pm.matching(t) << "\n";
    }
}
```

