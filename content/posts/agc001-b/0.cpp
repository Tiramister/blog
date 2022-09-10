#include <iostream>
using namespace std;
using ll = long long;

// (A, B)の平行四辺形内での軌道の長さ
ll reflect(ll A, ll B) {
    if (A > B) swap(A, B);

    ll ref = B / A;
    if (B % A == 0) {
        return (ref * 2 - 1) * A;
    } else {
        return ref * 2 * A + reflect(B % A, A);
    }
}

int main() {
    ll N, X;
    cin >> N >> X;
    cout << N + reflect(X, N - X) << endl;
    return 0;
}
