#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;
constexpr lint INF = 1LL << 60;

struct Eff {
    lint a, b;
    explicit Eff(lint a, lint b = 0) : a(a), b(b) {}

    // zero
    const static Eff id;

    bool operator==(const Eff& e) const {
        return a == e.a && b == e.b;
    }

    // max
    Eff operator+(const Eff& e) const {
        return Eff(std::max(a, e.a), std::max(b, e.b));
    }

    // composite
    Eff operator*(const Eff& e) const {
        return (*this == id || e == id) ? id : Eff(a + e.a, std::max(b + e.a, e.b));
    }

    // apply
    lint operator()(lint x) { return std::max(x + a, b); }
};

const Eff Eff::id(-INF, -INF);

template <class T>
using Vector = std::vector<T>;
template <class T>
using Matrix = Vector<Vector<T>>;

template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) { ... }

template <class T, class Int>
Matrix<T> mpow(Matrix<T> b, Int n) { ... }

void solve() {
    int n, m, s;
    lint w, k;
    std::cin >> n >> m >> w >> s >> k;
    --s;

    Matrix<Eff> mat(n, Vector<Eff>(n, Eff::id));
    while (m--) {
        int u, v;
        lint c;
        std::cin >> u >> v >> c;
        --u, --v;
        mat[u][v] = Eff(c);
    }

    mat = mpow(mat, k);

    auto e = Eff::id;
    for (int v = 0; v < n; ++v) {
        e = e + mat[s][v];
    }

    auto ans = e(w);
    std::cout << std::max(ans, -1LL) << std::endl;
}
