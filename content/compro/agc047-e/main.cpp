#include <iostream>

void query(char c, int i, int j, int k) {
    std::cout << c << " " << i << " " << j << " " << k << "\n";
}

/* ----- several constants, functions ----- */

constexpr int A = 0, B = 1, S = 2;
constexpr int ZERO = 100, ONE = 101;
constexpr int K = 30, KB = 200;

void reset(int i) { query('+', ZERO, ZERO, i); }
void copy(int i, int j) { query('+', ZERO, i, j); }

void negate(int i) { query('<', i, ONE, i); }
void pow(int i, int k) {
    while (k--) query('+', i, i, i);
}

/* ----- main routine ----- */

void init() {
    query('+', A, B, 2);
    query('<', ZERO, 2, ONE);  // v[ZERO] = 0, v[ONE] = 1
    reset(2);

    query('+', ZERO, ONE, KB);
    for (int k = 1; k <= K; ++k) {
        query('+', KB + k - 1, KB + k - 1, KB + k);
        // v[KB + k] = 2^k
    }
}

void tobin(int xi, int l) {
    const int SB = l + K + 1;

    for (int k = K; k >= 0; --k) {
        query('+', SB, KB + k, SB + 1);
        query('<', xi, SB + 1, l + k);
        negate(l + k);  // v[l+k] = (sum + 2^k <= x)

        copy(l + k, SB + 1);
        pow(SB + 1, k);
        query('+', SB, SB + 1, SB);  // sum += (v[l+k] * 2^k)
    }
}

void multiply(int xi, int yi, int zi, int l) {
    for (int xk = 0; xk <= K; ++xk) {
        for (int yk = 0; yk <= K; ++yk) {
            query('+', xi + xk, yi + yk, l + 1);
            query('<', ONE, l + 1, l + 1);
            query('+', zi + xk + yk, l + 1, zi + xk + yk);
            // v[zi+xk+yk] += x[xk] & y[yk]
        }
    }

    for (int k = 0; k <= K * 2; ++k) {
        pow(zi + k, k);
        query('+', l, zi + k, l);
    }
}

void solve() {
    std::cout << 6048 << "\n";  // 総命令数

    init();

    constexpr int AB = 300, BB = 400, FB = 500;
    tobin(A, AB);
    tobin(B, BB);
    multiply(AB, BB, FB, S);
}
