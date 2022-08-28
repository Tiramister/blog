auto dfs = [&](auto&& f, int x, int y, int dx, int dy) {
    int nx = x + dx, ny = y + dy;
    ...
    f(f, nx, ny, dx, dy);  // 再帰呼び出し
};

// ps: 電球の位置の集合
for (auto [x, y] : ps) {
    for (auto [dx, dy] : dxys) {
        dfs(dfs, x + dx, y + dy, dx, dy);
    }
}
