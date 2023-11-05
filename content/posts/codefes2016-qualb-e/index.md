---
title: "CODE FESTIVAL 2016 qual B E - Lexicographical disorder"
date: 2020-09-06
tags: [atcoder]
---

[E - Lexicographical disorder](https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_e)

## 問題

英小文字からなる $n$ 個の文字列 $(s\_i)$ が与えられる。以下の形式で与えられる $q$ 個のクエリに答えよ。

- a から z からなる、文字の比較順序を表す順列 $(p\_i)$ が与えられる。つまり $i \\lt j$ ならば、 $p\_i$ は $p\_j$ より小さい扱いとなる。
- この順序において、 $s\_k$ が $(s\_i)$ 中で辞書順で何番目かを求めよ。

### 制約

- $1 \\leq n, q \\leq 10\^5$
- $\\sum |s\_i| \\leq 4 \\cdot 10\^5 (= m)$
- $i \\neq j \\implies s\_i \\neq s\_j$

## 考察

以降、文字種数を $\\sigma(=26)$ とおく。

Trie のノードに「部分木中の $(s\_i)$ の個数」を持たせれば、根から Trie を辿ることで $O(\\sigma |s\_k|)$ でクエリを処理できる。しかしこれでは最悪 $\\Theta(\\sigma nq)$ 掛かってしまうので間に合わない。

そこで、Trie を辿るときの無駄を省くことにする。具体的には、

- 根でない
- 子を 1 つしか持たない
- どの $(s\_i)$ にも対応しない

ようなノードは、解に影響を及ぼすことはない。よってスキップすることができる。

このようなノードを省くと、Trie の深さの最大値は $\\Theta(\\sqrt\{m\})$ となる。これは $s$ に対応するパスが圧縮されないためには、 $s$ の接頭辞全てが Trie に追加されなくてはならないことによる。

よって圧縮後の Trie を使うことで、全体の計算量は $O(\\sigma \\sqrt\{m\} q)$ に落ちて間に合う。

## 実装例

[提出 #16537362 - CODE FESTIVAL 2016 qual B](https://atcoder.jp/contests/code-festival-2016-qualb/submissions/16537362)

```cpp
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <functional>

template <int K, class T>
struct Trie {
    struct Node {
        std::array<int, K> nxt;
        int id, sz, ch;
        explicit Node() : id(-1), sz(0), ch(0) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;
    std::vector<std::vector<int>> travs;  // 圧縮後の文字列

    explicit Trie(T base) { ... }

    template <class Container>
    void add(const Container& s, int id) {
        int pos = 0;

        for (T c : s) {
            ++nodes[pos].sz;

            int ci = enc(c);

            int npos = nodes[pos].nxt[ci];
            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[ci] = npos;
                nodes.emplace_back();

                ++nodes[pos].ch;
            }
            pos = npos;
        }

        ++nodes[pos].sz;
        nodes[pos].id = id;
    }

    int dfs(int pos, std::vector<int>& cs) {
        if (nodes[pos].id != -1) travs[nodes[pos].id] = cs;

        int ret = pos;
        for (int c = 0; c < K; ++c) {
            int npos = nodes[pos].nxt[c];
            if (npos == -1) continue;

            // reducible?
            bool red = (nodes[pos].ch == 1) &&
                       (nodes[pos].id == -1);

            if (!red) cs.push_back(c);
            nodes[pos].nxt[c] = dfs(npos, cs);
            if (!red) {
                cs.pop_back();
            } else {
                ret = nodes[pos].nxt[c];  // 圧縮
            }
        }
        return ret;
    }

    void compress(int n) {
        travs.resize(n);
        std::vector<int> cs;

        for (int c = 0; c < K; ++c) {
            int pos = nodes[0].nxt[c];
            if (pos == -1) continue;

            // 根は圧縮しない
            cs.push_back(c);
            nodes[0].nxt[c] = dfs(pos, cs);
            cs.pop_back();
        }
    }

    Node& operator[](int pos) { return nodes[pos]; }
    Node operator[](int pos) const { return nodes[pos]; }
};

void solve() {
    int n;
    std::cin >> n;

    Trie<26, char> trie('a');
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        trie.add(s, i);
    }

    trie.compress(n);

    int q;
    std::cin >> q;
    while (q--) {
        int k;
        std::cin >> k;
        --k;

        std::vector<int> cs(26);
        for (auto& c : cs) {
            char d;
            std::cin >> d;
            c = d - 'a';
        }

        // Trieを辿る
        int pos = 0, ans = 1;
        for (auto c : trie.travs[k]) {
            if (trie[pos].id != -1) ++ans;

            for (auto d : cs) {
                int npos = trie[pos].nxt[d];
                if (d != c) {
                    if (npos != -1) ans += trie[npos].sz;
                } else {
                    pos = npos;
                    break;
                }
            }
        }

        std::cout << ans << "\n";
    }
}
```

