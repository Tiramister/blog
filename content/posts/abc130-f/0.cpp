#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <limits>

using lint = long long;

struct Point {
    lint x, y, dx, dy;
};

const std::string dir = "RLUD";
const std::vector<lint>
    dxs{1, -1, 0, 0},
    dys{0, 0, 1, -1};

constexpr lint INF = 5e8;

int main() {
    int n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (auto& p : ps) {
        char d;
        std::cin >> p.x >> p.y >> d;
        p.x *= 2, p.y *= 2;

        for (int i = 0; i < 4; ++i) {
            if (d == dir[i]) {
                p.dx = dxs[i];
                p.dy = dys[i];
            }
        }
    }

    // wx(t), wy(t)を返す
    auto sim = [&](lint t) {
        lint xmin = INF * 2, xmax = -INF * 2,
             ymin = INF * 2, ymax = -INF * 2;

        for (const auto& p : ps) {
            lint x = p.x + p.dx * t,
                 y = p.y + p.dy * t;
            xmin = std::min(xmin, x);
            xmax = std::max(xmax, x);
            ymin = std::min(ymin, y);
            ymax = std::max(ymax, y);
        }

        return std::make_pair(xmax - xmin, ymax - ymin);
    };

    // s(t)を返す
    auto area = [&](lint t) {
        lint dx, dy;
        std::tie(dx, dy) = sim(t);
        return dx * dy;
    };

    lint ans = std::numeric_limits<lint>::max();

    for (int d = -2; d <= 2; ++d) {
        lint ok = 0, ng = INF;
        // okの左側傾き <= d

        // w_xの探索
        while (ng - ok > 1) {
            lint mid = (ok + ng) / 2;

            lint pdx, ndx;
            std::tie(pdx, std::ignore) = sim(mid - 1);
            std::tie(ndx, std::ignore) = sim(mid);

            (ndx - pdx <= d ? ok : ng) = mid;
        }
        ans = std::min(ans, area(ok));

        // w_yの探索
        ok = 0, ng = INF;
        while (ng - ok > 1) {
            lint mid = (ok + ng) / 2;

            lint pdy, ndy;
            std::tie(std::ignore, pdy) = sim(mid - 1);
            std::tie(std::ignore, ndy) = sim(mid);

            (ndy - pdy <= d ? ok : ng) = mid;
        }
        ans = std::min(ans, area(ok));
    }

    // 最後に4で割る
    std::cout << ans / 4
              << (ans % 4 == 0
                      ? ""
                      : ans % 4 == 1
                            ? ".25"
                            : ans % 4 == 2
                                  ? ".5"
                                  : ".75")
              << std::endl;
    return 0;
}
