#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int k, n;
    cin >> k >> n;

    if (k % 2 == 0) {
        cout << k / 2 << " ";
        for (int i = 0; i < n - 1; ++i) cout << k << " ";
        cout << "\n";

    } else {
        vector<int> ans(n, (k + 1) / 2);  // 真ん中からスタート
        int front = n;                    // ansより前が後よりいくつ多いか

        while (front > 1) {
            // 1つ前に戻す
            if (--ans.back() == 0) {
                ans.pop_back();
            } else {
                // 後ろにkを補充
                ans.resize(n, k);
            }
            front -= 2;
        }

        for (auto x : ans) cout << x << " ";
        cout << "\n";
    }
}
