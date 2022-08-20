// don't choose 0 or N-1
int i = (rng.next() % (N - 2)) + 1,
    j = (rng.next() % (N - 2)) + 1;
if (i == j) continue;
if (vs[i] == 0 || vs[i] == N - 1 || vs[j] == 0 || vs[j] == N - 1) continue;

// calculate difference
int cost = 0;
cost -= dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
cost -= dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
cost -= dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
cost -= dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

std::swap(qs[vs[i]], qs[vs[j]]);
std::swap(vs[i], vs[j]);

cost += dist(ps[vs[i - 1]], ps[vs[i]]) + dist(ps[vs[i]], ps[vs[i + 1]]);
cost += dist(ps[vs[j - 1]], ps[vs[j]]) + dist(ps[vs[j]], ps[vs[j + 1]]);
cost += dist(qs[vs[i] - 1], qs[vs[i]]) + dist(qs[vs[i]], qs[vs[i] + 1]);
cost += dist(qs[vs[j] - 1], qs[vs[j]]) + dist(qs[vs[j]], qs[vs[j] + 1]);

if (cost > 0) {
    // reject
    std::swap(vs[i], vs[j]);
    std::swap(qs[vs[i]], qs[vs[j]]);
}
