#include <iostream>

using namespace std;

int main() {
    int M, K;
    cin >> M >> K;

    // コーナーケース
    // M=0は下とまとめて良い
    if (M == 1) {
        if (K >= 1) {
            cout << -1 << endl;
        } else {
            cout << "0 0 1 1" << endl;
        }
        return 0;
    }

    // 可能性判定
    if (K >= (1 << M)) {
        cout << -1 << endl;
        return 0;
    }

    // 前半の出力
    for (int i = 0; i < (1 << M); ++i) {
        if (i != K) {
            cout << i << " ";
        }
    }
    cout << K << " ";

    // 後半の出力(逆順にするだけ)
    for (int i = (1 << M) - 1; i >= 0; --i) {
        if (i != K) {
            cout << i << " ";
        }
    }
    cout << K << " " << endl;

    return 0;
}
