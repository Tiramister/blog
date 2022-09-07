using bits = bitset<500>;
constexpr int INF = 1 << 30;

void solve() {
    /* ----- 入力 ----- */
    int N, M;
    cin >> N >> M;

    int ans = 0;
    if (N <= 23) {
        /* ----- Nが小さいとき ----- */
        vector<bits> B(N);
        for (auto& b : B) cin >> b;

        // 部分集合を全列挙
        for (int b = 0; b < (1 << N); ++b) {
            bits pat(0);
            for (int i = 0; i < N; ++i) {
                if ((b >> i) & 1) pat ^= B[i];
            }

            // xorが0なら要素数で更新
            if (pat.none()) {
                ans = max(ans, __builtin_popcount(b));
            }
        }
    } else {
        /* ----- Mが小さいとき ----- */
        vector<int> dp(1 << M, -INF);
        dp[0] = 0;

        for (int i = 0; i < N; ++i) {
            bits s;
            cin >> s;
            int b = s.to_ulong();  // 入力を整数に変換

            vector<int> ndp = dp;
            for (int p = 0; p < (1 << M); ++p) {
                ndp[b ^ p] = max(ndp[b ^ p], dp[p] + 1);
                // bを使う場合で更新
            }
            swap(dp, ndp);
        }
        ans = dp[0];
    }
    cout << ans << endl;
}
