#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

ll fib[1000];

// Fibonacci数列を埋める
void precalc() {
    fib[0] = 1;
    fib[1] = 1;
    for(int i = 2; i < 1000; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    return;
}

// 正方行列の積
vector<vector<ll>> matmul(vector<vector<ll>> a, vector<vector<ll>> b) {
    int l = a[0].size();

    vector<vector<ll>> ret(l, vector<ll>(l, 0));

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < l; ++j) {
            for (int k = 0; k < l; ++k) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

// ダブリングによる行列累乗
vector<vector<ll>> matpow(vector<vector<ll>> m, int n) {
    int l = m[0].size();

    // 単位行列を返す
    if (n == 0) {
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < l; ++j) {
                m[i][j] = (i == j);
            }
        }
        return m;
    }

    if (n == 1) return m;

    if (n % 2) {
        return matmul(matpow(m, n - 1), m);
    } else {
        return matpow(matmul(m, m), n / 2);
    }
}


int main() {
    // Fibonacci数列を先に求める
    precalc();

    int H, W, K;
    cin >> H >> W >> K;
    --K;

    vector<vector<ll>> M(W, vector<ll>(W, 0));
    // 以降Mは0-indexedであることに注意

    // 左に移動するパターン
    for (int i = 2; i <= W; ++i) {
        M[i - 2][i - 1] = fib[i - 2] * fib[W - i] % MOD;
    }

    // 右に移動するパターン
    for (int i = 1; i <= W - 1; ++i) {
        M[i][i - 1] = fib[i - 1] * fib[W - i - 1] % MOD;
    }

    // 真下に移動するパターン
    for (int i = 1; i <= W; ++i) {
        M[i - 1][i - 1] = fib[i - 1] * fib[W - i] % MOD;
    }

    auto res = matpow(M, H);
    cout << res[K][0] << endl;
    return 0;
}
