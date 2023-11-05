---
title: "Educational Codeforces Round 43 D - Degree Set"
date: 2020-02-18
tags: [codeforces]
---

[Problem - D - Codeforces](https://codeforces.com/contest/976/problem/D)

## 問題

サイズ $n$ の整数集合 $\\\{ d\_i \\\}$ が昇順に与えられる．以下を満たすグラフを構築せよ．

- 頂点数は $d\_n + 1$ ．
- 辺数は $10\^6$ 以下．
- 単純である(自己辺，多重辺を持たない)．
- 次数列を集合として見たとき， $\\\{ d\_i \\\}$ と一致する．

### 制約

- $1 \\leq n \\leq 300$
- $1 \\leq d\_i \\leq 1,000$

## 考察

シンプルに難しい構築． $n$ が小さい方から試すと見えてくる．

まず $n = 1$ ．これは完全グラフが条件を満たす．

次に $n = 2$ ．これは少し難しいが，「**他の全頂点と隣接する頂点**」を $d\_1$ 個用意すると，それら以外の頂点の次数が全部 $d\_1$ になるので条件を満たす．

この $n = 2$ のケースを繰り返し適用することで集合のサイズをどんどん小さくしていく，というのが解法．具体的には以下を繰り返す．

- 「他の全頂点と隣接する頂点」を $d\_1$ 個用意する．
- これらの頂点を消す．
- 残りの頂点の次数は全部等しく $d\_1$ なので，各 $d\_i$ から $d\_1$ を引く．
- 次数 $d\_1$ 用の頂点を 1 つ消す．
- $\\\{ d\_i \\\}$ から $d\_1, d\_n$ を消す．

気になるのは，各ステップで十分な数の頂点が残るかどうかだが，実はこれは常に残る．ステップの最初の時点で $d\_n + 1$ 頂点だったのが，最終的には $d\_n + 1 - d\_1 - 1 = d\_n - d\_1$ 頂点になる．ここで $d\_\{n - 1\} \\lt d\_n$ より $d\_n - d\_1 \\geq d\_\{n - 1\} - d\_1 + 1$ ．よって足りる．ちなみに余った分は孤立点にすればよい．

## 実装例

[Submission #71259832 - Codeforces](https://codeforces.com/contest/976/submission/71259832)

```cpp
#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> ds(n);
    for (auto& d : ds) std::cin >> d;

    std::vector<std::pair<int, int>> ans;
    while (!ds.empty()) {
        int vnum = ds.back() + 1;

        if (ds.size() == 1) {
            // 完全グラフ
            for (int v = 0; v < vnum; ++v) {
                for (int u = 0; u < v; ++u) {
                    ans.emplace_back(u, v);
                }
            }
            break;
        }

        int k = ds.front();

        // 後ろk頂点から全頂点に辺を張る
        for (int v = vnum - k; v < vnum; ++v) {
            for (int u = 0; u < v; ++u) {
                ans.emplace_back(u, v);
            }
        }

        // 次数を更新して先頭，末尾を削除
        for (auto& d : ds) d -= k;
        ds.erase(ds.begin());
        ds.pop_back();
    }

    std::cout << ans.size() << std::endl;
    for (auto p : ans) {
        std::cout << p.first + 1 << " " << p.second + 1 << "\n";
    }
}
```

