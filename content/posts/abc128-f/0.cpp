#include <iostream>
#include <vector>

using lint = long long;

int main() {
    int n;
    std::cin >> n;

    std::vector<lint> ss(n);
    for (auto& s : ss) std::cin >> s;

    lint ans = 0;
    for (int k = 1; k < n; ++k) {
        int l = 0, r = n - 1;
        lint sum = 0;

        while (r > k && (r > l || r % k != 0)) {
            sum += ss[l] + ss[r];
            ans = std::max(ans, sum);
            l += k;
            r -= k;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
