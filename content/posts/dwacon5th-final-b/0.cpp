#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <string>
#include <functional>

template <int K, class T>
struct Trie {
    struct Node {
        int c, sz;
        std::array<int, K> nxt;
        explicit Node(int c) : c(c), sz(0) { nxt.fill(-1); }
    };

    std::vector<Node> nodes;
    std::function<int(T)> enc;

    explicit Trie(T base) {
        nodes.emplace_back(-1);
        enc = [=](T c) { return c - base; };
    }

    explicit Trie(const std::function<int(T)>& enc)
        : enc(enc) { nodes.emplace_back(-1); }

    template <class Container>
    void add(const Container& s) { ... }

    template <class Container>
    void remove(const Container& s) { ... }

    std::string find(const std::string& s) {
        std::string ret;
        int pos = 0;

        for (auto ci : s) {
            int c = enc(ci);

            int npos = nodes[pos].nxt[c];
            if (npos == -1 || nodes[npos].sz == 0) {
                // 辿れないならもう一方へ
                c = 1 - c;
                npos = nodes[pos].nxt[c];
            }

            ret.push_back(c + '0');
            pos = npos;
        }

        remove(ret);
        return ret;
    }
};

// int -> string (front = MSB)
std::string tos(int x) {
    std::string ret;
    while (x > 0) {
        ret.push_back((x & 1) + '0');
        x >>= 1;
    }

    while ((int)ret.length() < 30) ret.push_back('0');
    std::reverse(ret.begin(), ret.end());
    return ret;
}

// string -> int (front = MSB)
int toi(const std::string& s) {
    int ret = 0;
    for (auto c : s) ret = (ret << 1) + (c - '0');
    return ret;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> ds(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        ds[i] = ds[i - 1] ^ x;
    }

    Trie<2, char> trie('0');
    for (int i = 1; i < n; ++i) trie.add(tos(ds[i]));

    for (int i = 1; i < n; ++i) {
        ds[i] = toi(trie.find(tos(ds[i - 1])));
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (ds[i + 1] ^ ds[i]) << " ";
    }
    std::cout << "\n";
}
