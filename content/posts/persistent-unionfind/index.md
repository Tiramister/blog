---
title: "部分永続 UnionFind の実装"
date: 2018-09-13
tags: [algorithm]
---

## 初めに

この記事では部分永続 UnionFind の **実装** を解説するものであり、踏み込んだ原理の解説はしません。あくまでも「どうやって実装するのか？」という部分に重点を置いた記事になります。

しかしこの記事を読むにはまず部分永続 UnionFind の原理がある程度理解できていないと厳しいと思われます。というよりほぼ読めません。ということで、私が参考にしたサイトを以下に記しておきます。

- [noshi さんの記事](http://noshi91.hatenablog.com/entry/2018/02/18/161529)
- [camypaper さんの記事](https://camypaper.bitbucket.io/2016/12/18/adc2016/)

## 部分永続 UnionFind とは？

そもそも部分永続 UnionFind とは、UnionFind から多少の計算量を犠牲にして以下のクエリに対応できるようにしたものです。

- $u$ を含む集合と、 $v$ を含む集合をマージする。 **このとき時刻が 1 進む** 。
- **時刻 t において** 、$u, v$ が同じ集合に属していたかを調べる。
- **時刻 t において** $v$ が属していた集合のサイズを求める。

簡単に言えば、 **過去の状態も保持した** UnionFind です。それでいて計算量も空間量も UnionFind と大差ありません。

ただし 1 つ大きく UnionFind に劣る点として、その性質上 **経路圧縮が行えない** ことが挙げられます。これにより、探索のならし計算量は $O(\\alpha(N))$ から $O(\\log N)$ に落ちます。

## 実装

基本的には UnionFind に手を加えるだけでできるので、今回は以下の私のライブラリをイジることにします。

```cpp
// 頂点数
const int V_NUM = 100000;

class UnionFind {
public:
    int par[V_NUM];  // 各頂点の親
    int rank[V_NUM]; // その頂点を根とする木の深さ
    int num[V_NUM];  // その頂点を根とする木の頂点数

    explicit UnionFind() {
        for (int i = 0; i < V_NUM; ++i) {
            par[i] = i;
        }
        fill(rank, rank + V_NUM, 0);
        fill(num, num + V_NUM, 1);
    }

    // xの親を返す + 経路圧縮
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            return par[x] = find(par[x]);
        }
    }

    // xとyが同じ木に属するか判定
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // xとyを含む木を結合する
    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        num[x] += num[y];
        if (rank[x] == rank[y]) rank[x]++;
    }

    // xを含む木の頂点数を返す
    int size(int x) {
        return num[find(x)];
    }
};
```

### メンバ変数

まず、部分永続 UnionFind ではメンバ変数が 2 つ増えます。

- `now`:現在時刻
- `time`: 各頂点 $x$ について、 $x$ の直接の親(つまり `par[x]` )がいつ更新されたか

通常の UnionFind では経路圧縮があるので、結合後も直接の親は変わり得ます。
一方で部分永続 UnionFind は経路圧縮を捨てているので、「 **一度結合されたら、直接の親はずっと変わらない** 」という性質を持ちます。
したがって、時刻 `time[x]` 以外で `par[x]` に変更がなされていないことが保障できます。

加えて、既存のメンバ変数である `num` の仕様が変わります。
今の `num` は現在の頂点数しか持ちませんが、これを「時刻」と「その時点での頂点数」の pair の配列に変えます。
この変更により、各時刻での要素数を求められるようになります。詳しくは後半の章にて。

以上をまとめると、メンバ変数とコンストラクタが以下のように変わります。

```cpp
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
```

### find 関数

次に find 関数です。 find 関数は頂点 `x` だけでなく、調べたい時刻 `t` を引数に取ります。
ここで、 `t` と `time[x]` の大小によって場合分けをします。

- `t < time[x]` の場合。  
  `time` の定義から、「 `par[x]` は時刻 `t` にてまだ更新されていない」、つまり「時刻 `t` にて `x` は木の根である」ことが分かります。よって `x` をそのまま返せばいいです。

- `t >= time[x]` の場合。  
  この場合、「 `par[x]` は時刻 `t` にてすでに更新されている」ため、通常の UnionFind 同様、親について再帰的に探索すればいいです。

以上で全パターンを網羅できました。というわけで find 関数と、ついでに same 関数も書き換えましょう。

```cpp
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
```

### unite 関数

こちらはただ `now` と `time` の更新が入るだけです。

ただし重要な点を 1 つ。部分永続 UnionFind では経路圧縮を行わないため、rank によってバランスを保たなければ偏った入力のときに計算量が $O(N)$ になってしまいます。
UnionFind を rank なしで実装した方も、今回はちゃんと rank つきで実装しなければなりません。

```cpp
    // 頂点xとyを繋げる
    void unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // yの親がxに更新されたので、timeに時刻を記録
        if (rank[x] == rank[y]) ++rank[x];
    }
```

上の実装では、まだ `num` の更新は省いてあります。
部分永続 UnionFind に変更する上で一番処理が面倒なのが `num` の扱いなので、これの更新は次章にて追加します。

なお、「各集合の要素数までは要らない」という方は以上で実装終了なので、次の章は丸々飛ばしていただいて構いません。お疲れ様でした。

### size 関数

size 関数の説明に入る前に、メンバ変数 `num` の更新を実装します。

2 つの木を結合したとき、その 2 つの木の頂点全てに対して(時刻, サイズ)の pair を突っ込んでいては、計算量的にアウトです。
そのため、 `num` を更新するのは「新しくできた木の根」のみとなります。

これに基づいて、 unite 関数に `num` の更新を加えます。
コメントにある通り、 `num` の更新位置には気をつけましょう[^num_update]。

```cpp
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
```

[^num_update]: `num[x].push_back(make_pair(now, size(x, now - 1) + size(y, now - 1)))` のように丁寧に処理すれば、更新位置はどこでも問題ありません。`

さて、本題の size 関数です。先程説明した通り、 `num` が更新されるのは木の根に対してのみなので、まずは find 関数で木の根に行く必要があります。

`num` の中には(時刻, 要素数)の pair が格納されているわけですが、この中には時刻が古すぎるものもあれば、逆に「知りたい時刻」より未来の情報もあります。
その中で適切な情報はどれかというと、「知りたい時刻」と同時刻か、あるいはそれより古い中で最も新しいものです。
`num` は時刻について昇順に格納されているため、これは二分探索によって高速に調べることができます。

というわけで、 size 関数は以下のようになります。

```cpp
    // 時刻tにおいて、頂点xを含む木の要素数を求める
    int size(int x, int t) {
        x = find(x, t);

        // 適切な情報が入ったindexを二分探索で探り当てる
        int ok = 0, ng = num[x].size();
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (num[x][mid].first <= t) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        return num[x][ok].second;
    }
```

以上で全体の実装が完了です。お疲れ様でした。

## 全体の実装例

ここまで実装してきたものをまとめると、以下のようになります。

```cpp
const int INF = 1 << 25;

// 頂点数
const int V_NUM = 100000;

class persistentUF {
public:
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

    // 頂点xとyを繋げる
    int unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return now;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // parの更新を先にやるとバグるので注意
        num[x].push_back(make_pair(now, size(x, now) + size(y, now)));

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // timeに時刻を記録
        if (rank[x] == rank[y]) ++rank[x];
    }

    // 時刻tにおいて、頂点xを含む木の要素数を返す
    int size(int x, int t) {
        x = find(x, t);

        // 適切な情報が入ったindexを二分探索で探り当てる
        int ok = 0, ng = num[x].size();
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if (num[x][mid].first <= t) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        return num[x][ok].second;
    }
};
```

とある問題に試しに投げたら無事通ったので、バグはないはずです。

ついでに要素数を省いたものも貼っておきます。

```cpp
const int INF = 1 << 25;

// 頂点数
const int V_NUM = 100000;

class persistentUF {
public:
    int now;         // 現在時刻
    int par[V_NUM];  // 各頂点の親
    int rank[V_NUM]; // その頂点を根とする木の深さ
    int time[V_NUM]; // 親がいつ更新されたか

    explicit persistentUF() {
        now = 0;
        for (int i = 0; i < V_NUM; ++i) {
            par[i] = i;
        }
        fill(rank, rank + V_NUM, 0);
        fill(time, time + V_NUM, INF); // 自身が根の間は便宜上INFとする
    }

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

    // 頂点xとyを繋げる
    // 繋げた直後の時刻を返す
    int unite(int x, int y) {
        ++now; // 時間を進める

        x = find(x, now);
        y = find(y, now);

        if (x == y) return now;

        // rank[x] >= rank[y]にする
        if (rank[x] < rank[y]) swap(x, y);

        // rankの大きい方、つまりxにyをくっつける
        par[y] = x;
        time[y] = now; // timeに時刻を記録
        if (rank[x] == rank[y]) ++rank[x];

        return now;
    }
};
```

やはり幾分スッキリしますね。なおこちらはテストしてませんが、不要な部分を切り取っただけなので多分問題はないでしょう。

