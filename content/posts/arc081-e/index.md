---
title: AtCoder Regular Contest 081 E - Don't Be a Subsequence
date: 2020-11-26
tags: [atcoder]
---

[E - Don't Be a Subsequence](https://atcoder.jp/contests/arc081/tasks/arc081_c)

## 問題

英小文字のみからなる文字列で、文字列 $S$ の部分列でないようなもののうち最短のものを求めよ。
複数ある場合は、その中で辞書順最小のものを求めよ。

### 制約

- $1 \\leq |S| \\leq 2 \\cdot 10\^5$

## 考察

以降、文字列 $S$ に対する解を $f(S)$ とする。
$S$ が空文字列でもよいことに注意(この場合、解は `a` となる)。

まずは $|f(S)|$ を求める。これは $f(S)$ の先頭の文字 $c$ で場合分けすると求められる。

- $S$ 中に $c$ が現れない場合。 $c$ 自体が条件を満たすので長さは $1$ となる。
- 現れる場合。 $S$ 中で現れる $c$ のうち一番前のものを $S\_i$ とすると、最適解は $c + f(S\_\{[i+1,|S|)\})$ となる。

ここで $S\_\{[i,|S|)\}$ は $S$ の $i$ 文字目以降からなる文字列を表す。

よって全ての $0 \\leq i \\leq |S|$ について以下を求めればよい。

- 各文字 $c$ について、 $S\_\{[i,|S|)\}$ 中で現れる $c$ のうち一番手前のものの index。
- $|f(S\_\{[i,|S|)\})|$

これは $i$ について降順に求めていくことで、全体で $\\Theta(\\sigma |S|)$ で求められる ($\\sigma$ は文字種数)。

上のアルゴリズムを使うと、「先頭が $c$ であり、条件を満たすような文字列の長さの最小値」が求められる。これが最小となるような $c$ のうち辞書順最小のものを先頭にすれば、 $f(S)$ の復元ができる。

## 実装例

$c$ が含まれない場合の処理を場合分けなしでやろうとしたら、却って実装がバグった。
自然に解釈できない番兵は使うべきではない。

[提出 #18405139 - AtCoder Regular Contest 081](https://atcoder.jp/contests/arc081/submissions/18405139)

```cpp
#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.length();

    vector<int> len(n + 1, n);  // S[i, n)に対する解の長さ
    len[n] = 1;
    auto nxt = vec(n + 1, vec(26, -1));
    // S[i, n)で一番手前にあるcの位置(なければ-1)

    for (int i = n - 1; i >= 0; --i) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;

        for (auto j : nxt[i]) {
            int nlen = (j == -1 ? 0 : len[j + 1]) + 1;
            len[i] = min(len[i], nlen);
        }
    }

    int i = 0, l = len[0];
    while (l > 0) {
        int nc = -1;  // 次の文字

        for (int c = 0; c < 26; ++c) {
            auto j = nxt[i][c];
            int nlen = (j == -1 ? 0 : len[j + 1]) + 1;

            if (nlen == l) {
                nc = c;
                break;
            }
        }

        cout << char(nc + 'a');
        i = nxt[i][nc] + 1;
        --l;
    }
    cout << "\n";
}
```

