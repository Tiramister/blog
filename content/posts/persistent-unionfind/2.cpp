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
