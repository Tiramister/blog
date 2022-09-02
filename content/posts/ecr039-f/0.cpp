#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

int main() {
    int n, x;
    std::string t;
    std::cin >> n >> x >> t;

    auto sdp = vec(x + 2, vec(n + 1, vec(n + 1, mint(0))));
    auto pdp = sdp, adp = sdp;
    auto cnts = vec(x + 2, mint(0));    // 解
    auto lenpow = vec(x + 2, mint(0));  // 2^|F(k)|

    // 初期化
    for (int k = 0; k < 2; ++k) {
        std::string s(1, '0' + k);  // F(k)

        for (int l = 0; l <= n; ++l) {
            // 空文字列
            sdp[k][l][l] = 2;
            pdp[k][l][l] = 2;
            adp[k][l][l] = 1;

            if (s == t.substr(l, 1)) {
                sdp[k][l][l + 1] = 1;
                pdp[k][l][l + 1] = 1;
                adp[k][l][l + 1] = 1;
            }
        }
        cnts[k] = adp[k][0][n];
        lenpow[k] = 2;
    }

    for (int k = 2; k <= x; ++k) {
        lenpow[k] = lenpow[k - 1] * lenpow[k - 2];

        for (int l = 0; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                pdp[k][l][r] = 0;
                sdp[k][l][r] = 0;
                adp[k][l][r] = 0;

                for (int i = l; i <= r; ++i) {
                    // F(k-1)から[l, i)を貰う
                    pdp[k][l][r] += (i == r ? pdp : adp)[k - 1][l][i] * pdp[k - 2][i][r];
                    sdp[k][l][r] += sdp[k - 1][l][i] * (i == l ? sdp : adp)[k - 2][i][r];
                    adp[k][l][r] += adp[k - 1][l][i] * adp[k - 2][i][r];
                }
            }
        }

        // 解の更新
        cnts[k] = cnts[k - 1] * lenpow[k - 2] + cnts[k - 2] * lenpow[k - 1];
        for (int i = 1; i < n; ++i) {
            cnts[k] += sdp[k - 1][0][i] * pdp[k - 2][i][n];
        }
    }

    std::cout << cnts[x] << std::endl;
    return 0;
}
