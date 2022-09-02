#include <iostream>
#include <vector>
#include <functional>

template <int MOD>
struct ModInt { ... };

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    const mint twoinv = mint(2).inv();

    int n;
    std::cin >> n;

    Graph<> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        tree[u].emplace_back(u, v);
        tree[v].emplace_back(v, u);
    }

    mint ans = 0;

    // vを根とする部分木のサイズを返す
    std::function<int(int, int)> dfs =
        [&](int v, int r) {
            std::vector<int> ch;
            int sz = 0;

            for (auto e : tree[v]) {
                if (e.dst == r) continue;
                ch.push_back(dfs(e.dst, v));
                sz += ch.back();
            }

            // rを含む部分木のサイズ
            ch.push_back(n - 1 - sz);

            mint co = twoinv.pow(n);  // 全部白
            for (auto c : ch) {
                // 1つだけ黒を含む
                co += twoinv.pow(n - c) * (mint(1) - twoinv.pow(c));
            }

            ans += twoinv - co;  // 余事象を取る
            return sz + 1;
        };

    dfs(0, -1);
    std::cout << ans << std::endl;
    return 0;
}
