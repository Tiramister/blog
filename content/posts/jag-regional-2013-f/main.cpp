#include <iostream>
#include <string>
#include <cassert>

using lint = long long;
constexpr lint MOD = 1000000007;

struct Parser {
    std::string s;
    int i;
    Parser(const std::string& s) : s(s), i(0) {}

    void sp() {
        while (s[i] == ' ') ++i;
    }

    lint term() {
        if (s[i] == 'S') {
            // S<x>
            ++i;
            sp();
            assert(s[i] == '<');
            ++i;
            sp();
            auto e = expr();
            sp();
            assert(s[i] == '>');
            ++i;

            return e * e % MOD;

        } else {
            // number
            assert(std::isdigit(s[i]));

            lint ret = 0;
            while (std::isdigit(s[i])) {
                ret = ret * 10 + s[i] - '0';
                ++i;
            }
            return ret;
        }
    }

    lint expr() {
        auto ret = term();
        sp();

        while (s.substr(i, 2) == ">>") {
            // iのバックアップ(j)を用意
            int j = i;
            i += 2;
            sp();

            // >>の先がtermでないなら、shiftではないので復元する
            if (s[i] != 'S' && !std::isdigit(s[i])) {
                i = j;
                break;
            }

            // shift
            auto t = term();
            if (t > 30) {
                ret = 0;
            } else {
                ret >>= t;
            }
            sp();
        }

        return ret;
    }
};

bool solve() {
    std::string s;
    std::getline(std::cin, s);
    if (s == "#") return false;

    Parser parser(s);
    std::cout << parser.expr() << "\n";
    return true;
}
