#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    int k;
    for (k = 20; n < (1 << k); --k) {}

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;
    std::reverse(xs.begin(), xs.end());
    // 強い方からに並び替え

    lint ans = 0;

    MinHeap<lint> heap;
    int itr = 0;  // 次に追加する人
    heap.push(xs[itr++]);

    for (int q = 0; q < k; ++q) {
        lint a = heap.top();
        heap.pop();
        if (a < 0) break;  // 自分が最強なので買収なしでOK

        ans += a;
        int added = (1 << (k - q - 1));  // 候補に追加
        while (added--) {
            heap.push(xs[itr++]);
        }
    }

    std::cout << ans << std::endl;
}
