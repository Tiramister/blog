for (int s = 0; s < (1 << n); ++s) {
    dp[s][0] = f[s];
}

for (int k = 1; k <= n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        dp[s][k] = dp[s][k - 1];
        if ((s >> (k - 1)) & 1) {
            dp[s][k] += dp[s ^ (1 << (k - 1))][k - 1];
        }
    }
}

for (int s = 0; s < (1 << n); ++s) {
    g[s] = dp[s][n];
}
