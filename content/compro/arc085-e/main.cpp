#include <atcoder/maxflow>
#include <iostream>

using lint = long long;

using namespace std;

constexpr lint M = 1LL << 30;
constexpr lint INF = 1LL << 50;

void solve() {
    int n;
    cin >> n;

    int s = n, g = n + 1;
    atcoder::mf_graph<lint> graph(n + 2);
    // s側が「壊す」集合

    // 倍数制約
    for (int i = 1; i <= n; ++i) {
        for (int j = i * 2; j <= n; j += i) {
            graph.add_edge(i - 1, j - 1, INF);
        }
    }

    // 選択報酬
    for (int i = 0; i < n; ++i) {
        lint a;
        cin >> a;
        graph.add_edge(s, i, M - a);  // 壊さなければaの報酬
        graph.add_edge(i, g, M);      // 壊せば報酬なし
    }

    cout << M * n - graph.flow(s, g) << "\n";
}
