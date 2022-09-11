    // 時刻tにおいて、頂点xを含む木の要素数を求める
    int size(int x, int t) {
        x = find(x, t);

        // 適切な情報が入ったindexを二分探索で探り当てる
        int ok = 0, ng = num[x].size();
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (num[mid].first <= t) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        return num[ok].second;
    }
