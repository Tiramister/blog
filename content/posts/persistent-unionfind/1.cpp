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
