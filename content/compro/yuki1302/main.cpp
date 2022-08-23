#include <atcoder/modint>
#include <iostream>
#include <vector>

template <class T>
struct Combination { ... };

using namespace std;

using mint = atcoder::modint998244353;
const Combination<mint> C(200000);

void solve() {
    int n;
    cin >> n;

    mint ans = 0;
    for (int k = 0; k <= n - 2; ++k) {
        ans += C.binom(n, k) * mint(n).pow(n - 2 - k) * C.invfact(n - 2 - k);
    }
    cout << (ans * C.fact(n - 2) / mint(n).pow(n - 2)).val() << "\n";
}
