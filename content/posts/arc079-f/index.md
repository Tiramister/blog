---
title: "AtCoder Regular Contest 079 F - Namori Grundy"
date: 2019-11-15
tags: [atcoder]
---

[F - Namori Grundy](https://atcoder.jp/contests/arc079/tasks/arc079_d)

## 問題

$n$ 頂点 $n$ 辺の弱連結な有向グラフが与えられる． $i$ 番目の辺は頂点 $p\_i$ から $i$ に伸びている．

このとき，以下を満たす長さ $n$ の整数列 $(a\_i)$ が存在するか判定せよ．

- 任意の辺 $uv$ について $a\_u \\neq a\_v$ ．
- 任意の $u$ と $0 \\leq x \\lt a\_u$ なる $x$ について，ある $v$ が存在して辺 $uv$ が存在しかつ $a\_v = x$ ．

### 制約

- $2 \\leq n \\leq 2 \\times 10\^5$

## 考察

全ての子に既に割り当てが決定している場合，その MEX(Minimum EXcluded)がその頂点に割り当てられる．
よって出自数が 0 の頂点から割り当てを決めて，その頂点を消すことで連鎖的に割り当てを進めることができる．

ただしこの割り当ては最後まで行かない．最終的に 1 つのサイクルが残るためである．弱連結という前提から，2 つ以上のサイクルが残ることはない．

ここでサイクルの 1 つの頂点を選び，その子に割り当てられた整数の集合を $S$ とする． $S$ の MEX を $m$ とすると，この頂点に割り当てられるのは $m$ か $S \\cup \\\{ m \\\}$ の MEX かの 2 択となる．そしてこれのどっちを選ぶかを決めてしまえば，残りは一意に割り当てられる．
よってこの選択を全探索することで全ての可能性を潰すことができる．

## 実装例

サイクルが残ってから先だけ分岐させればいいが，実装が闇そうだったので一番最初から分岐させることにした．

[提出 #8436228 - AtCoder Regular Contest 079](https://atcoder.jp/contests/arc079/submissions/8436228)

```cpp
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <queue>

// sに含まれないもので，小さい方から2つ
std::array<int, 2> mex(std::set<int> s) {
    std::array<int, 2> ret;
    int idx = 0;
    for (int x = 0;; ++x) {
        if (s.count(x)) continue;
        ret[idx] = x;
        if (++idx == 2) break;
    }
    return ret;
}

// choiceでSとS+mのどっちのMEXを取るか指定する
bool solve(const std::vector<int>& par, int choice) {
    int n = par.size();

    // 出次数
    std::vector<int> outdeg(n, 0);
    for (auto p : par) ++outdeg[p];

    std::queue<int> que;
    std::vector<int> assign(n, -1);
    for (int v = 0; v < n; ++v) {
        if (outdeg[v] == 0) {
            assign[v] = 0;
            que.push(v);
        }
    }

    // 子のassignの集合
    std::vector<std::set<int>> ch(n);
    while (true) {
        while (!que.empty()) {
            int v = que.front();
            que.pop();

            int u = par[v];
            ch[u].insert(assign[v]);

            // 親の出次数が0になったら割り当て
            if (--outdeg[u] == 0 && assign[u] < 0) {
                assign[u] = mex(ch[u])[0];
                que.push(u);
            }
        }

        bool finish = true;
        for (int v = 0; v < n; ++v) {
            if (assign[v] < 0) {
                // サイクルから1つ選んで，適当に割り当て
                // この割り当て(choice)を全探索
                finish = false;
                assign[v] = mex(ch[v])[choice];
                que.push(v);
                break;
            }
        }
        if (finish) break;
    }

    // Judge
    for (auto& c : ch) c.clear();
    for (int v = 0; v < n; ++v) {
        int u = par[v];
        ch[u].insert(assign[v]);
    }
    for (int v = 0; v < n; ++v) {
        if (assign[v] != mex(ch[v])[0]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> par(n);
    for (auto& p : par) {
        std::cin >> p;
        --p;
    }

    for (int choice = 0; choice < 2; ++choice) {
        if (solve(par, choice)) {
            std::cout << "POSSIBLE" << std::endl;
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE" << std::endl;
    return 0;
}
```

