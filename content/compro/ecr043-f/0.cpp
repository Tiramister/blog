#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

template <class Cap, bool isDirect>
struct MaxFlow { ... };

void solve() {
    int na, nb, m;
    std::cin >> na >> nb >> m;

    std::vector<int> adeg(na, 0), bdeg(nb, 0);
    std::vector<std::pair<int, int>> edges(m);
    for (auto& e : edges) {
        std::cin >> e.first >> e.second;
        --e.first, --e.second;
        ++adeg[e.first], ++bdeg[e.second];
    }

    int mindeg = std::min(*std::min_element(adeg.begin(), adeg.end()),
                          *std::min_element(bdeg.begin(), bdeg.end()));

    for (int k = 0; k <= mindeg; ++k) {
        int s = na + nb, g = na + nb + 1;
        MaxFlow<int, true> mf(na + nb + 2);

        // グラフを構築
        for (int va = 0; va < na; ++va) {
            mf.span(s, va, -1, adeg[va] - k);
        }
        for (int vb = 0; vb < nb; ++vb) {
            mf.span(vb + na, g, -1, bdeg[vb] - k);
        }

        for (int i = 0; i < m; ++i) {
            mf.span(edges[i].first, edges[i].second + na, i, 1);
        }

        // 流して使われなかった辺を集める
        mf.exec(s, g);
        std::vector<int> ans;
        for (auto e : mf.edges) {
            if (e.id < 0) continue;
            if (e.cap > 0) ans.push_back(e.id);
        }

        std::cout << ans.size() << " ";
        for (auto i : ans) std::cout << i + 1 << " ";
        std::cout << std::endl;
    }
}
