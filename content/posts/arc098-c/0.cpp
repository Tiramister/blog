#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    string S;
    cin >> N >> S;

    int cnt[N + 1];
    // i文字目までにWがいくつあるか(1-indexed)

    // 累積和テーブルを埋めていく
    cnt[0] = 0;
    for (int i = 0; i < N; ++i) {
        cnt[i + 1] = cnt[i];
        if (S[i] == 'W') ++cnt[i + 1];
    }

    int ans = N;
    for (int i = 1; i <= N; ++i) {
        // 自分より西にいて西を向いている人が
        //  cnt[i-1]人
        // 自分より東にいて東を向いている人が
        //  (N-i)-(cnt[N]-cnt[i])人
        ans = min(ans, cnt[i - 1] + (N - i) - (cnt[N] - cnt[i]));
    }
    cout << ans << endl;
    return 0;
}
