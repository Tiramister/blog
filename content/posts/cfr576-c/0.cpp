#include <iostream>
#include <vector>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<bool> used(n * 3, false);
    std::vector<int> matching;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        if (!used[u] && !used[v]) {
            matching.push_back(i);
            used[u] = used[v] = true;
        }
    }

    if ((int)matching.size() >= n) {
        std::cout << "Matching" << std::endl;
        for (int i = 0; i < n; ++i) std::cout << matching[i] << " ";
        std::cout << std::endl;

    } else {
        std::cout << "IndSet" << std::endl;
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            while (used[idx]) ++idx;
            std::cout << idx + 1 << " ";
            ++idx;
        }
        std::cout << std::endl;
    }
}
