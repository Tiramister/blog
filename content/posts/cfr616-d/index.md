---
title: "Codeforces Round 616 D - Coffee Varieties"
date: 2020-02-18
tags: [codeforces]
---

[Problem - D - Codeforces](https://codeforces.com/contest/1290/problem/D)

## 問題

長さ $n$ の隠された数列 $(a\_i)$ がある．今からサイズ $k$ のキュー $S$ を持つ機械に対し以下の質問を行える．

- $1 \\leq i \\leq n$ を与える．
- $a\_i \\in S$ なら Y，そうでなければ N が返ってくる．
- $S$ の末尾に $a\_i$ を挿入し， $|S| \\gt k$ なら $S$ の先頭を削除する．

最初 $S = \\emptyset$ で，好きなタイミングで $S = \\emptyset$ にできる．**この操作は質問回数に含めない**．

$(a\_i)$ の中に何種類の整数があるかを，以下の質問回数以内で求めよ．

- Easy: $\\frac\{2 n\^2\}\{k\}$
- Hard: $\\frac\{3 n\^2\}\{2 k\}$

### 制約

- $1 \\leq k \\leq n \\leq 2\^\{10\}$
- $\\frac\{3 n\^2\}\{2 k\} \\leq 1.5 \\cdot 10\^4$
- $n, k$ は 2 べき

## 考察

まず長さ $k$ の連続区間に対して質問することで，その区間からダブった整数を弾くことができる．しかし複数区間にあるダブりは検知できない．

そこで，数列を代わりに長さ $\\frac\{k\}\{2\}$ の連続区間(以下ブロック)に分割する．すると，2 つのブロックに対して連続で質問をすることで，これらのブロック内のダブりを全て検知できる．これを全ブロック対に対して行うと，対の数はざっくり $\\frac\{2n\^2\}\{k\^2\}$ 個で抑えられるので質問数は $\\frac\{2n\^2\}\{k\}$ となる．これで Easy が解けた．

ここで，各ブロックを頂点とする完全グラフを考える．2 つのブロックに対して連続で質問したときにこれらのブロック間の辺を消すことにすると，全ての辺を消した時点で解が求まっていることになる．逆にそうでなければ情報が不十分．

上の方法では辺を 1 つ消す毎に律儀にリセットをしていた．しかし完全グラフ上にパスを 1 つ作ってこれに対して連続で質問することにすると，リセットの回数を減らすことができる．よって「以下に少ないパスで完全グラフを被覆できるか？」という問題を考えることになる．

そして驚くべきことに， $n$ が偶数のとき完全グラフ $K\_n$ は常に $n / 2$ 個の辺素なハミルトンパスに分解できる．これは前半分の各 $v$ を始点として $v \\to v + 1 \\to v - 1 \\to v + 2 \\to v - 2 \\to \\cdots$ のようなパスを考えてやればよい．

1 つのハミルトンパスに対する質問回数は $n$ 回，パスの数は $\\frac\{n\}\{k\}$ 個なので全体で $\\frac\{n\^2\}\{k\}$ 回の質問で解が求まる．これで Hard が解けた．制約が緩いのは乱択 DFS で通せるようにするためらしい．

## 実装例

[Submission #70728998 - Codeforces](https://codeforces.com/contest/1290/submission/70728998)

```cpp
#include <iostream>
#include <vector>
#include <numeric>

bool query(int i) {
    ++i;
    if (i <= 0) {
        std::cout << 'R' << std::endl;
        return false;
    }

    std::cout << "? " << i << std::endl;
    char c;
    std::cin >> c;
    return c == 'Y';
}

void solve() {
    int n, k;
    std::cin >> n >> k;
    int bsize = (k == 1 ? 1 : k / 2);
    int m = n / bsize;

    std::vector<bool> ans(n, true);
    for (int s = 0; s < m / 2; ++s) {
        int v = s;

        std::vector<bool> visited(m, false);
        int d = 1, sign = 1;

        while (true) {
            visited[v] = true;

            // ブロックvの始点
            int base = v * bsize;
            for (int i = 0; i < bsize; ++i) {
                int u = base + i;
                if (!ans[u] || query(u)) ans[u] = false;
            }

            // 次の頂点へ
            v = (v + d * sign + m) % m;
            ++d, sign = -sign;
            if (visited[v]) break;
        }
        query(-1);
    }

    std::cout << "! " << std::accumulate(ans.begin(), ans.end(), 0)
              << std::endl;
}
```

