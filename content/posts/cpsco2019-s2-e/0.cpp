#include <iostream>
#include <vector>
#include <functional>

template <class Cost = int>
struct Edge {
    int src, dst;
    Cost cost;
    Edge(int src = -1, int dst = -1, Cost cost = 1)
        : src(src), dst(dst), cost(cost){};
};

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

using lint = long long;
constexpr lint INF = 1LL << 40;

int main() {
    int n;
    std::cin >> n;

    Graph<lint> graph(n);
    for (int v = 1; v < n; ++v) {
        int p;
        lint h;
        std::cin >> p >> h;
        graph[p].emplace_back(p, v, h);
    }

    std::function<std::vector<lint>(int)> dfs =
        [&](int v) {
            std::vector<lint> cost{0};
            // i個の連結成分を作るとき，上への辺が受ける最小ダメージ

            for (auto e : graph[v]) {
                auto chcost = dfs(e.dst);

                // eを切った場合を加味する
                chcost.push_back(INF);
                for (int num = chcost.size() - 1; num >= 0; --num) {
                    if (chcost[num] > e.cost) {
                        // 部分木を分解する前にeが切れてる
                        chcost[num] = INF;
                    } else {
                        // eを切って1つ増やす
                        chcost[num + 1] = std::min(chcost[num + 1], e.cost);
                    }
                }

                // マージ
                std::vector<lint> ncost(cost.size() + chcost.size() - 1, INF);
                for (int i = 0; i < cost.size(); ++i) {
                    for (int j = 0; j < chcost.size(); ++j) {
                        ncost[i + j] = std::min(ncost[i + j],
                                                cost[i] + chcost[j]);
                    }
                }
                std::swap(cost, ncost);
            }
            return cost;
        };

    auto ans = dfs(0);
    int num;
    for (num = n - 1; num >= 0; --num) {
        if (ans[num] < INF) break;
    }
    // 根の分を加算
    std::cout << num + 1 << std::endl;
    return 0;
}
