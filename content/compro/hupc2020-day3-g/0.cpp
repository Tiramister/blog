#include <iostream>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using lint = long long;
constexpr lint INF = 1LL << 60;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<lint> xs(n + 1), ws(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> xs[i] >> ws[i];

    // [i, j]を左から右へ移動するときのコスト
    auto lcost = vec(n + 1, vec(n + 1, 0LL));
    for (int l = 1; l <= n; ++l) {
        lint sum = ws[l] + 1;
        for (int r = l + 1; r <= n; ++r) {
            lcost[l][r] = lcost[l][r - 1] + sum * (xs[r] - xs[r - 1]);
            sum += ws[r];
        }
    }

    // [i, j]を右から左へ移動するときのコスト
    auto rcost = vec(n + 1, vec(n + 1, 0LL));
    for (int r = 1; r <= n; ++r) {
        lint sum = ws[r] + 1;
        for (int l = r - 1; l >= 1; --l) {
            rcost[l][r] = rcost[l + 1][r] + sum * (xs[l + 1] - xs[l]);
            sum += ws[l];
        }
    }

    std::vector<lint> bdp(n + 1, INF), rdp(n + 1, INF);
    // 文章中で定義したDPテーブル2つ
    bdp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int l = 0; l < i; ++l) {
            rdp[i] = std::min(rdp[i], bdp[l] + 1 + lcost[l + 1][i]);
        }

        for (int l = 1; l <= i; ++l) {
            bdp[i] = std::min(bdp[i], rdp[l] + rcost[l][i] + k);
        }
    }

    std::cout << bdp[n] << "\n";
}
