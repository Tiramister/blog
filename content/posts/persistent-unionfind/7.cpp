const int INF = 1 << 25;

// 頂点数
const int V_NUM = 100000;

class persistentUF {
public:
    int now;         // 現在時刻
    int par[V_NUM];  // 各頂点の親
    int rank[V_NUM]; // その頂点を根とする木の深さ
    int time[V_NUM]; // 親がいつ更新されたか

    explicit persistentUF() {
        now = 0;
        for (int i = 0; i < V_NUM; ++i) {
            par[i] = i;
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
    // 繋げた直後の時刻を返す
    int unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return now;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // timeに時刻を記録
        if (rank[x] == rank[y]) ++rank[x];

        return now;
    }
};
