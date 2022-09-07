for (int s = 0; s < (1 << n); ++s) {
    // s の部分集合のみを全探索
    for (int t = s; t >= 0; t = ((t - 1) & s)) {
        g[s] += f[t];
    }
}
