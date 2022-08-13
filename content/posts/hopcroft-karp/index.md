---
title: "Hopcroft-Karp Algorithm"
date: 2021-04-21T13:30:28+09:00
draft: false
---

Hopcroft-Karp algorithm は、二部グラフの最大マッチングを $O(\sqrt{|V|} \cdot (|V| + |E|))$ で求めるアルゴリズムである。

しばらくの間は、二部グラフに限らず一般的なグラフのマッチングについて議論する。

## 用語

- グラフ $G$ とそのマッチング $M$ について、 $M$ に含まれる辺と接続していない頂点を **自由 (free)** であるという。また $M$ に含まれる辺と含まれない辺を交互に通るパスを **交互路 (alternating path)** といい、特に両端が自由な交互路を **増加路 (augmenting path)** という。
- 集合 $S, T$ の **対称差 (symmetric difference)** $S \oplus T$ を、 $S, T$ のうち一方にのみ属する要素の集合とする。すなわち、 $S \oplus T = (S \cup T) \backslash (S \cap T)$ 。

「増加路」という名前は、以下の補題による。

補題 1
: $M$ をマッチング、 $P$ を $M$ の増加路とする。このとき、 $M \oplus P$ は $M$ よりサイズが 1 大きいマッチングとなる。

## 増加路と最大マッチング

補題 1 より、増加路が存在するマッチングは最大マッチングでない。さらに、補題 2 からこの逆も成立する。

補題 2
: マッチング $M$ と最大マッチング $M^\ast$ について、 $F = M \oplus M^\ast$ とする。このとき、 $F$ に含まれる $M$ の増加路の数と、 $|M^\ast| - |M|$ が一致する。

{{< collapse summary="証明" >}}
$M$ と $M^\ast$ はマッチングなので、 $F$ において任意の頂点の次数は 2 以下である。したがって、 $F$ はいくつかのサイクルとパスからなる。また、 $F$ に含まれるサイクルとパスは、 $M$ と $M^\ast$ の辺を交互に通る。

$M^\ast = M \oplus F$ なので、 $F$ の各連結成分と $M$ の対称差を取っていけば、 $M^\ast$ が得られる。そこで、各連結成分と対称差を取ったときに、 $|M|$ がどの程度増えるかを考える。

- サイクルと対称差を取ったとき。サイズは増えない。
- 両端が異なる集合に属するパスと対称差を取ったとき。サイズは増えない。
- 両端が $M^\ast$ に属するパスと対称差を取ったとき。これは $M$ の増加路でもあるので、サイズは 1 増える。
- 両端が $M$ に属するパスは存在しない。存在したと仮定すると、このパスは $M^\ast$ の増加路でもある。よって補題 1 より $M^\ast$ は最大マッチングでないことになり、矛盾する。

よって $|M|$ が変わるのは「両端が $M^\ast$ に属するパス」、すなわち「 $M$ の増加路」と対称差を取ったときのみである。したがって、 $F$ 中の $M$ に対する増加路の数が $|M^\ast| - |M|$ と一致する。
{{< /collapse >}}

以上より、「 $M$ が最大マッチングである」と「 $M$ に増加路が存在しない 」は同値となる。これを利用して最大マッチングを求めるのが、以下のアルゴリズムである。

1. $M := \emptyset$ とする。
2. $M$ の増加路を探す。
3. 増加路が存在すれば、 $M$ を増加路との対称差で更新して 2 に戻る。
4. 増加路が存在しなければ、 $M$ を最大マッチングとして出力する。

## 最短の増加路を使う場合

増加路の中でも、特に最短のものを探すことにする。

最短の増加路と対称差を取っていくことで得られるマッチングの列を、 $(\emptyset =) M_0, M_1, \cdots, M_k$ とする。すなわち、 $0 \leq i \lt k$ について $P_i = M_i \oplus M_{i+1}$ は $M_i$ の最短の増加路であり、 $M_k$ は最大マッチングである。

この $P_0, P_1, \dots, P_{k-1}$ には、以下に示すような性質がある。

補題 3
: $M$ をマッチングとする。 $M$ に対する最短の増加路を $P$ 、 $M \oplus P$ に対する増加路を $P\'$ とする。このとき $|P\'| \geq |P| + 2|P \cap P\'|$ となる。

{{< collapse summary="証明" >}}
$N = M \oplus P \oplus P\'$ とする。このとき $|N| = |M|+2$ なので、 $M \oplus N$ には $M$ の点素な増加路が 2 つ以上存在することが、補題 2 と同様にして示せる。うち 2 つを $P_1, P_2$ とおく。

$P$ の最小性より、 $|P_1|, |P_2| \geq |P|$ である。よって $|P \oplus P\'| = |N \oplus M| \geq |P_1| + |P_2| \geq 2 |P|$ となる。ここで $|P \oplus P\'| = |P| + |P\'| - 2|P \cap P\'|$ を用いると、 $|P\'| \geq |P| + 2|P \cap P\'|$ が示される。
{{< /collapse >}}

