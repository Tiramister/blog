---
title: "ICPC 2019 国内予選 E - 立方体表面パズル"
date: 2020-09-03
tags: [icpc]
---

[1636 < ICPC Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1636)

## 問題

立方体が $n \\times n$ の正方形状に並んだ板が $6$ つ与えられる。
これらは外周が一部欠けているもある。

これら $6$ つの板を組み合わせて、 $n \\times n \\times n$ の立方体の表面を作れるか判定せよ。なお各板はどちらの面を表面にしてもよい(つまり反転できる)ものとする。

### 制約

- $3 \\leq n \\leq 9$
- $n$ は奇数

## 考察

枝刈り DFS でシミュレーションするだけ(ちなみに DFS ではなく各板の配置・向きを全探索すると TLE する)。

ただ実装がかなり面倒くさい。以下では実際に $n \\times n \\times n$ の配列を塗っていくのだが、どの面に置くかによって 3 つの場合分け(といってもほとんどコピペだが)が生じている。

## 実装例

[Run #4814241 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/1636/review/4814241/misteer/C++14)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using Face = std::vector<std::string>;
using Cube = std::vector<Face>;

int n;
std::vector<Face> faces(6);
Cube cube;

void flip(Face& face) {
    for (auto& s : face) std::reverse(s.begin(), s.end());
}

void rotate(Face& face) {
    flip(face);

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < x; ++y) {
            std::swap(face[x][y], face[y][x]);
        }
    }
}

bool dfs(int b) {
    int d = __builtin_popcount(b);
    if (d == 6) return true;

    int z = (d % 2 == 0 ? 0 : n - 1);

    for (int i = 0; i < 6; ++i) {
        if ((b >> i) & 1) continue;

        auto& face = faces[i];

        for (int p = 0; p < 2; ++p) {
            // flip
            flip(face);

            for (int q = 0; q < 4; ++q) {
                // rotate
                rotate(face);

                if (d < 2) {
                    bool ok = true;
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X' &&
                                cube[x][y][z] == 'X') ok = false;
                        }
                    }
                    if (!ok) continue;

                    // paint
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[x][y][z] = 'X';
                        }
                    }

                    if (dfs(b | (1 << i))) return true;

                    // recover
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[x][y][z] = '.';
                        }
                    }

                } else if (d < 4) {
                    bool ok = true;
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X' &&
                                cube[x][z][y] == 'X') ok = false;
                        }
                    }

                    if (!ok) continue;

                    // paint
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[x][z][y] = 'X';
                        }
                    }

                    if (dfs(b | (1 << i))) return true;

                    // recover
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[x][z][y] = '.';
                        }
                    }

                } else {
                    bool ok = true;
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X' &&
                                cube[z][x][y] == 'X') ok = false;
                        }
                    }

                    if (!ok) continue;

                    // paint
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[z][x][y] = 'X';
                        }
                    }

                    if (dfs(b | (1 << i))) return true;

                    // recover
                    for (int x = 0; x < n; ++x) {
                        for (int y = 0; y < n; ++y) {
                            if (face[x][y] == 'X') cube[z][x][y] = '.';
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool solve() {
    std::cin >> n;
    if (n == 0) return false;

    int cnt = 0;
    for (auto& face : faces) {
        face.resize(n);
        for (auto& s : face) {
            std::cin >> s;
            cnt += std::count(s.begin(), s.end(), 'X');
        }
    }

    if (cnt != n * n * n - (n - 2) * (n - 2) * (n - 2)) {
        std::cout << "No\n";
        return true;
    }

    cube.resize(n);
    for (auto& face : cube) {
        face.resize(n);
        for (auto& s : face) s.assign(n, '.');
    }

    std::cout << (dfs(0) ? "Yes" : "No") << "\n";
    return true;
}
```

