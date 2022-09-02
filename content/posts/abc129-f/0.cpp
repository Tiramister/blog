#include <iostream>
#include <vector>

template <class T, class Int>
T ipow(T b, Int n) { ... }

template <class T>
using Vector = std::vector<T>;
template <class T>
using Matrix = Vector<Vector<T>>;

template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) { ... }
template <class T, class Int>
Matrix<T> mpow(Matrix<T> b, Int n) { ... }

struct ModInt { ... };

int ModInt::MOD;
using mint = ModInt;

using lint = long long;

int main() {
    lint l, a, b;
    std::cin >> l >> a >> b >> ModInt::MOD;

    auto ith = [&](lint x) {
        return (x <= a - b ? -1 : (x - a + b - 1) / b);
    };
    // x以上の最小の項

    mint ans = 0;
    for (int k = 1; k <= 18; ++k) {
        lint low = std::max(0LL, ith(ipow(10LL, k - 1))),
             high = std::min(l, ith(ipow(10LL, k)));
        // [low, high)項がk桁
        if (high < 0) continue;
        if (low > l) break;

        lint len = high - low;
        ans *= ipow(ipow(mint(10), k), len);
        // !! k*lenはオーバーフローするので注意 !!

        Matrix<mint> mat{{ipow(mint(10), k), 1, 0},
                         {0, 1, b},
                         {0, 0, 1}};
        mat = mpow(mat, len);
        ans += mat[0][1] * (a + b * low) + mat[0][2];
    }

    std::cout << ans << std::endl;
    return 0;
}
