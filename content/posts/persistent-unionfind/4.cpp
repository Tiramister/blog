    // 頂点xとyを繋げる
    void unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // parの更新を先にやるとバグるので注意
        num[x].push_back(make_pair(now, size(x, now) + size(y, now)));

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // timeに時刻を記録
        if (rank[x] == rank[y]) rank[x]++;
    }
