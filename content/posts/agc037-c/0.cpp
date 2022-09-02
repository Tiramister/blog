#include <iostream>
#include <vector>
#include <queue>

template <class T>
using MaxHeap = std::priority_queue<T>;

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n), ys(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    MaxHeap<std::pair<lint, int>> heap;
    // 揃えたいものの(bi, i)
    for (int i = 0; i < n; ++i) {
        if (xs[i] < ys[i]) heap.emplace(ys[i], i);
    }

    lint cnt = 0;
    while (!heap.empty()) {
        int i = heap.top().second;
        heap.pop();

        int l = (i + n - 1) % n,
            r = (i + 1) % n;
        lint s = ys[l] + ys[r];
        lint d = ys[i] - xs[i];

        if (d % s == 0) {
            // 合わせられるので合わせる
            cnt += d / s;
            ys[i] = xs[i];
        } else {
            // 減らせるだけ減らす
            cnt += ys[i] / s;
            ys[i] %= s;

            // 操作ができない or 過剰に小さくなった
            if (s > d || ys[i] < xs[i]) {
                std::cout << -1 << std::endl;
                return;
            }

            // 再度チャレンジ
            heap.emplace(ys[i], i);
        }
    }

    std::cout << cnt << std::endl;
}
