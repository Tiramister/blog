class Robot {
public:
    explicit Robot(int _x, int _y, int _id);

    // メンバ変数を出力
    void print();

    // 方向dの先にtargetがいればtargets内でのindexを返す
    // targetがいなければ-1を返す
    int beam_search(const Board& board, int d) const;

    // targetをdの方向へ動かしたときの動きをシミュレートする
    void target_move(const Board& board, int d);

    int x, y, id;
};

class Board {
public:
    explicit Board(int _H, int _W);

    // 標準入力からマップを読み込み、ロボットをふるい分け
    void load();

    // ロボットの情報を出力
    void print();

    // マス(x, y)がボード内にあるか
    bool inarea(int x, int y) const;

    // beamsの各Robotからビームを四方へ拡散させる
    void beam_diffusion();

    int H, W;
    vector<string> brd;
    vector<Robot> beams, targets;
};
