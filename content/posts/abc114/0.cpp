#include <iostream>
#include <map>
#include <string>

using namespace std;

// b^nを計算する関数
int mypow(int b, int n) {
    if (n == 0) return 1;
    if (n == 1) return b;
    if (n % 2 == 0) {
        return mypow(b * b, n / 2);
    } else {
        return mypow(b, n - 1) * b;
    }
}

// 012と753を変換する変数
const string i2c = "753";
const map<char, int> c2i = {{'7', 0}, {'5', 1}, {'3', 2}};

int main() {
    int N;
    cin >> N;

    int ans = 0;

    // dは桁数
    for (int d = 3; d < 10; ++d) {
        for (int b = 0; b < mypow(3, d); ++b) {
            string S;

            int cb = b;
            // 1の位から753に変換してpushしていく
            for (int i = 0; i < d; ++i) {
                S.push_back(i2c[cb % 3]);
                cb /= 3;
            }

            // 7, 5, 3の出現回数を数える
            bool cnt[3];
            fill(cnt, cnt + 3, false);

            for (char c : S) {
                cnt[c2i[c]] = true;
            }

            bool judge = true;
            for (int i = 0; i < 3; ++i) {
                if (!cnt[i]) judge = false;
            }
            if (!judge) continue;

            // N以下ならカウントする
            if (stoi(S) <= N) ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}
