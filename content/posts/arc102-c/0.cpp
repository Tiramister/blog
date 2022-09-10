#include <iostream>
using namespace std;
using ll = long long;

ll triple(ll a) {
    return a * a * a;
}

int main() {
    ll N, K;
    cin >> N >> K;
    ll ans = triple(N / K);
    if (K % 2 == 0) {
        ans += triple((N + K / 2) / K);
    }
    cout << ans << endl;
    return 0;
}
