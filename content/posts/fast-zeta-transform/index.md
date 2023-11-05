---
title: "高速ゼータ・メビウス変換"
date: 2019-09-01
tags: [algorithm]
---

## ゼータ・メビウス変換とは

$X$ を有限集合とする。このとき写像 $f: 2^X \\to \\R$ から、以下を満たす写像 $g: 2^X \\to \\R$ を求めることを **ゼータ変換** という[^1]。

[^1]: より一般には、 $f, g$ の終域は _結合的_ かつ _可換_ な加法が定義されていればよい。 $\\R$ の他にも、例えば $\\N, \\Z, \\cnums, \\Z/n\\Z$ もこの条件を満たす。

$$
\\forall S \subseteq X, \\; g(S) = \\sum\_\{T \\subseteq S\} f(T)
$$

この記事では、 $\\sum$ の下が $T \\subseteq S$ のものを **下からの** ゼータ変換、 $T \\supseteq S$ のものを **上からの** ゼータ変換と呼ぶことにする。

そしてこの逆変換、すなわち $g: 2^X \\to G$ から以下を満たす $f: 2^X \\to G$ を求めることを **メビウス変換** という[^2]。

[^2]: メビウス変換を適用するには、終域は結合的かつ可換に加えて、 _可逆_ である必要がある。先に挙げた $\\N, \\Z, \\cnums, \\Z/n\\Z$ の中では、 $\\N$ は満たさないが、他 3 つは満たす。

$$
\\forall S \subseteq X, \\; f(S) = \\sum\_\{T \\subseteq S\} (-1)\^\{|T| - |S|\}g(T)
$$

ゼータ変換同様、 $\\sum$ の下が $T \\subseteq S$ のものを **下からの** メビウス変換、 $T \\supseteq S$ のものを **上からの** メビウス変換と呼ぶことにする。

「逆変換」と述べた通り、下からの (resp. 上からの) メビウス変換は、下からの (resp. 上からの) ゼータ変換の逆変換となっている。
この事実は非自明だが、この記事ではその証明は省略する[^5]。

[^5]: [指数時間アルゴリズム入門](https://www.slideshare.net/wata_orz/ss-12131479) の 53 ページに式変形が載っている。 $f$ と $g$ が逆になっているので注意。

以降 $X = \\\{ 1, 2, \\cdots, n \\\}$ のみを考え、関数 $f$ を長さ $2\^n$ の配列として表現する。これと対応して、以降 $f(\\\{ 2, 4, 5 \\\})$ を $f(11010)$ のように表現する。

## ゼータ変換の高速化

ここから下からのゼータ変換、すなわち全ての $S \subseteq X$ について $g(S) = \\sum\_\{T \\subseteq S\} f(T)$ を高速に求めることを考える。

### 愚直解

まず愚直に求めようとすると、以下のようなコードになるだろう。

```cpp
for (int s = 0; s < (1 << n); ++s) {
    for (int t = 0; t < (1 << n); ++t) {
        if ((s & t) == t) g[s] += f[t];
    }
}
```
$S$ と $T$ は $X$ の部分集合全体を回り、 $S \\cap T = T$ 、すなわち $T \\subseteq S$ のときだけ $g(S)$ に $f(T)$ を加算する。
$X$ の部分集合は計 $2\^n$ 個あることから、このコードの計算量は $2\^n \\cdot 2\^n = 4\^n$ となる。

### 部分集合の列挙

しかしこのコードでは $T$ の探索に無駄が多すぎる。できることなら $X$ ではなく $S$ の部分集合全体だけを回したいが、実はこれは以下のコードで実現できる。

```cpp
for (int s = 0; s < (1 << n); ++s) {
    // s の部分集合のみを全探索
    for (int t = s; t >= 0; t = ((t - 1) & s)) {
        g[s] += f[t];
    }
}
```

この手法は [ビット演算 (bit 演算) の使い方を総特集！ 〜 マスクビットから bit DP まで 〜](https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#与えられた部分集合の部分集合を列挙) に載っている。
$S$ の部分集合は $2\^\{|S|\}$ 個あり、 $X$ のサイズ $k$ の部分集合は $\\binom\{n\}\{k\}$ 個あることから、このコードの計算量は $\\sum\_\{k = 0\}\^\{n\} \\binom\{n\}\{k\} \\cdot 2\^k = (1 + 2)\^n = 3\^n$ となる。

### 高速ゼータ変換

さらに高速化して、 $n \\cdot 2\^n$ の計算量でゼータ変換を行うのが本記事の主題である **高速ゼータ変換** と呼ばれる手法である。
方針は「下位要素から順に拡張していく」というもの。

$S \subseteq X$ と $k = 0, 1, \dots, n$ について、 $dp\_\{S, k\}$ を「 $1 \\sim k$ は $S$ の部分集合、それより上は $S$ と一致している集合における、 $f$ の総和」と定義する。言葉では分かりにくいので例を挙げると、

$$
dp\_\{\\textcolor\{pink\}\{110\}\\textcolor\{skyblue\}\{101\}, 3\} =
f(\\textcolor\{pink\}\{110\}\\textcolor\{skyblue\}\{000\}) +
f(\\textcolor\{pink\}\{110\}\\textcolor\{skyblue\}\{001\}) +
f(\\textcolor\{pink\}\{110\}\\textcolor\{skyblue\}\{100\}) +
f(\\textcolor\{pink\}\{110\}\\textcolor\{skyblue\}\{101\})
$$

といった具合である。定義より、 $dp\_\{S, 0\} = f(S)$ 、 $dp\_\{S, n\} = g(S)$ 。

これを $k = 1$ から $k = n$ まで順に更新していく。このとき、 $k \\in S$ か否かで場合分けをする。具体例で考えてみると、

$$
\\begin\{alignat\}\{2\}
dp\_\{\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{10\}, 3\} &=
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{00\}) +
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{10\}) &&=
dp\_\{\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{10\}, 2\} \\\\
dp\_\{\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{1\}\\textcolor\{skyblue\}\{10\}, 3\} &=
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{00\}) +
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{10\}) &+
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{1\}\\textcolor\{skyblue\}\{00\}) +
f(\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{1\}\\textcolor\{skyblue\}\{10\}) &=
dp\_\{\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{0\}\\textcolor\{skyblue\}\{10\}, 2\} +
dp\_\{\\textcolor\{pink\}\{10\}\\textcolor\{lightgreen\}\{1\}\\textcolor\{skyblue\}\{10\}, 2\}
\\end\{alignat\}
$$

