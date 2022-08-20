#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <chrono>

using ldouble = float;

// ライブラリは割愛

constexpr int TL = 2980;
Timer timer;
Random rng;

constexpr int N = 100;
std::vector<std::pair<int, int>> ps(N);

int dist(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int score;
void move(int& x, int& y, int nx, int ny, bool output) {
    score += std::abs(x - nx) + std::abs(y - ny);
    if (!output) {
        x = nx, y = ny;
        return;
    }

    while (x < nx) {
        std::cout << 'D';
        ++x;
    }
    while (x > nx) {
        std::cout << 'U';
        --x;
    }
    while (y < ny) {
        std::cout << 'R';
        ++y;
    }
    while (y > ny) {
        std::cout << 'L';
        --y;
    }
}

std::vector<std::pair<int, int>> qs(N);

void output(const std::vector<int>& vs, bool output) {
    int x = 0, y = 0;
    std::vector<int> pile;

    for (auto v : vs) {
        auto [nx, ny] = ps[v];
        move(x, y, nx, ny, output);

        if (output) std::cout << 'I';
        pile.push_back(v);
    }

    move(x, y, 10, 10, output);

    auto next = [&]() {
        if (y % 2 == 0) {
            if (x < 19) {
                move(x, y, x + 1, y, output);
            } else {
                move(x, y, x, y + 1, output);
            }
        } else {
            if (x > 10) {
                move(x, y, x - 1, y, output);
            } else {
                move(x, y, x, y + 1, output);
            }
        }
    };

    std::vector<std::vector<bool>> grid(20, std::vector<bool>(20, false));
    for (auto [x, y] : ps) {
        if (x >= 10 && y >= 10) grid[x][y] = true;
    }

    while (!pile.empty()) {
        int v = pile.back();
        pile.pop_back();
        while (grid[x][y]) next();

        if (output) std::cout << 'O';
        qs[v] = {x, y};
        grid[x][y] = true;
    }

    int i = 0;
    for (auto [nx, ny] : qs) {
        if (nx == 0 && ny == 0) {
            std::cerr << i << "\n";
        }
        ++i;
        move(x, y, nx, ny, output);
        if (output) std::cout << 'I';
    }
}

// greedy
std::vector<int> initial() {
    std::vector<int> vs;
    std::vector<bool> used(N, false);

    int rem = N;
    for (int i = 0; i < N; ++i) {
        auto [x, y] = ps[i];
        if (x >= 10 && y >= 10) {
            used[i] = true;
            qs[i] = {x, y};
            --rem;
        }
    }

    std::pair<int, int> prev(0, 0);

    while (rem--) {
        int nxt = -1;
        for (int u = 0; u < N; ++u) {
            if (used[u]) continue;

            nxt = u;
            break;

            if (nxt == -1 || dist(prev, ps[u]) < dist(prev, ps[nxt])) {
                nxt = u;
            }
        }

        vs.push_back(nxt);
        used[nxt] = true;
        prev = ps[nxt];
    }

    return vs;
}

constexpr ldouble INIT_TEMP = 3;

void solve() {
    for (auto& [x, y] : ps) std::cin >> x >> y;

    auto vs = initial();
    int n = vs.size();

    // calculate score and qs
    score = 0;
    output(vs, false);
    int cur = score;

    int mincur = cur;
    auto minvs = vs;

    // simulated annealing
    int time = 0, mod = 0, sim = 0;
    auto temp = INIT_TEMP;

    while (time < TL) {
        if (++sim, ++mod == 100000) {
            time = timer.get_ms();
            temp = INIT_TEMP * (TL - time) / TL;
            mod = 0;
        }

        // don't choose 0 or n-1
        int i = (rng.next() % (n - 2)) + 1,
            j = (rng.next() % (n - 2)) + 1;
        if (vs[i] == 0 || vs[i] == N - 1 || vs[j] == 0 || vs[j] == N - 1) continue;
        if (i == j) continue;

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

        if (rng.nextFloat() > std::exp(-cost / temp)) {
            // reject
            std::swap(vs[i], vs[j]);
            std::swap(qs[vs[i]], qs[vs[j]]);

        } else {
            cur += cost;
            if (cost == 0) continue;

            if (cur < mincur) {
                mincur = cur;
                minvs = vs;
            }
        }
    }

    output(minvs, true);
}
