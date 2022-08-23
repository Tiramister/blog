#include <iostream>
#include <vector>
#include <string>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.length();

    vector<int> len(n + 1, n);  // S[i, n)に対する解の長さ
    len[n] = 1;
    auto nxt = vec(n + 1, vec(26, -1));
    // S[i, n)で一番手前にあるcの位置(なければ-1)

    for (int i = n - 1; i >= 0; --i) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;

        for (auto j : nxt[i]) {
            int nlen = (j == -1 ? 0 : len[j + 1]) + 1;
            len[i] = min(len[i], nlen);
        }
    }

    int i = 0, l = len[0];
    while (l > 0) {
        int nc = -1;  // 次の文字

        for (int c = 0; c < 26; ++c) {
            auto j = nxt[i][c];
            int nlen = (j == -1 ? 0 : len[j + 1]) + 1;

            if (nlen == l) {
                nc = c;
                break;
            }
        }

        cout << char(nc + 'a');
        i = nxt[i][nc] + 1;
        --l;
    }
    cout << "\n";
}
