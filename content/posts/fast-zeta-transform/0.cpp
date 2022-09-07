for (int s = 0; s < (1 << n); ++s) {
    for (int t = 0; t < (1 << n); ++t) {
        if ((s & t) == t) g[s] += f[t];
    }
}
