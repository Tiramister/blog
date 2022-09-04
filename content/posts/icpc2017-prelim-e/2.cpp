constexpr int mask = (1 << 16) - 1;
constexpr int INF = 1 << 30;

/* ----- 真理値表埋め ----- */
vector<vector<int>> T(17);
// T[l] = 長さlの論理式で表せる真理値表の集合(lは最小)

vector<int> U(1 << 16, INF);
// T[t] = 真理値表tを表す最短の論理式の長さ

void init() {
    // 長さ1は0, 1, a, b, c, dのみ
    T[1] = {0b0000000000000000,
            0b1111111111111111,
            0b1010101010101010,
            0b1100110011001100,
            0b1111000011110000,
            0b1111111100000000};
    for (auto t : T[1]) U[t] = 1;

    for (int k = 2; k <= 16; ++k) {
        for (auto t : T[k - 1]) {
            int v = mask ^ t;  // notを合成
            if (U[v] == INF) {
                U[v] = k;
                T[k].push_back(v);
            }
        }

        for (int i = 1; i <= k - 3 - i; ++i) {
            // 長さの和がk-3になる組を全て試す
            for (auto t1 : T[i]) {
                for (auto t2 : T[k - 3 - i]) {
                    int v = t1 & t2;  // andを合成
                    if (U[v] == INF) {
                        U[v] = k;
                        T[k].push_back(v);
                    }

                    v = t1 ^ t2;  // xorを合成
                    if (U[v] == INF) {
                        U[v] = k;
                        T[k].push_back(v);
                    }
                }
            }
        }
    }
}

/* ----- 構文解析 ----- */
string S;
int pat;  // a, b, c, dの割り振り

bool expr(int&);

// expr^expr, expr*expr
bool bin(int& i) {
    bool ret = expr(i);
    if (S[i] == '*') {
        ++i;
        ret = expr(i) && ret;
    } else if (S[i] == '^') {
        ++i;
        ret = expr(i) != ret;
    }
    return ret;
}

// 0, 1, a, b, c, d
bool term(int& i) {
    bool ret;
    if ('0' <= S[i] && S[i] <= '1') {
        ret = S[i] - '0';
    } else if ('a' <= S[i] && S[i] <= 'd') {
        ret = (pat >> (S[i] - 'a')) & 1;
    }
    ++i;
    return ret;
}

// term, -expr, (bin)
bool expr(int& i) {
    bool ret;
    if (S[i] == '(') {
        ++i;
        ret = bin(i);
        ++i;
    } else if (S[i] == '-') {
        ++i;
        ret = !expr(i);
    } else {
        ret = term(i);
    }
    return ret;
}

/* ----- main ----- */
bool solve() {
    cin >> S;

    // 真理値表を計算
    int i, tab = 0;
    for (pat = 0; pat < (1 << 4); ++pat) {
        i = 0;
        tab += expr(i) << pat;
    }

    // 前計算で得たテーブルを参照
    cout << U[tab] << endl;
    return true;
}
