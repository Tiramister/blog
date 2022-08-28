#include <iostream>
#include <vector>
#include <string>

// 文字列を3進数でエンコード
int enc(const std::string& s) {
    int ret = 0;
    for (char c : s) {
        ret = ret * 3 + (c - '1');
    }
    return ret;
}

void solve() {
    int q, m;
    std::cin >> q >> m;

    // k = 3^m
    int k = 1;
    for (int i = 0; i < m; ++i) k *= 3;

    std::vector<bool> out(k, false);  // 既に上位互換が存在するか

    // 下位互換を全てtrueに更新する
    auto propagate = [&](auto&& f, std::string& s) -> void {
        if (out[enc(s)]) return;  // 枝刈り

        out[enc(s)] = true;
        for (int i = 0; i < m; ++i) {
            if (s[i] == '1') continue;
            --s[i];
            f(f, s);
            ++s[i];
        }
    };

    while (q--) {
        std::string s;
        std::cin >> s;

        if (out[enc(s)]) {
            std::cout << "1";
            continue;
        }

        std::cout << "0";

        // 下位互換を更新
        for (int i = 0; i < m; ++i) {
            if (s[i] == '1') continue;
            --s[i];
            propagate(propagate, s);
            ++s[i];
        }
    }

    std::cout << "\n";
}
