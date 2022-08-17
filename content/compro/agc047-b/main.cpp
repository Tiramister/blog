#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>

struct Trie {
    struct Node {
        int c;
        std::array<int, 26> nxt;  // 子のindex
        std::array<int, 26> cnt;  // 文字cを含むような子孫の数
        int sz;                   // 部分木のサイズ

        Node(int c) : c(c), sz(0) {
            nxt.fill(-1);
            cnt.fill(0);
        }
    };

    std::vector<Node> nodes;

    Trie() { nodes.emplace_back(-1); }

    void add(const std::string& s) {
        int pos = 0;
        for (char c : s) {
            int ci = c - 'a';

            int npos = nodes[pos].nxt[ci];
            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[ci] = npos;
                nodes.emplace_back(ci);
            }
            pos = npos;
        }

        ++nodes[pos].sz;
    }

    int find(const std::string& s) const {
        int pos = 0;
        for (char c : s) {
            int ci = c - 'a';
            pos = nodes[pos].nxt[ci];
        }
        return pos;
    }

    // cntを埋める
    void fillcnt() {
        for (int pos = (int)nodes.size() - 1; pos >= 0; --pos) {
            auto& node = nodes[pos];

            for (int c = 0; c < 26; ++c) {
                int npos = node.nxt[c];
                if (npos == -1) continue;

                const auto& cnode = nodes[npos];
                node.sz += cnode.sz;
                for (int d = 0; d < 26; ++d) {
                    node.cnt[d] += cnode.cnt[d];
                }
            }

            // 全ての子孫はcを含む
            if (node.c != -1) node.cnt[node.c] = node.sz;
        }
    }
};

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> ss(n);
    for (auto& s : ss) {
        std::cin >> s;
        std::reverse(s.begin(), s.end());
    }

    Trie trie;
    for (const auto& s : ss) trie.add(s);

    trie.fillcnt();

    lint ans = 0;

    for (auto s : ss) {
        // 末尾とそれ以外に分離
        int last = s.back() - 'a';
        s.pop_back();

        int pos = trie.find(s);

        // posの子でlastを含むものを数え上げ
        for (int ci = 0; ci < 26; ++ci) {
            int npos = trie.nodes[pos].nxt[ci];

            if (npos == -1) continue;
            ans += trie.nodes[npos].cnt[last];

            // 自分自身は除く
            if (ci == last) --ans;
        }
    }

    std::cout << ans << "\n";
}
