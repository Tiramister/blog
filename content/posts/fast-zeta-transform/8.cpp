for (int s = 0; s < (1 << n); ++s) {
    f[s] = g[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> k) & 1) {
            f[s] -= f[s ^ (1 << k)];
        }
    }
}
