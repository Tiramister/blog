for (int s = 0; s < (1 << n); ++s) {
    dp[s] = f[s];
}

for (int k = 1; k <= n; ++k) {
    // この時点でdp[s]は上の実装のdp[s][k-1]と一致
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> (k - 1)) & 1) {
            dp[s] += dp[s ^ (1 << (k - 1))];
        }
    }
}

for (int s = 0; s < (1 << n); ++s) {
    g[s] = dp[s];
}
