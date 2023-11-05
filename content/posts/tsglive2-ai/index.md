---
title: "TSG LIVE! 2 ライブ AI プログラミング 反省"
date: 2018-12-20
tags: [voluntary, marathon]
---

この記事は [TSG Advent Calendar 2018](https://adventar.org/calendars/3450) の 20 日目の記事として書かれたものです。

10 日前にこの Advent Calendar で「 [TSG LIVE! 2 ライブ競技プログラミング反省](https://blog.tiramister.net/posts/tsglive2-compro/)」という記事を書きました。今回はその続きとして、私がプレイヤーとして参加したもう 1 つの企画「 **ライブ AI プログラミング** 」について書きます。

どういう企画か簡単に説明すると、「75 分間でできるだけ強い **ゲーム AI** を作る」という企画です。「ゲーム AI」と言ってもそこまで大それたものではなく、ゲームをプレイするプログラムを指します。

ちなみに本コンテストの作問者である moratorium さんも、Advent Calendar で「 [TSG live AI コンテストの内容と感想、盤面生成に関する妄想など](https://moraprogramming.hateblo.jp/entry/2018/12/12/121531) 」という記事を投稿しています。裏の話が見られて面白いので、ぜひこちらも読んでみてください。

## ゲーム概要[^1]

[^1]: 先に上げた [moratorium さんの記事](https://moraprogramming.hateblo.jp/entry/2018/12/12/121531) にゲーム動画が載っています。

このゲームは攻守に分かれてのターン制で行われる。

$H \\times W$ のまばらに壁が配置され、外周が壁で囲まれた 2 次元グリッドがある。グリッド上には **Beam** 、 **Target** と呼ばれるロボットがそれぞれ最初 $N$ 台、 $M$ 台配置されている。

各ターン、攻撃側は Beam、守備側は Target のうち 1 台を、上下左右のうちいずれかに動かすことができる。このとき各ロボットは壁か他のロボットに接触するまで、その方向に動き続ける。

さらに Beam は移動の際、移動する方向に **ビーム** を打つことができる。ビームは壁によって遮蔽されるが、ビーム上にいた Target は消滅する。さらにビームは盤面上に残り続け、Target にとっては壁となる(接触しても消滅はしない)。

### スコアと制約

各ケースについて攻守を交代し、共通の盤面にてゲームを行う。そして攻撃時に Target をより早く全滅させたプレイヤーに所定のスコアが入る。なおゲームは最大 300 ターンまで行われる。

制約、スコア、ケース数は以下の通り。

- $(H = W = 10, N = 3, M = 2, Score = 40) \\times 10$
- $(H = W = 20, N = 10, M = 3, Score = 100) \\times 3$
- $(H = W = 30, N = 20, M = 5, Score = 200) \\times 1$

## 本番の流れ

### 環境整備

それでは早速乱択を、とやりたくなりますがここで思い留まります。

過去に何度か長めの実装をした経験[^longcode]から、適当に実装したら後でコードが壊滅することは目に見えていました。かといって、十分丁寧に実装するには 75 分は短いかも分かりません。

[^longcode]: [HTTF2019](https://atcoder.jp/contests/future-contest-2019-qual/) 、 [Codefestival AI Challenge 2018](https://www.exkazuu.net/AIChallenge2018AtCodeFestival/) 等。

少し悩んだ結果、自分の実装スピードを信じてクラスから実装することにしました。結果としては実装が幾分楽になったので、この判断は正しかったように思います。

初期段階では、クラスの構造は以下のような感じでした。

```cpp
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
```

一番懸念していた `Board::load()` の実装もそれほど複雑ではなく、各メンバ関数の具体的な実装は 20 分くらいで終わりました。

ちなみにこれは競プロの癖ですが、わざわざメンバ変数を private にはしません。普段のプログラミングでやったらアウトですが、どのみち使い捨てるコードなので。

### スペースのある方へ

そして乱択の実装に移るわけですが、最低限移動できることを担保するために「1 マス先が壁でない方向へ移動する」ように実装しました。
この時点で大体 30 分です。

しかしこの時点で、

- 二重 for 文で同じ変数名を使っている。
- 遷移をミスって、for で無限ループが起きる[^for_loop]。
- 誤読して間違えた Robot id を出力する。
- 壁を表す文字を勘違いする[^wall]。

[^for_loop]: `for(int i = 0; i < 4; d = (d + 1) % 4)` のように、ループ回数を制御する `i` をインクリメントし忘れました。`
[^wall]: 競プロで壁と言えば `#` なのですが、今回は `*` でした。思い込みダメ、絶対。

といった酷いミスを連発しており、これらの対処に 20 分ほど費やしてしまいました。

### Beam の改良

次に目指したのは「攻撃時に Beam と同じ列か行にいる Target を確実に潰す」という動きの実装です。

そのために、「指定された方向の先に Target がいるか判定する」Robot のメンバ関数を実装しました。具体的には「壁にぶつかるまで移動して、途中でどれかの Target の座標と一致したら true を返す」という簡単なものです。

これを提出したのが 60 分頃。しかしビジュアライザを見るとたまに上手く動いていないときがあり、その原因を探っていたらコンテスト終了になりました。

ちなみに以下が最後までバグらせていた箇所です。どこがバグの原因か分かりますか？

```cpp
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
```

答えは 8 行目の `target.x == ny` です。コンテスト後、ここを修正したらちゃんと Target を潰してくれました。

### Beam を避ける

コンテスト中は時間がなかったので、Target の動きは最後まで乱択でした。それでは物足りなかったので、コンテスト後に延長戦として「Beam と同じ行、列になるような箇所に移動しない」という動きも実装しました。

ちゃんと実装できて理想通りの動きをしてくれたのですが、なぜかこれが random に負けるという始末[^random_win]。ゲーム AI って難しいですね。

[^random_win]: 実は Beam を避ける機能を実装する前後で、random に対する勝率が落ちました。おそらく Target の動きが狭まったことが原因でしょう。

ちなみに最終的にクラスの構造は以下のように変わりました。

```cpp
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
```

### やりたかったこと

今回はコードのテスト用に、運営側で「random」「cat」という 2 つの対戦用 AI を用意していただきました。しかしむちゃくちゃ強い cat はおろか、上に述べた通り random にも安定して勝てる AI は作れませんでした。

さらに強くするためにやりたいこととしては、

- 数手掛けて Target を潰すようなムーブを探索する。
- Target を極力スペースが広い、かつ Beam から遠い箇所に逃がす。

などが考えられますが、上手い実装が思い浮かびません。

あるいは機械学習やゲーム理論を学べばもっと強いのが作れるかも知れませんが、当然ながら知識及ばず。なんとかして cat に勝ちたいですね。

## 感想

1 つ言わせてもらうとすれば、75 分は非常に短いです。いっそのこと 1 週間ほど用意して、当日に複数人の AI を戦わせるのもありかもしれません(それはライブプログラミングではありませんが)。少なくとももっとハイレベルな戦いが見れると思います。

それとやはりゲーム AI 実装は難しいです。競プロ以上に複雑な実装もこなせるようになりたいですね。

