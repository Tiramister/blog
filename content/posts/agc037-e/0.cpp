#include <iostream>
#include <algorithm>
#include <string>

void solve() {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;

    std::string u = s;
    std::reverse(u.begin(), u.end());
    u = s + u;

    // 辞書順最小のものを選ぶ
    int si = 0;
    for (int i = 1; i < n; ++i) {
        if (u.substr(i, n) < u.substr(si, n)) si = i;
    }
    u = u.substr(si, n);

    // 先頭の文字がいくつ連続するか調べる
    int l;
    for (l = 0; l < n; ++l) {
        if (u[l] != u[0]) break;
    }
    auto back = u.substr(l);

    // 倍々にする
    --k;
    while (l < n && k > 0) {
        l = std::min(n, l * 2);
        --k;
    }

    // 先頭の文字を連結させて長さnにカット
    auto ans = std::string(l, u[0]) + back;
    ans = ans.substr(0, n);

    std::cout << ans << std::endl;
}
