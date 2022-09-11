#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

int main() {
    ll N;
    cin >> N;
    ll A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        A[i] -= i + 1;
    }

    sort(A, A + N);
    ll b = A[N / 2];

    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += abs(A[i] - b);
    }

    cout << ans << endl;
    return 0;
}
