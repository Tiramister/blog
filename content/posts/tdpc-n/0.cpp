#include <iostream>
#include <vector>
#include <queue>

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Edges = std::vector<Edge<Cost>>;

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T>
struct Combination { ... };

const Combination<mint> C(10000);

void solve() {
    int n;
    std::cin >> n;
    int m = n - 1;

    Edges<> edges;
    std::vector<std::vector<int>> es(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        es[u].push_back(i);
        es[v].push_back(i);
        edges.emplace_back(u, v);
    }

    mint ans = 0;
    for (int r = 0; r < m; ++r) {
        std::vector<std::vector<int>> chs(m);

        // BFSで木を構成
        // このときついでに逆トポロジカル順序も求める(stk)
        std::queue<int> que;
        que.push(r);

        std::vector<bool> used(m, false);
        used[r] = true;

        std::vector<int> stk;

        while (!que.empty()) {
            int e = que.front();
            que.pop();
            stk.push_back(e);

            int v;
            v = edges[e].src;
            for (auto f : es[v]) {
                if (used[f]) continue;
                chs[e].push_back(f);
                que.push(f);
                used[f] = true;
            }

            v = edges[e].dst;
            for (auto f : es[v]) {
                if (used[f]) continue;
                chs[e].push_back(f);
                que.push(f);
                used[f] = true;
            }
        }

        std::vector<int> sz(m);
        std::vector<mint> pat(m);

        // 逆トポロジカル順序を使って非再帰DFS
        while (!stk.empty()) {
            int e = stk.back();
            stk.pop_back();

            sz[e] = 0;
            pat[e] = 1;
            for (auto f : chs[e]) {
                sz[e] += sz[f];
                pat[e] *= pat[f];
            }

            int z = sz[e];
            for (auto f : chs[e]) {
                pat[e] *= C.comb(z, sz[f]);
                z -= sz[f];
            }
            ++sz[e];
        }

        ans += pat[r];
    }

    std::cout << ans << std::endl;
}
