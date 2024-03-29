---
title: AtCoder Grand Contest 047 B - First Second
date: 2020-08-10
tags: [atcoder]
links:
  - label: 問題
    url: 
  - label: 提出
    url: 
---

[B - First Second](https://atcoder.jp/contests/agc047/tasks/agc047_b)

## 問題

$n$ 個の文字列 $\\{ s\_i \\}$ が与えられる。
以下の操作を $s\_i$ に好きな回数だけ繰り返すことで $s\_j$ と一致させられるような $i \neq j$ の個数を求めよ。

- 先頭 2 文字のうち片方を取り除く。

### 制約

- $2 \leq n \leq 2 \times 10^5$
- $s\_i \neq s\_j$
- $\sum |s\_i| \leq 10^6$

## 考察

まず後で考えやすいように、 $s\_i$ を全て反転させて考える。すると操作は「末尾 2 文字のうち片方を取り除く」となる。

### 条件の言い換え

観察してみると、「上述の操作を $k$ 回行う」という操作は「末尾 $k + 1$ 文字のうち 1 つ以外を全て消す」という操作と同値であることが分かる。

$s$ の末尾の文字を $c$ 、$s$ の末尾から $c$ を取り除いたものを $s\'$ とおく。
すると「文字列 $s$ を $t$ に一致させられる」という条件は、以下 2 つを両方満たすことと同値となる。

1. $s\'$ は $t$ の接頭辞である。つまりある文字列 $t\'$ によって $t = s\' t\'$ と表わせる。
2. 上で定めた文字列 $t\'$ に文字 $c$ が含まれる。

### 数え上げ

各 $i$ に対して、 $s\_i$ から $s\_j$ に変換できるような $j$ の個数を高速に数えたい。

条件 1 から「 $s\_i\'$ を接頭辞に持つ $s\_j$ 」を数えたいので、 Trie 木を使う。 Trie 木において「 $s\_i\'$ は $s\_j$ の接頭辞」という条件は、「 $s\_i\'$ に対応するノードは $s\_j$ に対応するノードの親である」と言い換えられる。よって $s\_i\'$ に対応するノードの子を数えればいい。

さらに条件 2 に対処するために、 Trie 木の各ノードに対して「文字 $c$ を含むような子孫の個数」というものを計算する。
これにより、 $c\_i\'$ を含む文字列に対応する子を定数時間で数えられる。

## 実装例

[提出 #15793676 - AtCoder Grand Contest 047](https://atcoder.jp/contests/agc047/submissions/15793676)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>

struct Trie {
    struct Node {
        int c;
        std::array<int, 26> nxt;  // 子のindex
        std::array<int, 26> cnt;  // 文字cを含むような子孫の数
        int sz;                   // 部分木のサイズ

        Node(int c) : c(c), sz(0) {
            nxt.fill(-1);
            cnt.fill(0);
        }
    };

    std::vector<Node> nodes;

    Trie() { nodes.emplace_back(-1); }

    void add(const std::string& s) {
        int pos = 0;
        for (char c : s) {
            int ci = c - 'a';

            int npos = nodes[pos].nxt[ci];
            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[ci] = npos;
                nodes.emplace_back(ci);
            }
            pos = npos;
        }

        ++nodes[pos].sz;
    }

    int find(const std::string& s) const {
        int pos = 0;
        for (char c : s) {
            int ci = c - 'a';
            pos = nodes[pos].nxt[ci];
        }
        return pos;
    }

    // cntを埋める
    void fillcnt() {
        for (int pos = (int)nodes.size() - 1; pos >= 0; --pos) {
            auto& node = nodes[pos];

            for (int c = 0; c < 26; ++c) {
                int npos = node.nxt[c];
                if (npos == -1) continue;

                const auto& cnode = nodes[npos];
                node.sz += cnode.sz;
                for (int d = 0; d < 26; ++d) {
                    node.cnt[d] += cnode.cnt[d];
                }
            }

            // 全ての子孫はcを含む
            if (node.c != -1) node.cnt[node.c] = node.sz;
        }
    }
};

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> ss(n);
    for (auto& s : ss) {
        std::cin >> s;
        std::reverse(s.begin(), s.end());
    }

    Trie trie;
    for (const auto& s : ss) trie.add(s);

    trie.fillcnt();

    lint ans = 0;

    for (auto s : ss) {
        // 末尾とそれ以外に分離
        int last = s.back() - 'a';
        s.pop_back();

        int pos = trie.find(s);

        // posの子でlastを含むものを数え上げ
        for (int ci = 0; ci < 26; ++ci) {
            int npos = trie.nodes[pos].nxt[ci];

            if (npos == -1) continue;
            ans += trie.nodes[npos].cnt[last];

            // 自分自身は除く
            if (ci == last) --ans;
        }
    }

    std::cout << ans << "\n";
}
```

