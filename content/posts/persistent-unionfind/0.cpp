// 頂点数
const int V_NUM = 100000;

class UnionFind {
public:
    int par[V_NUM];  // 各頂点の親
    int rank[V_NUM]; // その頂点を根とする木の深さ
    int num[V_NUM];  // その頂点を根とする木の頂点数

    explicit UnionFind() {
        for (int i = 0; i < V_NUM; ++i) {
            par[i] = i;
        }
        fill(rank, rank + V_NUM, 0);
        fill(num, num + V_NUM, 1);
    }

    // xの親を返す + 経路圧縮
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            return par[x] = find(par[x]);
        }
    }

    // xとyが同じ木に属するか判定
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // xとyを含む木を結合する
    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        num[x] += num[y];
        if (rank[x] == rank[y]) rank[x]++;
    }

    // xを含む木の頂点数を返す
    int size(int x) {
        return num[find(x)];
    }
};
