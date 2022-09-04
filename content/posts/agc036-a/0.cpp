using namespace std;
using lint = long long;

// Z * Z < Sを満たす最小のZを求める
lint sqrti(lint S) {
    lint ok = 0, ng = 1e9 + 1;
    while (ng - ok > 1) {
        lint mid = (ok + ng) / 2;
        (mid * mid < S ? ok : ng) = mid;
    }
    return ok;
}

int main() {
    lint S;
    cin >> S;
    lint Z = sqrti(S);

    vector<lint> X(3), Y(3);
    X[0] = Y[0] = 0, X[2] = 1;

    if (S <= Z * (Z + 1)) {
        Y[1] = Z * (Z + 1) - S;
        X[1] = Z, Y[2] = Z + 1;
    } else {
        Y[1] = (Z + 1) * (Z + 1) - S;
        X[1] = Y[2] = Z + 1;
    }

    assert(X[1] * Y[2] - X[2] * Y[1] == S);
    for (int i = 0; i < 3; ++i) {
        assert(X[i] <= 1e9);
        assert(Y[i] <= 1e9);
        cout << X[i] << " " << Y[i] << " ";
    }
    cout << endl;
    return 0;
}
