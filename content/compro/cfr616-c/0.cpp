#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

struct UnionFind {
    std::vector<int> par, dist, sz, ty;
    std::vector<std::vector<int>> szs;
    int gnum, sum;

    explicit UnionFind(int n)
        : par(n), dist(n, 0), sz(n, 1), ty(n, 2), szs(n, {0, 1}), gnum(n), sum(0) {
        std::iota(par.begin(), par.end(), 0);
    }

    // vが属する連結成分の根を，色を反転させながら返す
    int find(int v, int& t) {
        if (par[v] == v) {
            return v;
        } else {
            t ^= dist[v];
            return find(par[v], t);
        }
    }

    void unite(int u, int v, int t) {
        int ut = 0, vt = t;
        u = find(u, ut), v = find(v, vt);
        if (u == v) return;

        if (sz[u] < sz[v]) {
            std::swap(u, v);
            std::swap(ut, vt);
        }

        sz[u] += sz[v];

        sum -= score(u) + score(v);
        // マージされる側がタイプを強制される場合，それに合わせる
        if (ty[u] == 2 && ty[v] != 2) {
            ty[u] = (ty[v] + (ut != vt)) % 2;
        }
        // サイズをマージ
        szs[u][ut] += szs[v][vt];
        szs[u][1 - ut] += szs[v][1 - vt];
        sum += score(u);

        par[v] = u;
        dist[v] = (ut != vt);
        --gnum;
    }

    // uが属する連結成分でいくつスイッチを選ぶべきか
    int score(int u) {
        int t = 0;
        u = find(u, t);
        return ty[u] == 2 ? std::min(szs[u][0], szs[u][1]) : szs[u][ty[u]];
    }

    // uが属する連結成分に，選ぶ集合を強制させる
    void settype(int u, int t) {
        u = find(u, t);
        sum -= score(u);
        ty[u] = t;
        sum += score(u);
    }
};

void solve() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;

    std::vector<std::vector<int>> graph(n);
    for (int v = 0; v < k; ++v) {
        int c;
        std::cin >> c;
        while (c--) {
            int u;
            std::cin >> u;
            graph[--u].push_back(v);
        }
    }

    UnionFind uf(k);
    for (int i = 0; i < n; ++i) {
        const auto& vs = graph[i];

        if (vs.size() == 1) {
            // 選ぶ集合を強制させる
            int v = vs.front();
            uf.settype(v, s[i] == '0');

        } else if (vs.size() == 2) {
            // マージする
            int u = vs[0], v = vs[1];
            uf.unite(u, v, s[i] == '0');
        }
        std::cout << uf.sum << "\n";
    }
}
