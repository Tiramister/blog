bool Robot::beam_search(const Board& board, int d) const {
    int nx = x, ny = y;
    while (board.inarea(nx, ny) && board.brd[nx][ny] != "*") {
        nx += dx[d];
        ny += dy[d];

        for (const Robot& target : board.targets) {
            if (target.x == nx && target.x == ny) {
                return true;
            }
        }
    }

    return false;
}
