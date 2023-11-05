---
title: "第 5 回 ドワンゴからの挑戦状 本選 B - XOR Spread"
date: 2020-08-30
tags: [atcoder]
---

[B - XOR Spread](https://atcoder.jp/contests/dwacon5th-final/tasks/dwacon5th_final_b)

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる(0-indexed)。

以下の操作を好きなだけ行ったとき、最終的な数列で辞書順最小のものを求めよ。

- $0 \\lt i \\lt n - 1$ を自由に選ぶ。
- $a\_\{i - 1\} := a\_\{i - 1\} \\oplus a\_i, \\; a\_\{i + 1\} := a\_\{i + 1\} \\oplus a\_i$ で更新する。

ここで $\\oplus$ は bitwise xor を表す。

### 制約

- $1 \\leq n \\leq 10\^5$
- $0 \\leq a\_i \\leq 10\^9$

## 考察

更新式から差分を取ってみたくなるが、あまりキレイな形にならない。
実は取るべきなのは差分ではなく**和分**(つまり累積和)で、和分の上で操作は単なる隣接スワップになる。
具体的に $d\_i = \\bigoplus\_\{j=0\}\^\{i - 1\} a\_i$ として長さ $n + 1$ の数列 $\\\{ d\_i \\\}\_\{i=0\}\^\{n\}$ を考えると、 $i$ に対する操作は $d\_i, d\_\{i + 1\}$ のスワップとなる。

よって $\\\{ d\_i \\\}\_\{i=1\}\^\{n-1\}$ を自由に並び替えて、数列 $\\\{ d\_\{i+1\} \\oplus d\_i \\\}\_\{i=0\}\^\{n-1\}$ を辞書順最小にする問題と言い換えられる。
これは貪欲法で前から順に決めていくことができる。つまり $d\_\{i-1\}$ まで決まったとき、残っている要素のうち $x \\oplus d\_\{i-1\}$ が最小になる $x$ を $d\_i$ とすればいい。

この $x$ を求める方法として、上の桁から「 $x$ と一致させられるなら一致させる」という貪欲法が考えられる。
これを高速に行うためには「上位数桁が $x$ と一致するものが残っているか？」を高速に知る必要があるが、これは $\\\{ d\_i \\\}\_\{i=1\}\^\{n-1\}$ を**Trie**で管理することで実現できる。

## 実装例

Trie の中で一番重要なのは`Trie::find()`で、ここで $x$ を高速に求めている。

[提出 #16404340 - 第5回 ドワンゴからの挑戦状 本選](https://atcoder.jp/contests/dwacon5th-final/submissions/16404340)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <functional>

template <int K, class T>
struct Trie {
    struct Node {
        int c, sz;
        std::array<int, K> nxt;
        explicit Node(int c) : c(c), sz(0) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;

    explicit Trie(T base) {
        nodes.emplace_back(-1);
        enc = [=](T c) { return c - base; };
    }

    explicit Trie(const std::function<int(T)>& enc)
        : enc(enc) { nodes.emplace_back(-1); }

    template <class Container>
    void add(const Container& s) { ... }

    template <class Container>
    void remove(const Container& s) { ... }

    std::string find(const std::string& s) {
        std::string ret;
        int pos = 0;

        for (auto ci : s) {
            int c = enc(ci);

            int npos = nodes[pos].nxt[c];
            if (npos == -1 || nodes[npos].sz == 0) {
                // 辿れないならもう一方へ
                c = 1 - c;
                npos = nodes[pos].nxt[c];
            }

            ret.push_back(c + '0');
            pos = npos;
        }

        remove(ret);
        return ret;
    }
};

// int -> string (front = MSB)
std::string tos(int x) {
    std::string ret;
    while (x > 0) {
        ret.push_back((x & 1) + '0');
        x >>= 1;
    }

    while ((int)ret.length() < 30) ret.push_back('0');
    std::reverse(ret.begin(), ret.end());
    return ret;
}

// string -> int (front = MSB)
int toi(const std::string& s) {
    int ret = 0;
    for (auto c : s) ret = (ret << 1) + (c - '0');
    return ret;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> ds(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        ds[i] = ds[i - 1] ^ x;
    }

    Trie<2, char> trie('0');
    for (int i = 1; i < n; ++i) trie.add(tos(ds[i]));

    for (int i = 1; i < n; ++i) {
        ds[i] = toi(trie.find(tos(ds[i - 1])));
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (ds[i + 1] ^ ds[i]) << " ";
    }
    std::cout << "\n";
}
```

