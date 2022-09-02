#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <queue>

// sに含まれないもので，小さい方から2つ
std::array<int, 2> mex(std::set<int> s) {
    std::array<int, 2> ret;
    int idx = 0;
    for (int x = 0;; ++x) {
        if (s.count(x)) continue;
        ret[idx] = x;
        if (++idx == 2) break;
    }
    return ret;
}

// choiceでSとS+mのどっちのMEXを取るか指定する
bool solve(const std::vector<int>& par, int choice) {
    int n = par.size();

    // 出次数
    std::vector<int> outdeg(n, 0);
    for (auto p : par) ++outdeg[p];

    std::queue<int> que;
    std::vector<int> assign(n, -1);
    for (int v = 0; v < n; ++v) {
        if (outdeg[v] == 0) {
            assign[v] = 0;
            que.push(v);
        }
    }

    // 子のassignの集合
    std::vector<std::set<int>> ch(n);
    while (true) {
        while (!que.empty()) {
            int v = que.front();
            que.pop();

            int u = par[v];
            ch[u].insert(assign[v]);

            // 親の出次数が0になったら割り当て
            if (--outdeg[u] == 0 && assign[u] < 0) {
                assign[u] = mex(ch[u])[0];
                que.push(u);
            }
        }

        bool finish = true;
        for (int v = 0; v < n; ++v) {
            if (assign[v] < 0) {
                // サイクルから1つ選んで，適当に割り当て
                // この割り当て(choice)を全探索
                finish = false;
                assign[v] = mex(ch[v])[choice];
                que.push(v);
                break;
            }
        }
        if (finish) break;
    }

    // Judge
    for (auto& c : ch) c.clear();
    for (int v = 0; v < n; ++v) {
        int u = par[v];
        ch[u].insert(assign[v]);
    }
    for (int v = 0; v < n; ++v) {
        if (assign[v] != mex(ch[v])[0]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> par(n);
    for (auto& p : par) {
        std::cin >> p;
        --p;
    }

    for (int choice = 0; choice < 2; ++choice) {
        if (solve(par, choice)) {
            std::cout << "POSSIBLE" << std::endl;
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE" << std::endl;
    return 0;
}
