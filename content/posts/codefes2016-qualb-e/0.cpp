#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <functional>

template <int K, class T>
struct Trie {
    struct Node {
        std::array<int, K> nxt;
        int id, sz, ch;
        explicit Node() : id(-1), sz(0), ch(0) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;
    std::vector<std::vector<int>> travs;  // 圧縮後の文字列

    explicit Trie(T base) { ... }

    template <class Container>
    void add(const Container& s, int id) {
        int pos = 0;

        for (T c : s) {
            ++nodes[pos].sz;

            int ci = enc(c);

            int npos = nodes[pos].nxt[ci];
            if (npos == -1) {
                npos = nodes.size();
                nodes[pos].nxt[ci] = npos;
                nodes.emplace_back();

                ++nodes[pos].ch;
            }
            pos = npos;
        }

        ++nodes[pos].sz;
        nodes[pos].id = id;
    }

    int dfs(int pos, std::vector<int>& cs) {
        if (nodes[pos].id != -1) travs[nodes[pos].id] = cs;

        int ret = pos;
        for (int c = 0; c < K; ++c) {
            int npos = nodes[pos].nxt[c];
            if (npos == -1) continue;

            // reducible?
            bool red = (nodes[pos].ch == 1) &&
                       (nodes[pos].id == -1);

            if (!red) cs.push_back(c);
            nodes[pos].nxt[c] = dfs(npos, cs);
            if (!red) {
                cs.pop_back();
            } else {
                ret = nodes[pos].nxt[c];  // 圧縮
            }
        }
        return ret;
    }

    void compress(int n) {
        travs.resize(n);
        std::vector<int> cs;

        for (int c = 0; c < K; ++c) {
            int pos = nodes[0].nxt[c];
            if (pos == -1) continue;

            // 根は圧縮しない
            cs.push_back(c);
            nodes[0].nxt[c] = dfs(pos, cs);
            cs.pop_back();
        }
    }

    Node& operator[](int pos) { return nodes[pos]; }
    Node operator[](int pos) const { return nodes[pos]; }
};

void solve() {
    int n;
    std::cin >> n;

    Trie<26, char> trie('a');
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        trie.add(s, i);
    }

    trie.compress(n);

    int q;
    std::cin >> q;
    while (q--) {
        int k;
        std::cin >> k;
        --k;

        std::vector<int> cs(26);
        for (auto& c : cs) {
            char d;
            std::cin >> d;
            c = d - 'a';
        }

        // Trieを辿る
        int pos = 0, ans = 1;
        for (auto c : trie.travs[k]) {
            if (trie[pos].id != -1) ++ans;

            for (auto d : cs) {
                int npos = trie[pos].nxt[d];
                if (d != c) {
                    if (npos != -1) ans += trie[npos].sz;
                } else {
                    pos = npos;
                    break;
                }
            }
        }

        std::cout << ans << "\n";
    }
}
