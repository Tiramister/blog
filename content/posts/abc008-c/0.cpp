template <typename T>
using V = vector<T>;
using ll = long long;

#define DOUBLE(n) static_cast<double>(n)
#define REP(i, n) FOR(i, 0, n)

#define fcout cout << fixed << setprecision(10)

/* ---------- ここまでマクロ ---------- */

const ll INF = 1LL << 50;

int main() {
    ll N;
    cin >> N;

    V<ll> C(N);
    REP(i, N) {
        cin >> C[i];
    }
    C.pb(INF);    // 番兵

    SORT(C);

    double ans = 0;
    ll mul = 1;
    // 同じ値がダブっていたとき用

    REP(i, N) {
        if (C[i] == C[i + 1]) {
            mul++;
            continue;
            // 値被りなのでスルー
            // 何もしないとi=N-1でC[N]にアクセスしようとしてセグフォる
            // だが先に追加した番兵によってそれが防がれている
        }

        ll cnt = 0;
        // 自分の約数が書かれたコインを数える
        REP(j, i) {
            if (C[i] % C[j] == 0) cnt++;
        }

        double p;
        // 先程出した確率を実際に計算する
        if (cnt % 2 == 0) {
            p = DOUBLE(cnt / 2 + 1) / (cnt + 1);
        } else {
            p = 0.5;
        }
        ans += p * mul;

        mul = 1;
        // mulの初期化を忘れないように
    }

    fcout << ans << endl;
    return 0;
}
