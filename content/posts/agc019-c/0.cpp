#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <vector>
using namespace std;

template <typename T>
using V = vector<T>;
using ll = long long;

#define SIZE(v) (static_cast<ll>((v).size()))
#define ALL(v) (v).begin(), (v).end()
#define SORT(v) sort(ALL(v))

const double PI = acos(-1);


// BITオブジェクト、Range Maximum Queryバージョン
class BIT {
public:
    explicit BIT(ll N, ll v) : V_NUM(N) {
        data.resize(N);
        fill(ALL(data), v);
    }

    ll query(ll i) {
        ll ret = 0;
        while (i > 0) {
            ret = max(ret, data[i]);
            i -= (i & -i);
        }
        return ret;
    }

    void update(ll i, ll v) {
        while (i < V_NUM) {
            data[i] = max(data[i], v);
            i += (i & -i);
        }
    }

    ll V_NUM;
    V<ll> data;
};

// 座標(coordinate)を保持する構造体
struct coo {
    coo(ll _x = 0, ll _y = 0) : x(_x), y(_y){};
    ll x;
    ll y;

    // ソートするために比較演算子をオーバーロードする
    bool operator<(const coo& r) const {
        return x == r.x ? y < r.y : x < r.x;
    }
};

// Y座標で座圧をする
map<ll, ll> compress(const V<coo>& a) {
    set<ll> sety;
    for (coo c : a) {
        sety.insert(c.y);
    }

    map<ll, ll> ret;
    ll idx = 1;
    for (ll y : sety) {
        ret[y] = idx;
        ++idx;
    }

    return ret;
}

int main() {
    cout << fixed << setprecision(12);

    // startとgoal
    coo s, g;
    cin >> s.x >> s.y >> g.x >> g.y;

    // startの方が下にくるようにする
    if (s.y > g.y) swap(s, g);

    ll N;
    cin >> N;
    V<coo> a;
    // 長方形領域内にある噴水のみを記録する

    for (ll i = 0; i < N; ++i) {
        ll x, y;
        cin >> x >> y;
        if (y < s.y || g.y < y) continue;

        if (s.x < g.x) {
            if (s.x <= x && x <= g.x) {
                a.push_back(coo(x - s.x, y - s.y));
            }
        } else {
            // startとgoalのX座標が逆の場合はこっちも左右反転する
            if (g.x <= x && x <= s.x) {
                a.push_back(coo(s.x - x, y - g.y));
            }
        }
    }

    SORT(a);
    map<ll, ll> com = compress(a);

    BIT bit(SIZE(com) + 1, 0);

    for (coo c : a) {
        ll y = com[c.y];
        bit.update(y, bit.query(y) + 1);
        // bit.query(y)でy以下の最大値を求める
        // それに1加えた値で更新
    }

    // BIT全体の最大値が答え
    ll turn = bit.query(SIZE(com));

    double ans = (abs(g.x - s.x) + abs(g.y - s.y)) * 100;
    // 噴水を無視した場合の距離
    ans -= (20 - PI * 5) * turn;
    // 曲がる分だけ削れる

    // コーナーケース
    if (turn == abs(g.y - s.y) + 1 || turn == abs(g.x - s.x) + 1) ans += PI * 5;

    cout << ans << endl;
    return 0;
}
