const int INF = 1 << 25;

// 頂点数
const int V_NUM = 100000;

class persistentUF {
public:
    int now;         // 現在時刻
    int par[V_NUM];  // 各頂点の親
    int rank[V_NUM]; // その頂点を根とする木の深さ
    int time[V_NUM]; // 親がいつ更新されたか
    vector<pair<int, int>> num[V_NUM]; // (時刻, 頂点数)を要素にもつvector

    explicit persistentUF() {
        now = 0;
        for (int i = 0; i < V_NUM; ++i) {
            par[i] = i;
            num[i].push_back(make_pair(0, 1)); // 時刻0にて頂点数は1
        }
        fill(rank, rank + V_NUM, 0);
        fill(time, time + V_NUM, INF); // 自身が根の間は便宜上INFとする
    }

    // 時刻tにおけるxの親を返す
    int find(int x, int t) {
        if (t < time[x]) {
            return x;
        } else {
            return find(par[x], t);
        }
    }

    // 時刻tにてxとyが同じ木に属するか判定
    bool same(int x, int y, int t) {
        return find(x, t) == find(y, t);
    }

    // 頂点xとyを繋げる
    int unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return now;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // parの更新を先にやるとバグるので注意
        num[x].push_back(make_pair(now, size(x, now) + size(y, now)));

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // timeに時刻を記録
        if (rank[x] == rank[y]) ++rank[x];
    }

    // 時刻tにおいて、頂点xを含む木の要素数を返す
    int size(int x, int t) {
        x = find(x, t);

        // 適切な情報が入ったindexを二分探索で探り当てる
        int ok = 0, ng = num[x].size();
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (num[x][mid].first <= t) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        return num[x][ok].second;
    }
};
