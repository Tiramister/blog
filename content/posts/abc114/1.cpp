#include <iostream>

using namespace std;

// 100以下の素数一覧
const int prime[25] = {
    2, 3, 5, 7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    53, 59, 61, 67, 71,
    73, 79, 83, 89, 97};

int main() {
    int N;
    cin >> N;

    int cnt[25];
    fill(cnt, cnt + 25, 0);
    // cnt[i] = N!を素因数分解したときのp[i]の指数

    for (int n = 1; n <= N; ++n) {
        int m = n;

        // mを素因数分解する
        for (int i = 0; i < 25; ++i) {
            while (m % prime[i] == 0) {
                ++cnt[i];
                m /= prime[i];
            }
        }
    }

    int ans = 0;

    // p^74の形
    for (int p = 0; p < 25; ++p) {
        if (cnt[p] >= 74) ++ans;
    }

    // p^2 q^24とp^4 q^14の形
    for (int p = 0; p < 25; ++p) {
        for (int q = 0; q < 25; ++q) {
            if (p == q) continue;
            if (cnt[p] >= 4 && cnt[q] >= 14) ++ans;
            if (cnt[p] >= 2 && cnt[q] >= 24) ++ans;
        }
    }

    // p^2 q^4 r^4の形
    for (int p = 0; p < 25; ++p) {
        for (int q = 0; q < 25; ++q) {
            // 重複カウントを防ぐためにq < rにしている
            for (int r = q + 1; r < 25; ++r) {
                if (p == q || r == p) continue;
                if (cnt[p] >= 2 && cnt[q] >= 4 && cnt[r] >= 4) ++ans;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
