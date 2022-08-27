#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <cassert>

const std::vector<int> dxs{-1, 0, 1, 0}, dys{0, -1, 0, 1};
const std::string ways = "NWSE";

struct Parser {
    int h, w, cnt;
    int px, py, dir, i;
    std::vector<std::string> grid;
    std::string cmd;

    void fail() {
        std::cout << "-1\n";
        std::exit(0);
    }

    void ok() {
        std::cout << cnt << "\n";
        std::exit(0);
    }

    void move(bool moving) {
        char c = cmd[i++];
        if (!moving) return;

        switch (c) {
            case '^': {
                int nx = px + dxs[dir],
                    ny = py + dys[dir];
                if (grid[nx][ny] != '#') {
                    px = nx, py = ny;
                }
                break;
            }
            case 'v': {
                int nx = px - dxs[dir],
                    ny = py - dys[dir];
                if (grid[nx][ny] != '#') {
                    px = nx, py = ny;
                }
                break;
            }
            case '<': {
                dir = (dir + 1) % 4;
                break;
            }
            case '>': {
                dir = (dir + 3) % 4;
                break;
            }
        }
        ++cnt;

        if (grid[px][py] == 'g') ok();
    }

    bool cond() {
        char c = cmd[i++];
        if (c == '~') return !cond();
        if (c == 'T') return true;

        for (int j = 0; j < 4; ++j) {
            if (ways[j] == c) return dir == j;
        }

        int nx = px + dxs[dir],
            ny = py + dys[dir];
        return grid[nx][ny] == '#';
    }

    void expr_if(bool moving) {
        assert(cmd[i] == '[');
        ++i;

        exec(cond() && moving);

        assert(cmd[i] == ']');
        ++i;
    }

    void expr_while(bool moving) {
        assert(cmd[i] == '{');
        int beg = ++i;

        std::set<std::tuple<int, int, int>> visited;
        while (true) {
            auto state = std::make_tuple(px, py, dir);
            if (visited.count(state)) fail();  // loop
            visited.insert(state);

            i = beg;
            bool flag = cond() && moving;
            exec(flag);
            if (!flag) break;
        }

        assert(cmd[i] == '}');
        ++i;
    }

    void exec(bool moving) {
        while (true) {
            if (cmd[i] == '[') {
                expr_if(moving);

            } else if (cmd[i] == '{') {
                expr_while(moving);

            } else if (cmd[i] == '^' || cmd[i] == 'v' ||
                       cmd[i] == '<' || cmd[i] == '>') {
                move(moving);

            } else {
                break;
            }
        }
    }

    explicit Parser() : cnt(0), dir(0), i(0) {
        std::cin >> h >> w;

        grid.resize(h);
        for (auto& s : grid) std::cin >> s;

        for (int x = 0; x < h; ++x) {
            for (int y = 0; y < w; ++y) {
                if (grid[x][y] == 's') {
                    px = x, py = y;
                    grid[x][y] = '.';
                }
            }
        }

        std::cin >> cmd;
        cmd.push_back('$');
    }
};

void solve() {
    Parser p;
    p.exec(true);
    std::cout << "-1\n";
}
