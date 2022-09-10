#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        ll A, B;
        cin >> A >> B;
        if (A > B) {
            swap(A, B);
        }  // A <= B

        ll ok = A, ng = B + 1;
        // K = Aのときは前半と同様にマッチングすればいい

        while (ng - ok > 1) {
            ll K = (ok + ng) / 2;
            ll m = (K + A) / 2;

            // コーナーケース
            if (K == A) --m;

            if (m * (A + K - m) < A * B) {
                ok = K;
            } else {
                ng = K;
            }
        }
        cout << ok + A - 2 << endl;
    }
    return 0;
}
