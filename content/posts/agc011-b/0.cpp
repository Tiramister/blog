#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ll N;
    cin >> N;
    ll A[N];
    for (ll i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A, A + N);

    ll ans = 0, sum = 0;
    // sum = i匹目までの大きさの総和

    for (ll i = 0; i < N; ++i) {
        // i匹目まで全部くっついたやつはi+1匹目を吸収できるか?
        if (sum * 2 < A[i]) {
            // 吸収できないのでカウントリセット
            ans = 0;
        }
        sum += A[i];
        ++ans;
    }

    cout << ans << endl;
    return 0;
}
