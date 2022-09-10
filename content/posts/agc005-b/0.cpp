#include <iostream>
#include <set>
using namespace std;
using ll = long long;

int main() {
    int N;
    cin >> N;

    ll place[N + 1];
    // place[i]...値iのaにおけるindex

    for (int i = 1; i <= N; ++i) {
        ll a;
        cin >> a;
        place[a] = i;
        // 保持するのはindexなので、ここが普通と逆なことに注意
    }

    ll ans = 0;
    set<ll> used = {0, N + 1};
    // すでに見た要素のindexを保持する

    for (int i = 1; i <= N; ++i) {
        ll r, l;

        auto itr = used.lower_bound(place[i]);
        r = *itr;
        // lower_boundで右端を調べる(upper_boundでもいい)
        l = *(--itr);
        // その1個手前が左端

        ans += i * (place[i] - l) * (r - place[i]);
        used.insert(place[i]);
    }

    cout << ans << endl;
    return 0;
}
