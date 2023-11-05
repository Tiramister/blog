---
title: Mister の JAG 夏合宿 2019 参加記
date: 2019-09-17
tags: [icpc]
links:
  - label: Day1
    url: 
  - label: Day2
    url: 
  - label: Day3
    url: 
---

The atama 3 人で JAG(ACM-ICPC OB/OG の会)が主催する夏合宿に参加してきました。

## Day 1

### The atama の集合は早い

初日は集合場所がオリンピックセンター(以降オリセン)だったので、万全を期して The atama は一旦合流してから行くことに。
結果全員が時間通りに集合して、11:00 にオリセンに着いた。全員揃った時刻では FA だった気がする。

{{<raw>}}

<blockquote class="twitter-tweet">
  <p lang="ja" dir="ltr">The atama入場です</p>
  &mdash; Mister (@mistterpp)
  <a href="https://twitter.com/mistterpp/status/1172692833678921728?ref_src=twsrc%5Etfw">September 14, 2019</a>
</blockquote>

{{</raw>}}

### Day1 の貢献は少ない

その後人がぞろぞろと会場入りして、Day1 のコンテストが始まった。

[Aizu Online Judge Arena](https://onlinejudge.u-aizu.ac.jp/services/room.html#JAGSummerCamp19Day1)

- いつも通り A 問題をさかな、B 問題をおくら、C 問題を僕が読む
- B 問題をおくらが実装 → {{<color lightgreen>}}AC{{</color>}}
- A 問題をさかなが実装 → {{<color lightgreen>}}AC{{</color>}}
- C 問題の考察が終わる
  - セグ木が要るので慣れているに実装を投げる → {{<color lightgreen>}}AC{{</color>}}
- D 問題に考察を集中
  - サイクルに分解して中国剰余定理を使えば解けるね
  - 似た問題を見たことがあるということでさかなが実装 → {{<color lightgreen>}}AC{{</color>}}
- J が解かれているので考察する
  - 最大マッチングと連結成分じゃん
  - ライブラリ担当？のおくらが実装 → {{<color lightgreen>}}AC{{</color>}}
- 実装中に僕が E 問題を考察
  - 積を距離としたとき BFS とかで矛盾を調べれば解ける
  - 素因数分解とか考えたが、計算量が削れない
- さかなとおくらが H 問題を考察
  - 「どの行にあるかは分かる」というところまでは来た
  - しかしそこから先が詰められず
- 少し解かれている G 問題とかを考えたが微塵も分からない
- 再び E 問題に考察を集中
  - とりあえず対数でおくらが実装 → {{<color orange>}}WA{{</color>}}
  - さかな「ハッシュ的な方法でなんとかならない？」→ MOD を取るも {{<color orange>}}WA{{</color>}}
  - 非連結なケースで死ぬことに気づき修正 → {{<color lightgreen>}}AC{{</color>}}
    - ちなみにコンテスト後に対数のを修正して投げたが通らなかった
- K 問題が畳み込みで解けることに気づく
  - 僕「誰か FFT 持ってますか？」さかな「いいえ」おくら「いいえ」　おしまい
  - 僕がうろ覚えで実装を試みるも、できるはずもなく終了

結果 ABCDEJ の 15 位(オンサイトは多分 10 位)。以下反省点。

- 僕が実装をしなかった
- 全員が全問題を読むべきだった
- FFT くらい用意しておくべきだった
- E の考察に時間がかかりすぎた

振り返ると ABCDEJ を 2:30 くらいで片付けて、せめて K 問題までは通したかったという印象。おくらが Li-Chao 木を持っていたので I 問題もワンチャンあったかもしれない。

何にせよ実力不足、特に速度不足を痛感する結果となった。

### 314 の夜は長い

コンテスト後は夕飯を除いてほとんど自由時間。談話室でボドゲに混ざらせていただいたりした。

なお僕が割り振られた 314 号室は Twitter でよく見る顔ぶれで、さらに何人か訪問者が来て結局 2:00 まで起きていた。ワイワイできてとても楽しかった。

## Day2

### 夏合宿の朝食は遠い

7:00 - 9:00 が朝食の時間なのだが、宿泊者が数百人いるのに食堂が 1 つしかないので非常に混む。というわけで早起きして 6:55 に食堂に着いたのだが、それでも結局 10 分待たされた。

ちなみに Day3 はそれを踏まえて 6:45 に向かったところ、並んではいたが 1 回目の波で入ることができた。

{{<raw>}}

<blockquote class="twitter-tweet">
  <p lang="ja" dir="ltr">
    夏合宿の芋は旨い？(要検証)
    <a href="https://t.co/AmXhh0eMuO">pic.twitter.com/AmXhh0eMuO</a>
  </p>
  &mdash; Mister (@mistterpp)
  <a href="https://twitter.com/mistterpp/status/1173357768574529537"
    >September 15, 2019</a
  >
</blockquote>

{{</raw>}}

### Day2 の精進は足りない

その後しばらく部屋で寝て、Day2 のコンテストが始まった。

[Aizu Online Judge Arena](https://onlinejudge.u-aizu.ac.jp/services/room.html#JAGSummerCamp19Day2)

- 難易度順がランダムということで、FA 狙いで各位バラバラに問題を読むことに
- 僕が E 問題から読み始める
  - 面倒そうな式だな → いやギャグやんけこれ → {{<color lightgreen>}}AC{{</color>}}
  - 5 分 {{<color lightgreen>}}AC{{</color>}} で全体 2 位だったが、FA とは 2 分差だった
- J 問題がいけそうになったので僕が実装
  - サンプルで嘘であることに気がついて悲しくなる
- さかなとおくらが A 問題を考察
  - さかなが実装 → {{<color lightgreen>}}AC{{</color>}}
- 僕が D 問題、S が J 問題、O が I 問題を考察
- D 問題の解法が分かるも、計算量がヤバい
  - しばらく考えていたが、計算量の見積もりミスに気づく
  - 僕が実装 → {{<color lightgreen>}}AC{{</color>}}
- I 問題の考察が終わる
  - おくらに実装をしてもらう
  - 大きいケースは良いが、小さいケースのシミュレートが大変
  - ジャッジがバグっているという情報が入るが、とりあえず投げておく
- さかなが J 問題の解となる式を導出する
  - しかしこれの計算量がどうしても減らせない
  - 見積もり的にコンテスト中には間に合わないが、とりあえず埋め込みを走らせる
- 他の問題も何も分からず、時間だけが過ぎていく
- I 問題のリジャッジが行われるも {{<color orange>}}WA{{</color>}}
  - コードを印刷するも何もミスは見当たらない
  - 大きいケースを走らせると、`inf` という出力が出る
  - `pow()` 関数が名前衝突を起こしていることが発覚 → {{<color lightgreen>}}AC{{</color>}}
    - 3 人のコーディングスタイルの違いが災いの元だった
- 終了数分前に F 問題が一般マッチングに帰着できることに気づいて終了

結果 ADEI の 20 位(オンサイトで多分 13 位)。I 問題のジャッジがバグってなければもっと上だったと思うが、それにしても悲しい結果だった。

反省点は「コーディングスタイルの違いがバラバラだった」くらいで、他の問題は現状どうしようもないという感覚が強い。シンプルに実力不足を痛感した。

### 懇親会の飯は多い

コンテスト後諸々を経て、19:00 から懇親会が始まった。

とはいえ根本的にコミュ障なので、あまり人脈が広げられず悲しかった。それでも初めて話した人もいて楽しかった。

あと飯が競プロ関係のものが多かった。以下は哀愁漂うカツサンドくん。

{{<raw>}}

<blockquote class="twitter-tweet">
  <p lang="ja" dir="ltr">
    カツがN枚とパンがM枚あります。<br />カツサンドを最大いくつ作れるか求めて下さい。
    <a href="https://twitter.com/hashtag/JAGSummerCamp2019?src=hash&amp;">#JAGSummerCamp2019</a>
    <a href="https://t.co/DFFLUVs1IG">pic.twitter.com/DFFLUVs1IG</a>
  </p>
  &mdash; Mister (@mistterpp)
  <a href="https://twitter.com/mistterpp/status/1173182007473360896">September 15, 2019</a>
</blockquote>

{{</raw>}}

懇親会後、風呂から部屋に戻るとこたつがめくんが ABC のコードゴルフをしていた。僕は ABC に参加する予定はなかったので観戦していたが、AtCoder のコーディングエリアにコードをベタ書きする様は見ていて圧巻だった。コンテスト全体でもちゃんと全完していて凄いなぁとなった。

ちなみにこの日の夜もなんやかんや 1:30 まで起きていた。人はなぜ。

## Day3

### Day3 の嘘は怖い

部屋でダラダラしていたらチェックアウトがビリになっていた。全員とっくに出る準備はできていたんです。

それはさておき Day3 のコンテストが始まった。

[Aizu Online Judge Arena](https://onlinejudge.u-aizu.ac.jp/services/room.html#JAGSummerCamp19Day3)

- やや変則的だがさかながテンプレを書きつつ僕が A 問題を考察することに
  - 解けたので解法をさかなに伝える → {{<color lightgreen>}}AC{{</color>}}
- 実装中に僕が B 問題を考察する
  - 順番は前後しないから二分探索だなとなる
  - 「**greater** or equal to」の「or equal to」を見逃して 1 {{<color orange>}}WA{{</color>}} → {{<color lightgreen>}}AC{{</color>}}
- 諸事情で PC が使えない時間があり、B 問題の実装待ち中にさかなと C 問題を考察する
  - 往復回数は区間グラフの彩色問題で、これは離散数学演習でやったため解ける
  - 最後の週が面倒だが、それを詰め切る前に PC が使えるようになって後は任せる
  - 詰め切れたらしくおくらが実装 → {{<color lightgreen>}}AC{{</color>}}
- D 問題が構築なので The atama の atama ことさかなが取り組む
  - $X = 0$ と $A \^ O = X$ が無理ということが分かる
  - $X$ の bit が全部 $1$ の場合に構築ができる
  - 他の場合も帰着できるかと思ったができなくて終了
- E 問題は見た感じフローっぽいのでグラフを考える
  - 流量下限を課すことでグラフが完成する(嘘)
  - 僕が最小費用流を実装をする間おくらにグラフの構築を頼む
  - 実装が終わるもなんか上手くいかない
  - どうすれば直るのかよく分からないままコンテストが終わった
- 後で聞いた話だが、終盤さかなは J 問題(これも構築)を考察していた
  - $N$ が奇数の場合が無理であることは分かっていた
  - $N$ が偶数の場合、$N$ 頂点の完全グラフを完全マッチングに分解できれば解けていた
  - コンテスト後に調べたら構築方法が出てきた。

{{<raw>}}

<blockquote class="twitter-tweet">
  <p lang="ja" dir="ltr">
    偶数頂点の完全グラフを完全マッチングに分解する(1-factorizationする)方法を知って感動した
  </p>
  &mdash; Mister (@mistterpp)
  <a href="https://twitter.com/mistterpp/status/1173474970439057409">September 16, 2019</a>
</blockquote>

{{</raw>}}

結局 ABC の 20 位(オンサイトで多分 12 位)。コンテスト後無力感に包まれていた。
なお他の問題もちゃんと読んでいて、合間合間で考察をしていたが全く分からなかった。

コンテスト後に heno くんに E 問題のフローが嘘であることを指摘してもらった。
そして D 問題はアドホック構築ではなく 2-SAT が想定解だった。我々の 3 時間は一体......。

### 万豚記の閉店は早い

そんなこんなで 3 日間に渡る合宿は終わりを告げた。
JAG の皆さん、writer 陣の皆さん、本当にありがとうございました。
正直なところ、夏休みの頭にやってほしかった。

ちなみに合宿中に何度か「近くにある万豚記という店の炒飯が旨い」とおくらに熱弁されていたので、帰りに The atama で寄ることにした。

{{<raw>}}

<blockquote class="twitter-tweet">
  <p lang="ja" dir="ltr">
    泣いてしまった <a href="https://twitter.com/hashtag/JAGSummerCamp2019?src=hash&amp;">#JAGSummerCamp2019</a>
    <a href="https://t.co/fLmfLHPiyt">pic.twitter.com/fLmfLHPiyt</a>
  </p>
  &mdash; Mister (@mistterpp)
  <a href="https://twitter.com/mistterpp/status/1173494126458757121">September 16, 2019</a>
</blockquote>

{{</raw>}}

