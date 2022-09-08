#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;

template <typename T, typename U>
T mypow(T b, U n) {
    if (n == 0) return 1;
    if (n == 1) return b /* % MOD */;
    if (n % 2 == 0) {
        return mypow(b * b /* % MOD */, n / 2);
    } else {
        return mypow(b, n - 1) * b /* % MOD */;
    }
}

vector<ll> primes, cubes;

// 10^5以下の素数と、10^10以下の立方数を列挙する
void precalc() {
    bool isp[100010];
    fill(isp, isp + 100010, true);

    for (ll i = 2; i * i < 1e10; ++i) {
        if (!isp[i]) continue;
        primes.push_back(i);
        for (ll j = 2; i * j <= 100000; ++j) isp[i * j] = false;
    }

    for (ll p : primes) {
        if (p * p * p > 1e10) break;
        cubes.push_back(p * p * p);
    }
}

// 標準形に変換
ll delcube(ll n) {
    for (ll c : cubes) {
        while (n % c == 0) n /= c;
    }
    return n;
}

// 標準形の補数を求める
ll anticube(ll n) {
    ll ret = 1;

    for (ll p : primes) {
        if (p * p > n) break;
        if (n % p > 0) continue;

        int c = 0;
        while (n % p == 0) {
            n /= p;
            ++c;
        }
        ret *= mypow(p, 3 - c);
    }

    // 最後に残ったnは素数か1
    // 素数なら指数は1
    ret *= mypow(n, 2);
    return ret;
}

int main() {
    precalc();

    int N;
    cin >> N;

    // 標準形をキーに、その個数を保持する
    map<ll, int> cnt;
    for (int i = 0; i < N; ++i) {
        ll s;
        cin >> s;
        s = delcube(s);
        if (cnt.count(s) == 0) cnt[s] = 0;
        ++cnt[s];
    }

    int ans = 0;
    for (auto p : cnt) {
        if (p.second == 0) continue;
        if (p.first == 1) {  // 立方数の集合は例外
            ++ans;
            continue;
        }

        ll opp = anticube(p.first);

        // 補数集合と、大きい方を選ぶ
        if (cnt.count(opp)) {
            ans += max(cnt[p.first], cnt[opp]);
            cnt[p.first] = cnt[opp] = 0;
        } else {
            ans += cnt[p.first];
        }
    }

    cout << ans << endl;
    return 0;
}
