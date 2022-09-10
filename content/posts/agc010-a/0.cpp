#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int oddcnt = 0;
    for (int i = 0; i < N; ++i) {
        int A;
        cin >> A;

        // 2で割った余りを足すことで、奇数の場合のみ1を加算
        oddcnt += A % 2;
    }

    cout << (oddcnt % 2 == 0 ? "YES" : "NO") << endl;
    return 0;
}
