template <int MOD> class ModInt { ... }
template <int MOD> class Combination { ... }

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;
const Combination<MOD> C(1 << 20);

int main() {
    /* ----- 入力 ----- */
    int N, H, D;
    cin >> N >> H >> D;

    /* ----- 1! + ... + N! ----- */
    mint fsum = 0;
    for (int l = 1; l <= N; ++l) {
        fsum += C.fact(l);
    }

    /* ----- DP ----- */
    vector<mint> dp(H + 1, 0), dpsum(H + 1, 0);
    dp[0] = dpsum[0] = C.fact(N) / fsum;
    // dp[h] = ブロック数の最大値がhで、そのような山の数が1個となるような操作数

    for (int h = 1; h <= H; ++h) {
        dp[h] = fsum * (dpsum[h - 1] -
                        (h - D - 1 >= 0 ? dpsum[h - D - 1] : 0));
        dpsum[h] = dpsum[h - 1] + dp[h];
    }

    cout << dp[H] << endl;
    return 0;
}
