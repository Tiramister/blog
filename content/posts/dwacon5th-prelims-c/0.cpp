#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using lint = long long;

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::vector<lint> dsum(n + 1, 0), msum(n + 1, 0), dmsum(n + 1, 0);
    std::vector<int> cpos;
    for (int i = 1; i <= n; ++i) {
        char c = s[i - 1];
        dsum[i] = dsum[i - 1];
        msum[i] = msum[i - 1];
        dmsum[i] = dmsum[i - 1];

        if (c == 'D') {
            ++dsum[i];
        } else if (c == 'M') {
            ++msum[i];
            dmsum[i] += dsum[i];
        } else if (c == 'C') {
            cpos.push_back(i);
        }
    }

    int q;
    std::cin >> q;
    for (int p = 0; p < q; ++p) {
        int k;
        std::cin >> k;
        lint ans = 0;
        for (auto i : cpos) {
            int l = std::max(0, i - k);
            ans += (dmsum[i] - dmsum[l]) -
                   (msum[i] - msum[l]) * dsum[l];
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
