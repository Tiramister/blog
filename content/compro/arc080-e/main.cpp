#include <atcoder/segtree>
#include <iostream>
#include <vector>
#include <queue>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using namespace std;

struct Data {
    int val, idx;
    explicit Data(int val, int idx) : val(val), idx(idx) {}

    static Data op(Data a, Data b) { return a.val <= b.val ? a : b; }
    static Data e() { return Data(1 << 30, -1); }
};

void solve() {
    int n;
    cin >> n;

    atcoder::segtree<Data, Data::op, Data::e> eseg(n), oseg(n);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        (i % 2 == 0 ? eseg : oseg).set(i, Data(p, i));
    }

    vector<int> ans;

    MinHeap<tuple<int, int, int>> heap;
    // val, [l, r)

    // 区間[l, r)を(空でなければ)最小値と共に追加
    auto push = [&](int l, int r) {
        if (r <= l) return;
        auto d = (l % 2 == 0 ? eseg : oseg).prod(l, r);
        heap.emplace(d.val, l, r);
    };

    push(0, n);
    while (!heap.empty()) {
        auto [v, l, r] = heap.top();
        heap.pop();

        auto x = (l % 2 == 0 ? eseg : oseg).prod(l, r);
        auto lr = x.idx;
        ans.push_back(x.val);

        auto y = (l % 2 == 0 ? oseg : eseg).prod(lr, r);
        auto rl = y.idx;
        ans.push_back(y.val);

        push(l, lr);
        push(lr + 1, rl);
        push(rl + 1, r);
    }

    for (auto p : ans) cout << p << " ";
    cout << "\n";
}
