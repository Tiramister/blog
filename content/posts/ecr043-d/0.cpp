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
