int main() {
    int M;
    cin >> M;

    int S = 1 << M;
    vector<int> A(S * 2);  // {0, 0, 1, 1, ..., 2^M-1, 2^M-1}
    for (int i = 0; i < S; ++i) {
        A[i * 2] = A[i * 2 + 1] = i;
    }

    // next_permutationで全パターンを調べる
    do {
        vector<int> acc(S * 2 + 1, 0);  // 累積xor
        for (int i = 0; i < S * 2; ++i) {
            acc[i + 1] = acc[i] ^ A[i];
        }

        // 上の式で区間xorを計算
        set<int> B;
        for (int i = 0; i < S * 2; ++i) {
            for (int j = i + 1; j < S * 2; ++j) {
                if (A[i] == A[j]) B.insert(acc[i] ^ acc[j] ^ A[i]);
            }
        }

        // 区間xorの値が1種類なら条件成立
        if (B.size() == 1) {
            cout << *B.begin() << ":" << A << endl;
            // setの出力はテンプレでwrapしてある
        }
    } while (next_permutation(A.begin(), A.end()));

    return 0;
}