補題 3 から、 $|P_i| \leq |P_{i+1}|$ が成り立つ。

補題 4
: 任意の $i \neq j$ について、 $|P_i| = |P_j|$ ならば $P_i, P_j$ は点素である。

{{< collapse summary="証明" >}}
$i \lt j$ かつ $|P_i| = |P_j|$ で、 $P_i \cap P_j \neq \emptyset$ なる $i, j$ が存在すると仮定する。 $i, j$ はそのようなものの中でも、特に極小であるとする。すなわち、任意の $i \lt m \lt j$ について、 $P_i \cap P_m = P_j \cap P_m = \emptyset$ とする。

このとき、 $P_j$ は $M_i \oplus P_i$ の増加路となる。よって補題 1 より $|P_j| \geq |P_i| + 2|P_i \cap P_j|$ が成り立つ。 $|P_i| = |P_j|$ より $|P_i \cap P_j| = 0$ だが、これは $P_i \cap P_j \neq \emptyset$ に矛盾する。よって示された。
{{< /collapse >}}

これらを利用すると、以下のようにアルゴリズムを改良できる。

1. $M := \emptyset$ とする。
2. $M$ に対する最短の増加路の長さを $k$ とする。増加路が存在しなければ、 $M$ を最大マッチングとして出力し、終了する。
3. $\{ P_1, \cdots, P_t \}$ を、互いに点素な長さ $k$ の増加路の集合で、かつ極大なものとする。
4. $M := M \oplus P_1 \oplus \cdots \oplus P_t$ と更新し、2 に戻る。

このアルゴリズムが少ないステップ数で停止する、というのが以下の補題 5 である。

補題 5
: 上のアルゴリズムは、高々 $2 \lceil \sqrt{|V|} \rceil - 1$ ステップで停止する。

{{< collapse summary="証明" >}}
$\lceil \sqrt{|V|} \rceil - 1$ ステップを終えた直後について考える。補題 3,4 より、ステップを経る毎に $k$ は増加していく。よってこの時点において $k \geq \lceil \sqrt{|V|} \rceil$ 、すなわち全ての増加路の長さが $\lceil \sqrt{|V|} \rceil$ 以上となる。

ここで最大マッチングを $M^\ast$ とし、 $F = M \oplus M^\ast$ について考える。まず各増加路の長さは $\lceil \sqrt{|V|} \rceil$ 以上なので、増加路は高々 $\lceil \sqrt{|V|} \rceil$ 本しか存在しない。さらに補題 2 より、 $F$ に含まれる $M$ の増加路の数が $|M^\ast| - |M|$ と一致する。よって $|M^\ast| - |M| \leq \lceil \sqrt{|V|} \rceil$ となる。1 ステップで $|M|$ は少なくとも 1 増えるので、残りステップ数は高々 $\lceil \sqrt{|V|} \rceil$ となる。

以上より、このアルゴリズムは高々 $2 \lceil \sqrt{|V|} \rceil - 1$ ステップで停止することが示された。
{{< /collapse >}}

したがって、 $\{ P_1, \cdots, P_t \}$ を $O(f(|V|, |E|))$ で求められれば、 $O(\sqrt{|V|} \cdot f(|V|, |E|))$ で最大マッチングが求まる。次の節では、二部グラフのケースで $f(|V|, |E|) = |V| + |E|$ を実現する。

## 二部グラフの場合

二部グラフ $G = (U \cup V, E)$ とそのマッチング $M$ について、 $U, V$ 中の自由な頂点の集合を $\bar{U}, \bar{V}$ とする。 $G$ における $\bar{U}$ から $\bar{V}$ への交互路の集合で、点素かつ極大なものを求めればいい。

$\bar{U}$ から $\bar{V}$ への交互路というのは、 $M$ に含まれない辺、 $M$ に含まれる辺、...という順に通るパスである。したがって、以下が成り立つ。

- $U$ から $V$ へ向かうとき、 $M$ に含まれない辺を通る。
- $V$ から $U$ へ向かうとき、 $M$ に含まれる辺を通る。

そこで、 $G$ を以下のように向きづけた有向グラフ $G\'$ を考える。

- $uv \in E \backslash M$ ならば、 $u$ から $v$ へ向きをつける。
- $uv \in M$ ならば、 $v$ から $u$ へ向きをつける。

すると、 $G\'$ におけるパスと $G$ における交互路が一対一に対応する。これで交互路という条件を気にせずによくなった。

$\bar{U}$ から $\bar{V}$ への最短路ということで、 $\bar{U}$ を始点として BFS をする。 $\bar{U}$ からの距離が $i$ である頂点の集合を $L_i$ とし、 $l = \min \\\{i \mid L_i \cap \bar{V} \neq \emptyset \\\}$ とする。つまり $l$ は $\bar{U}$ から $\bar{V}$ への最短距離である。もし $L_i \cap \bar{V} \neq \emptyset$ なる $i$ がなければ、増加路がないということなので終了する。