のように、 $k \\in S$ の場合は $dp\_\{S \\backslash \\\{ k \\\}, k - 1\}$ も足す必要がある。

これを実装に落とし込むと以下の通り。

```cpp
for (int s = 0; s < (1 << n); ++s) {
    dp[s][0] = f[s];
}

for (int k = 1; k <= n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        dp[s][k] = dp[s][k - 1];
        if ((s >> (k - 1)) & 1) {
            dp[s][k] += dp[s ^ (1 << (k - 1))][k - 1];
        }
    }
}

for (int s = 0; s < (1 << n); ++s) {
    g[s] = dp[s][n];
}
```

集合及び DP の添字は 1-indexed なのに対して bit 演算は 0-indexed なので、シフト数を 1 減らしてやる必要がある。

#### 配列の使い回し

さらに更新について考えてみると、DP テーブルは 1 次元のものを使い回せることに気づく。すなわち、以下のような実装ができる。

```cpp
for (int s = 0; s < (1 << n); ++s) {
    dp[s] = f[s];
}

for (int k = 1; k <= n; ++k) {
    // この時点でdp[s]は上の実装のdp[s][k-1]と一致
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> (k - 1)) & 1) {
            dp[s] += dp[s ^ (1 << (k - 1))];
        }
    }
}

for (int s = 0; s < (1 << n); ++s) {
    g[s] = dp[s];
}
```

ここで「 $dp\_\{S \\backslash \\\{ k \\\}\}$ は $dp\_\{S\}$ より先に更新されているが大丈夫なのか」となるが、 $k \\not \\in S \\backslash \\\{ k \\\}$ なので、この週ではそもそも $dp\_\{S \\backslash \\\{ k \\\}\}$ は更新されていない。

さらに $k$ を 1 ずらしたり DP 配列として直に $g$ を使ったりして整理することで、他の記事でもよく見られるような実装になる。

```cpp
for (int s = 0; s < (1 << n); ++s) {
    g[s] = f[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> k) & 1) {
            g[s] += g[s ^ (1 << k)];
        }
    }
}
```

長い道のりだったが、ようやく高速ゼータ変換のコードに辿り着いた。計算量は見ての通り $n \cdot 2^n$ 。

## 高速ゼータ・メビウス変換の実装例まとめ

最後にまとめとして、各種変換の実装例を載せておく。
なお配列 $f, g$ はコード外で宣言済みとする。

### 下からの高速ゼータ変換

$$
g(S) = \\sum\_\{T \\subseteq S\} f(T)
$$

```cpp
for (int s = 0; s < (1 << n); ++s) {
    g[s] = f[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if (!((s >> k) & 1)) {
            g[s] += g[s ^ (1 << k)];
        }
    }
}
```

先程解説したように、 $k \\in S$ のときに $dp\_\{S\} \\mathrel\{+\}= dp\_\{S \\setminus \\\{ k \\\}\}$ と更新する。

### 上からの高速ゼータ変換

$$
g(S) = \\sum\_\{T \\supseteq S\} f(T)
$$

```cpp
for (int s = 0; s < (1 << n); ++s) {
    g[s] = f[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> k) & 1) {
            g[s] += g[s ^ (1 << k)];
        }
    }
}
```

下からのときとは逆に、 $k \\notin S$ のときに $dp\_\{S\} \\mathrel\{+\}= dp\_\{S \\cup \\\{ k \\\}\}$ と更新する。

### 下からの高速メビウス変換

$$
f(S) = \\sum\_\{T \\subseteq S\} (-1)\^\{|S| - |T|\} g(T)
$$

```cpp
for (int s = 0; s < (1 << n); ++s) {
    f[s] = g[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if (!((s >> k) & 1)) {
            f[s] -= f[s ^ (1 << k)];
        }
    }
}
```

非自明だが、実はゼータ変換の更新の符号を反転させるだけでいい。 $g(T)$ が $f(S)$ に足されるまでに符号が $|S| - |T|$ 回反転される、というお気持ち。

### 上からの高速メビウス変換

$$
f(S) = \\sum\_\{T \\supseteq S\} (-1)\^\{|T| - |S|\} g(T)
$$

```cpp
for (int s = 0; s < (1 << n); ++s) {
    f[s] = g[s];
}

for (int k = 0; k < n; ++k) {
    for (int s = 0; s < (1 << n); ++s) {
        if ((s >> k) & 1) {
            f[s] -= f[s ^ (1 << k)];
        }
    }
}
```

下からのメビウス変換と同じく、上からのゼータ変換の符号を反転させるだけでいい。

