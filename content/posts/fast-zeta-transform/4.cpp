for (int s = 0; s < (1 << n); ++s) {
    g[s] = f[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> k) & 1) {
            g[s] += g[s ^ (1 << k)];
        }
    }
}
