#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <queue>
#include <functional>

using lint = long long;
constexpr lint INF = 1LL << 60;
lint x, y;

template <int K, class T>
struct PatternsMatching {
    struct Node {
        std::array<int, K> nxt;
        int fail;
        lint cost;  // ノードに対応するprefixのうち、コストの最小値

        explicit Node() : fail(0), cost(INF) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;

    explicit PatternsMatching(T base) {
        nodes.emplace_back();
        enc = [=](T c) { return c - base; };
    }

    template <class Container>
    void add(const Container& s) {
        int pos = 0;
        lint cost = s.size() * y;

        for (T ci : s) {
            nodes[pos].cost = std::min(nodes[pos].cost, cost);
            cost -= x + y;  // prefixが1長くなるとコストはx+y減る

            int c = enc(ci);
            int npos = nodes[pos].nxt[c];

            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[c] = npos;
                nodes.emplace_back();
            }
            pos = npos;
        }

        nodes[pos].cost = std::min(nodes[pos].cost, cost);
    }

    void build() {
        std::queue<int> que;
        for (int& pos : nodes[0].nxt) {
            if (pos == -1) {
                pos = 0;
            } else {
                que.push(pos);
            }
        }

        while (!que.empty()) {
            int pos = que.front();
            que.pop();

            for (int c = 0; c < K; ++c) {
                int npos = nodes[pos].nxt[c];
                if (npos == -1) continue;

                int p = nodes[pos].fail;
                while (nodes[p].nxt[c] == -1) p = nodes[p].fail;
                int fpos = next(nodes[pos].fail, c);

                nodes[npos].fail = fpos;
                nodes[npos].cost = std::min(nodes[npos].cost, nodes[fpos].cost);
                // suffix linkとのminを取ることに注意
                que.push(npos);
            }
        }
    }

    int next(int pos, int c) const {
        while (nodes[pos].nxt[c] == -1) pos = nodes[pos].fail;
        return nodes[pos].nxt[c];
    }

    template <class Container>
    lint matching(const Container& s) const {
        int pos = 0;
        lint ret = nodes[0].cost;  // コストの最小値

        for (int i = 0; i < (int)s.size(); ++i) {
            pos = next(pos, enc(s[i]));
            ret = std::min(ret, nodes[pos].cost);
        }
        return ret;
    }
};

void solve() {
    int n, q;
    std::cin >> n >> q >> x >> y;

    PatternsMatching<26, char> pm('a');
    while (n--) {
        std::string s;
        std::cin >> s;
        pm.add(s);
    }
    pm.build();

    while (q--) {
        std::string t;
        std::cin >> t;
        std::cout << x * t.size() + pm.matching(t) << "\n";
    }
}
