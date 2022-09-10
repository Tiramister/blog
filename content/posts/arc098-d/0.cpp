#include <iostream>

using namespace std;

using ll = long long;

int main() {
    int N;
    cin >> N;

    ll A[N + 1];
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    ll sum[N + 1], xorsum[N + 1];
    sum[0] = xorsum[0] = 0;
    // 累積和と累積xor どちらも1-indexed

    for (int i = 1; i <= N; ++i) {
        sum[i] = sum[i - 1] + A[i];
        xorsum[i] = (xorsum[i - 1] ^ A[i]);
    }

    ll ans = 0;
    for (int l = 1; l <= N; ++l) {
        int ok = l, ng = N + 1;
        // (l, ok)は条件を満たし、(l, ng)は条件を満たさない
        // このokとngの距離を縮めていくことで境界値r0を求める

        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (sum[mid] - sum[l - 1] == (xorsum[mid] ^ xorsum[l - 1])) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        // 最終的なokが境界値r0となる
        ans += ok - l + 1;
    }

    cout << ans << endl;
    return 0;
}
