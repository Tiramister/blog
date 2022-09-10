#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct edge {
    int from;
    int to;
    int cost;
    edge(int _from, int _to, int _cost) : from(_from), to(_to), cost(_cost){};
};

vector<edge> ans;

// [add, add + L)のバイパスを作る
void bypass(int add, int L) {
    if (L <= 0) return;
    for (int k = 19; k >= 0; --k) {
        if (L >= (1 << k)) {
            // [add, add + 2^k)を作る
            // k本の辺の後、つまり頂点k+1から20に辺を張る
            ans.push_back(edge(k + 1, 20, add));

            // [add + 2^k, add + L)を作る
            bypass(add + (1 << k), L - (1 << k));
            break;
        }
    }
    return;
}

int main() {
    int L;
    cin >> L;

    // 0の辺を全部張る
    for (int i = 1; i < 20; ++i) {
        ans.push_back(edge(i, i + 1, 0));
    }

    // 大まかにグラフを作る
    for (int k = 19; k >= 1; --k) {
        if (L >= (1 << k)) {
            // k本辺を張って[0, 2^k)を作る
            for (int i = 1; i <= k; ++i) {
                ans.push_back(edge(i, i + 1, 1 << (i - 1)));
            }

            // [2^k, L)を作る
            bypass(1 << k, L - (1 << k));
            break;
        }
    }

    cout << 20 << " " << ans.size() << endl;
    for (auto e : ans) {
        cout << e.from << " " << e.to << " " << e.cost << endl;
    }
    return 0;
}
