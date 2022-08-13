#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// 頂点数が(nl, nr)、辺集合がesの二部グラフ
// 使われる辺の番号を返す
vector<int> matching(
    int nl, int nr, const vector<pair<int, int>>& es) {
    int m = es.size();

    vector<bool> used(m, false);

    // 左側の頂点を0,1,...,nl-1
    // 右側の頂点をnl,nl+1,...,nl+nr-1と番号付ける
    vector<vector<int>> graph(nl + nr);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = es[i];
        graph[u].push_back(i);
        graph[v + nl].push_back(i);
    }

    // 頂点vから辺iを使ったときの行き先
    // ただし交互でない場合は-1
    auto get = [&](int v, int i) {
        // 左から右へはマッチングにない辺を使う
        // 右から左へはマッチングにある辺を使う
        if ((v < nl) == used[i]) return -1;

        return v ^ es[i].first ^ (es[i].second + nl);
    };

    while (true) {
        // 頂点vが自由か否か
        vector<bool> isfree(nl + nr, false);
        for (int v = 0; v < nl + nr; ++v) {
            isfree[v] = all_of(graph[v].begin(), graph[v].end(),
                               [&](auto i) { return !used[i]; });
        }

        queue<int> que;
        vector<int> ds(nl + nr, -1);

        // 左側の自由な頂点からスタート
        for (int v = 0; v < nl; ++v) {
            if (isfree[v]) {
                que.push(v);
                ds[v] = 0;
            }
        }

        // BFS
        while (!que.empty()) {
            auto v = que.front();
            que.pop();

            for (auto i : graph[v]) {
                // 接続するもう一方の頂点
                auto u = get(v, i);
                if (u != -1 && ds[u] == -1) {
                    ds[u] = ds[v] + 1;
                    que.push(u);
                }
            }
        }

        // 右側の自由な頂点のうち、最短距離の最小値
        int k = -1;
        for (int v = nl; v < nl + nr; ++v) {
            if (!isfree[v] || ds[v] == -1) continue;

            if (k == -1) {
                k = ds[v];
            } else {
                k = min(k, ds[v]);
            }
        }

        // 増加路がなければ終了
        if (k == -1) break;

        vector<bool> visited(nl + nr, false);  // 頂点がマッチングに使われたか
        vector<int> eis(nl + nr, 0);           // 次に見る辺の番号

        // vから増加路が作れればtrue
        auto dfs = [&](auto&& f, int v) -> bool {
            // 右側の自由な頂点でエンド
            if (ds[v] == k && isfree[v]) {
                visited[v] = true;
                return true;
            }

            auto& ei = eis[v];
            while (ei < (int)graph[v].size()) {
                auto i = graph[v][ei++];

                auto u = get(v, i);
                // マッチングに使われておらず、かつ次のレイヤーにあるなら移動
                if (u == -1 || visited[u] ||
                    ds[u] != ds[v] + 1) continue;

                if (f(f, u)) {
                    // 増加路が作れるので、辺iを反転
                    used[i] = !used[i];
                    visited[v] = true;
                    return true;
                }
            }

            // 増加路は作れないので、以降見なくていい
            visited[v] = true;
            return false;
        };

        // 左側の自由な頂点からスタート
        for (int v = 0; v < nl; ++v) {
            if (isfree[v] && !visited[v]) dfs(dfs, v);
        }
    }

    vector<int> ret;
    for (int i = 0; i < m; ++i) {
        if (used[i]) ret.push_back(i);
    }
    return ret;
}
