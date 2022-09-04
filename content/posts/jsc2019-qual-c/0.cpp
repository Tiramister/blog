using namespace std;
using mint = ModInt<1000000007>;

int main() {
    int N;
    string S;
    cin >> N >> S;

    int K = 0;
    mint ans = 1;
    for (auto c : S) {
        if ((c == 'W') == (K % 2 == 0)) {
            // 保留中のどれかの右端にする
            ans *= K;
            if ((--K) < 0) break;
        } else {
            // iを左端にする　右端は保留
            ++K;
        }
    }

    if (K != 0) {
        // invalidなマッチング
        cout << 0 << endl;
        return 0;
    }

    // N!を掛けて出力
    for (int i = 1; i <= N; ++i) ans *= i;
    cout << ans << endl;
    return 0;
}
