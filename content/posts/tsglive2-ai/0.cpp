class Robot {
public:
    explicit Robot(int _x, int _y, int _id);

    int x, y, id;
};

class Board {
public:
    explicit Board(int _H, int _W);

    // 標準入力を元に初期化する
    void load();

    // (x, y)が盤面内にあるか判定する
    bool inarea(int x, int y);

    int H, W;
    vector<vector<string>> brd;
    vector<Robot> beams, targets;
};
