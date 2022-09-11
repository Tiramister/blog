#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int a[M], odd = 0;
    for (int i = 0; i < M; ++i) {
        cin >> a[i];
        odd += a[i] % 2;
    }

    if (M == 1) {
        cout << a[0] << endl;
        if (a[0] == 1) {
            cout << 1 << endl;
            cout << a[0] << endl;
        } else {
            cout << 2 << endl;
            cout << a[0] - 1 << " " << 1 << endl;
        }
        return 0;
    }

    // 可能性判定
    if (odd > 2) {
        cout << "Impossible" << endl;
        return 0;
    }

    // 奇数要素を両端に持っていく
    odd = 0;
    for (int i = 0; i < M; ++i) {
        if (a[i] % 2 == 1) {
            ++odd;
            if (odd == 1) {
                swap(a[i], a[0]);
            } else if (odd == 2) {
                swap(a[i], a[M - 1]);
            }
        }
    }

    // 数列aを出力
    for (int i = 0; i < M; ++i) {
        if (a[i] > 0) {
            cout << a[i] << " ";
        }
    }
    cout << endl;

    // 数列bを構築
    vector<int> b;

    --a[0];
    ++a[M - 1];
    for (int i = 0; i < M; ++i) {
        // 0を出力してはいけないことに注意
        if (a[i] > 0) b.push_back(a[i]);
    }

    // 数列bを出力
    cout << b.size() << endl;
    for (int c : b) {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}
