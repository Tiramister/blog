#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    int N;
    cin >> N;

    pair<int, int> x[N];
    // (x_n, n)を保持

    for (int i = 0; i < N; ++i) {
        cin >> x[i].first;
        x[i].second = i + 1;
    }
    sort(x, x + N);
    // x_nでソート

    int a[N * N + 1], now = 0;
    fill(a, a + N * N + 1, -1);
    // aは1-indexed 埋まってなければ-1
    // 今a[now]まで埋まっている

    // x_nの小さい方から埋めていく
    for (int i = 0; i < N; ++i) {
        int idx, n;
        tie(idx, n) = x[i];
        a[idx] = n;

        // -1の箇所にnを左から詰めていく
        for (int j = 0; j < n - 1; ++j) {
            while (true) {
                if (a[++now] < 0) {
                    a[now] = n;
                    break;
                }
            }
        }

        // idxより左側にn-1個埋められなかったらアウト
        if (now > idx) {
            cout << "No" << endl;
            return 0;
        }
    }

    // 大小反転して同じことをする
    now = N * N + 1;
    for (int i = N - 1; i >= 0; --i) {
        int idx, n;
        tie(idx, n) = x[i];

        for (int j = n; j < N; ++j) {
            while (true) {
                if (a[--now] < 0) {
                    a[now] = n;
                    break;
                }
            }
        }

        if (now < idx) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    for (int i = 1; i <= N * N; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
