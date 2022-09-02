#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

enum Color { red,
             blue };

Color query(const std::vector<int>& v) {
    std::cout << '?';
    for (auto& x : v) {
        std::cout << ' ' << x + 1;
    }
    std::cout << std::endl;

    std::string s;
    std::cin >> s;
    if (s == "Red") return red;
    if (s == "Blue") return blue;
    std::exit(0);
}

void answer(const std::string& s) {
    std::cout << '!' << ' ' << s << std::endl;
    std::exit(0);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> idx(n * 2);
    std::iota(idx.begin(), idx.end(), 0);

    // send query of [l, l + n - 1]
    auto rquery = [&](int l) {
        std::vector<int> v;
        for (int i = 0; i < n; ++i) {
            v.push_back(idx[l + i]);
        }
        return query(v);
    };

    Color c = rquery(0);
    if (c == blue) {
        std::rotate(idx.begin(), idx.begin() + n, idx.end());
    }

    // [0, n-1]: red, [n, 2n-1]: blue
    // search border of query
    int ok = 0, ng = n;
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        c = rquery(mid);
        (c == red ? ok : ng) = mid;
    }

    std::rotate(idx.begin(), idx.begin() + ok, idx.end());
    // [0, n): red, [1, n]: blue

    std::string preans(n * 2, '*');
    preans[0] = 'R';
    preans[n] = 'B';

    // solve former
    for (int i = 1; i < n; ++i) {
        std::vector<int> v{idx[0], idx[n]};
        for (int j = 1; j < n; ++j) {
            if (j == i) continue;
            v.push_back(idx[j]);
        }
        c = query(v);
        preans[i] = (c == red ? 'B' : 'R');
    }

    // solve later
    for (int i = 1; i < n; ++i) {
        std::vector<int> v{idx[0], idx[n]};
        for (int j = 1; j < n; ++j) {
            if (j == i) continue;
            v.push_back(idx[n + j]);
        }
        c = query(v);
        preans[n + i] = (c == red ? 'B' : 'R');
    }

    // convert to answer
    std::string ans(n * 2, '*');
    for (int i = 0; i < n * 2; ++i) {
        ans[idx[i]] = preans[i];
    }

    answer(ans);
    return 0;
}
