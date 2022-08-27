#include <iostream>
#include <vector>
#include <queue>
#include <map>

template <class T>
using MaxHeap = std::priority_queue<T>;
template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

template <int MOD, int Root>
struct NumberTheoreticalTransform { ... };

using mints = std::vector<mint>;
using NTT = NumberTheoreticalTransform<MOD, 3>;

const NTT Ntt;

// priority queue用の比較関数
struct Compare {
    bool operator()(const mints& a, const mints& b) {
        return a.size() > b.size();
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (!cnt.count(x)) cnt[x] = 0;
        ++cnt[x];
    }

    // 多項式をpriority queueに突っ込む
    std::priority_queue<mints, std::vector<mints>, Compare> que;
    for (auto p : cnt) {
        int q = p.second;
        auto v = std::vector<mint>(q + 1, 1);
        que.emplace(v);
    }

    // サイズの小さい方からマージ
    while (que.size() > 1) {
        auto f = que.top();
        que.pop();
        auto g = que.top();
        que.pop();
        mints h = Ntt.ntt(f, g);
        que.push(h);
    }

    auto f = que.top();
    std::cout << f[n / 2] << std::endl;
}
