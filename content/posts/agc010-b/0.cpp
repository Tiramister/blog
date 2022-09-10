#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll N;
    cin >> N;

    ll A[N], sum = 0;
    for (ll i = 0; i < N; ++i) {
        cin >> A[i];
        sum += A[i];
    }

    if (sum % (N * (N + 1) / 2) > 0) {
        cout << "NO" << endl;
        return 0;
    }

    // 合計操作回数
    ll M = sum / (N * (N + 1) / 2);

    for (ll i = 0; i < N; ++i) {
        ll d = A[(i + 1) % N] - A[i];

        // 箱iの選ばれる回数は(M-d)/Nとなる
        // この値は非負整数でなくてはならない
        if (M < d || (M - d) % N > 0) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}