$G\'$ のうち、 $L_0$ から $L_1$ 、 $L_1$ から $L_2$ 、......、 $L_{l-1}$ から $L_l$ へ伸びているような辺のみからなるグラフを $\hat{G}$ とおく。言い換えると、 $\hat{G}$ は $\bar{U}$ から $\bar{V}$ への最短路で使われうる辺のみからなるグラフである。したがって、 $G\'$ における $\bar{U}$ から $\bar{V}$ への最短路と、 $\hat{G}$ における $\bar{U}$ から $\bar{V}$ へのパスが一対一に対応する。これで最短路という条件も無視できるようになった。

以上より、 $\hat{G}$ における $\bar{U}$ から $\bar{V}$ へのパスの集合で、点素かつ極大なものを求めればいい。

これは単純な DFS により $O(|V| + |E|)$ でできる。「一度見た辺は、使われようが使われまいが二度と見なくていい」というのが肝で、各頂点について「その頂点が増加路に使われたか」と「接続する辺をどこまで見たか」を保持しておけばよい。

## 実装例

やるべきことは単純だが、実装は結構長くなる。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// 頂点数が(nl, nr)、辺集合がesの二部グラフ
// 使われる辺の番号を返す
vector<int> matching(
    int nl, int nr, const vector<pair<int, int>>& es) {
    int m = es.size();

    vector<bool> used(m, false);

    // 左側の頂点を0,1,...,nl-1
    // 右側の頂点をnl,nl+1,...,nl+nr-1と番号付ける
    vector<vector<int>> graph(nl + nr);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = es[i];
        graph[u].push_back(i);
        graph[v + nl].push_back(i);
    }

    // 頂点vから辺iを使ったときの行き先
    // ただし交互でない場合は-1
    auto get = [&](int v, int i) {
        // 左から右へはマッチングにない辺を使う
        // 右から左へはマッチングにある辺を使う
        if ((v < nl) == used[i]) return -1;

        return v ^ es[i].first ^ (es[i].second + nl);
    };

    while (true) {
        // 頂点vが自由か否か
        vector<bool> isfree(nl + nr, false);
        for (int v = 0; v < nl + nr; ++v) {
            isfree[v] = all_of(graph[v].begin(), graph[v].end(),
                               [&](auto i) { return !used[i]; });
        }

        queue<int> que;
        vector<int> ds(nl + nr, -1);

        // 左側の自由な頂点からスタート
        for (int v = 0; v < nl; ++v) {
            if (isfree[v]) {
                que.push(v);
                ds[v] = 0;
            }
        }

        // BFS
        while (!que.empty()) {
            auto v = que.front();
            que.pop();

            for (auto i : graph[v]) {
                // 接続するもう一方の頂点
                auto u = get(v, i);
                if (u != -1 && ds[u] == -1) {
                    ds[u] = ds[v] + 1;
                    que.push(u);
                }
            }
        }

        // 右側の自由な頂点のうち、最短距離の最小値
        int k = -1;
        for (int v = nl; v < nl + nr; ++v) {
            if (!isfree[v] || ds[v] == -1) continue;

            if (k == -1) {
                k = ds[v];
            } else {
                k = min(k, ds[v]);
            }
        }

        // 増加路がなければ終了
        if (k == -1) break;

        vector<bool> visited(nl + nr, false);  // 頂点がマッチングに使われたか
        vector<int> eis(nl + nr, 0);           // 次に見る辺の番号

        // vから増加路が作れればtrue
        auto dfs = [&](auto&& f, int v) -> bool {
            // 右側の自由な頂点でエンド
            if (ds[v] == k && isfree[v]) {
                visited[v] = true;
                return true;
            }

            auto& ei = eis[v];
            while (ei < (int)graph[v].size()) {
                auto i = graph[v][ei++];

                auto u = get(v, i);
                // マッチングに使われておらず、かつ次のレイヤーにあるなら移動
                if (u == -1 || visited[u] ||
                    ds[u] != ds[v] + 1) continue;

                if (f(f, u)) {
                    // 増加路が作れるので、辺iを反転
                    used[i] = !used[i];
                    visited[v] = true;
                    return true;
                }
            }

            // 増加路は作れないので、以降見なくていい
            visited[v] = true;
            return false;
        };

        // 左側の自由な頂点からスタート
        for (int v = 0; v < nl; ++v) {
            if (isfree[v] && !visited[v]) dfs(dfs, v);
        }
    }

    vector<int> ret;
    for (int i = 0; i < m; ++i) {
        if (used[i]) ret.push_back(i);
    }
    return ret;
}
```

verify は [Library Checker](https://judge.yosupo.jp/submission/45401) を利用した。
