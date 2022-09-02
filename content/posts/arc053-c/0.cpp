#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<lint, lint>> ps(n);
    for (auto& p : ps) {
        std::cin >> p.first >> p.second;
    }

    std::sort(ps.begin(), ps.end(),
              [](auto a, auto b) {
                  bool aneg = a.first < a.second,
                       bneg = b.first < b.second;
                  if (aneg != bneg) {
                      return aneg > bneg;
                  } else if (aneg) {
                      return a.first < b.first;
                  } else {
                      return a.second > b.second;
                  }
              });

    lint ans = 0, sum = 0;
    for (auto p : ps) {
        sum += p.first;
        ans = std::max(ans, sum);
        sum -= p.second;
    }

    std::cout << ans << std::endl;
    return 0;
}
