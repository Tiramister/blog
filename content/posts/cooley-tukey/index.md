---
title: Cooley-Tukey Algorithm
date: 2021-03-05
tags: [algorithm]
---

$n$ 次多項式 $f(x) = \sum\_{p=0}^{n-1} a\_p x^p$ から、以下で定義される $n$ 次多項式 $\hat{f}$ への写像を **離散 Fourier(フーリエ)変換** という。ここで $\omega\_n$ は $1$ の原始 $n$ 乗根。

$$
\hat{f}(t) = \sum\_{k=0}^{n-1} f(\omega\_n^k) t^k
$$

「多項式」を「係数からなる数列」と解釈すると、長さ $n$ の数列 $\\\{ a\_p \\\}$ から、以下で定義される長さ $n$ の数列 $\\\{ \hat{a}\_k \\\}$への写像とも解釈できる。以降こちらの解釈を用いる。

$$
\hat{a}\_k = f(\omega\_n^k) = \sum\_{p=0}^{n-1} a\_p \omega\_n^{kp}
$$

これは各 $k$ に対して愚直に計算することで $\Theta(n^2)$ の計算量で求められるが、
これをより高速に求めるアルゴリズム全体を指して **高速 Fourier 変換(FFT)** と呼ぶ。

本記事では、その中でも非再帰で実装できて実装も軽い **Cooley-Tukey(クーリー–テューキー)のアルゴリズム** を紹介する。

## 基本方針

以降 $n$ は 2 べきであるとする。

まず $\hat{a}\_k$ を $k$ の偶奇によって場合分けして求める。
実際に $\hat{a}\_{2k}, \hat{a}\_{2k+1}$ を計算してみると以下のようになる。

$$
\begin{aligned}
    \hat{a}\_{2k}
&=  \sum\_{p=0}^{n-1} a\_p \omega\_n^{2kp}
=   \sum\_{p=0}^{n-1} a\_p \omega\_{\frac{n}{2}}^{kp} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1} a\_p
      \omega\_{\frac{n}{2}}^{kp} +
    \sum\_{p=0}^{\frac{n}{2}-1} a\_{p + \frac{n}{2}}
      \omega\_{\frac{n}{2}}^{k(p + \frac{n}{2})} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1} a\_p
      \omega\_{\frac{n}{2}}^{kp} +
    \sum\_{p=0}^{\frac{n}{2}-1} a\_{p + \frac{n}{2}}
      \omega\_{\frac{n}{2}}^{kp} \omega\_{\frac{n}{2}}^{\frac{n}{2}k} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1} (a\_p + a\_{p + \frac{n}{2}})
      \omega\_{\frac{n}{2}}^{kp}
\end{aligned}
$$

$$
\begin{aligned}
    \hat{a}\_{2k+1}
&=  \sum\_{p=0}^{n-1} a\_p \omega\_n^{(2k+1)p}
=   \sum\_{p=0}^{n-1} a\_p \omega\_n^p \omega\_{\frac{n}{2}}^{kp} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1} a\_p \omega\_n^p \omega\_{\frac{n}{2}}^{kp} +
    \sum\_{p=0}^{\frac{n}{2}-1} a\_{p + \frac{n}{2}}
      \omega\_n^{p + \frac{n}{2}} \omega\_{\frac{n}{2}}^{k(p + \frac{n}{2})} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1} a\_p \omega\_n^p \omega\_{\frac{n}{2}}^{kp} +
    \sum\_{p=0}^{\frac{n}{2}-1} a\_{p + \frac{n}{2}}
      \omega\_n^{p} \omega\_n^{\frac{n}{2}} \omega\_{\frac{n}{2}}^{kp} \omega\_n^{\frac{n}{2}k} \\\\
&=  \sum\_{p=0}^{\frac{n}{2}-1}
    \left(
      (a\_p - a\_{p + \frac{n}{2}}) \omega\_n^{p}
    \right)
    \omega\_{\frac{n}{2}}^{kp}
\end{aligned}
$$

まとめると以下の通り。

$$
\begin{aligned}
    \hat{a}\_{2k}
&=  \sum\_{p=0}^{\frac{n}{2}-1}
    \left(
        a\_p + a\_{p + \frac{n}{2}}
    \right)
    \omega\_{\frac{n}{2}}^{kp} \\\\
    \hat{a}\_{2k+1}
&=  \sum\_{p=0}^{\frac{n}{2}-1}
    \left(
      (a\_p - a\_{p + \frac{n}{2}}) \omega\_n^{p}
    \right)
    \omega\_{\frac{n}{2}}^{kp}
\end{aligned}
$$

これらは Fourier 変換の定義と同じ形をしている。実際、

$$
\begin{aligned}
b^0\_p &= a\_p + a\_{p + \frac{n}{2}} \\\\
b^1\_p &= (a\_p - a\_{p + \frac{n}{2}}) \omega\_n^{p}
\end{aligned}
$$

として長さ $\frac{n}{2}$ の数列 $\\\{ b^0 \\\}, \\\{ b^1 \\\}$ を定めれば、これらに再帰的に Fourier 変換を施すことで $\\\{ \hat{a}\_{2k} \\\}, \\\{ \hat{a}\_{2k+1} \\\}$ がそれぞれ得られる。後は偶数番、奇数番の項が交互に並ぶように並び替えれば良い。

このアルゴリズムでは長さ $n$ の数列に対する問題を、長さ $\frac{n}{2}$ の数列に対する問題 2 つに線形時間で帰着している。よって時間計算量は $\Theta(n \log n)$ となる。

### 再帰実装

このアルゴリズムを Python で一部だけ実装すると以下のようになる。現時点ではまだ再帰関数として実装されているので、これを次の節で非再帰関数に変形する。

```py
# 数列, 開始地点, 長さ
def fft(a, s, n):
    # 基底ケース
    if n == 1:
        return
 
    # a[s    : s+n/2] = b0[0: n/2]
    # a[s+n/2: n    ] = b1[0: n/2]
    # となるように変形
    for p in range(0, n // 2):
        l = a[s + p]
        r = a[s + p + n // 2]
        a[s + p] = l + r
        a[s + p + n // 2] = (l - r) * omega(n, p)
 
    # 再帰的にfftを適用
    fft(a, s,          n // 2)
    fft(a, s + n // 2, n // 2)

    # 偶数番、奇数番が交互に並ぶように並び替える
    tmp = [0] * n
    for p in range(0, n // 2):
        tmp[p * 2] = a[s + p]
        tmp[p * 2 + 1] = a[s + p + n // 2]
 
    for p in range(0, n):
        a[s + p] = tmp[p]
```

## 非再帰へ

先程の関数を非再帰にする上でネックとなるのは、「偶数番、奇数番が交互に並ぶように並び替える」という処理である。
この処理さえなくなればこの関数は末尾再帰となる(再帰呼び出し後に戻ってくる必要がなくなる)ので、再帰呼び出しを展開できる。

### index の並び方

そこで「もしこの並び替えを行わない場合、最終的に得られる数列は正しい数列をどのように並び替えたものなのか」を考える。これが分かれば、最後に一気に並び替えることでこの処理を省ける。

まず先のアルゴリズムでは、 $\\\{ \hat{a}\_{2k} \\\}, \\\{ \hat{a}\_{2k+1} \\\}$ を別々に求めている。ここから「前半に偶数番の項、後半に奇数番の項が並ぶ」ということが分かる。つまり index を 2 進数表記したとき、最終的な数列の index の下 1 桁は $0, \cdots, 0, 1, \cdots, 1$ となっている。

そして $0, \cdots, 0$ の部分と $1, \cdots, 1$ の部分に対して再帰的に関数が呼び出される。この呼び出し内で、元々 index が $2k, 2k+1$ だった項は index が $k$ として扱われる、つまり 1 の位が無視される。
したがって先程と同様の理由から、最終的な数列の index の下 2 桁は $00, \cdots, 00, 10, \cdots, 10, 01, \cdots, 01, 11, \cdots, 11$ となっている。

以上の考察を再帰的に適用すると、「**index を 2 進数として 1 の位から見たとき、辞書順となるように並んでいる**」ことが分かる。つまり $i$ を bit 列と見て反転させたものを $rev(i)$ とする[^rev]と、最終的に得られる数列は $\hat{a}\_{rev(0)}, \hat{a}\_{rev(1)}, \cdots, \hat{a}\_{rev(n-1)}$ となっている。

[^rev]: より厳密には、 $n=2^k$ であるとき「 $i$ を長さ $k$ の bit 列と見て反転させたもの」と定義される。つまり $rev$ の定義は $i$ だけでなく $n$ にも依存していることに注意。

具体例として $n=2^3$ のケースでは、得られる数列の index は $0, 4, 2, 6, 1, 5, 3, 7$ となっている(2 進数表記すると $000, 100, 010, 110, 001, 101, 011, 111$ )。

### 末尾再帰実装

これを踏まえて先程の実装を変更すると以下のようになる。これで ufft が末尾再帰となった。

```py
# unordered FFT
# 数列, 開始地点, 長さ
def ufft(a, s, n):
    # 基底ケース
    if n == 1:
        return
 
    # a[s    : s+n/2] = b0[0: n/2]
    # a[s+n/2: n    ] = b1[0: n/2]
    # となるように変形
    for p in range(0, n // 2):
        l = a[s + p]
        r = a[s + p + n // 2]
        a[s + p] = l + r
        a[s + p + n // 2] = (l - r) * omega(n, p * conj)
 
    # 再帰的にfftを適用
    ufft(a, s,          n // 2)
    ufft(a, s + n // 2, n // 2)


# iを長さkのbit列と見たとき、それを反転させたものを返す
def rev(i, k):
    j = 0
    for _ in range(k):
        j = (j << 1) + (i & 1)
        i >>= 1
    return j


# FFT本体
def fft(a):
    n = len(a)

    # n = 2^kなるkを求める
    k = 0
    while (1 << k) < n:
        k += 1

    ufft(a, 0, n)

    # 適切に並び替える
    for i in range(n):
        j = rev(i, k)
        if i < j:
            swap(a[i], a[j])
```

### 非再帰実装

そしてこの ufft を非再帰で実装すると以下のようになる。

```py
# unordered FFT
def ufft(a):
    n = len(a)

    # m: FFTを施したい数列(ブロック)の長さ
    # 長さmのブロックがn/m個ある
    m = n

    while m > 1:
        # ブロックのindex
        for s in range(0, n // m):
            # ブロック内のindex
            for p in range(0, m // 2):
                l = a[s * m + p]
                r = a[s * m + p + m // 2]
                a[s * m + p] = l + r
                a[s * m + p + m // 2] = (l - r) * omega(m, p)

        # 各ブロックを半分に分割
        m //= 2
```

以下、上の実装の解説。

Cooley-Tukey のアルゴリズムは、大枠としては「長さ $n$ の数列の問題を長さ $\frac{n}{2}$ の数列の問題 2 つへ帰着する」という操作を繰り返して問題を解いている。
一番外側のループ `while m > 1:` がこの見方に対応している。つまり `while m > 1:` 内で「各長さ $m$ の数列の問題を、全て長さ $\frac{m}{2}$ の数列の問題 2 つへ帰着する」という処理をして、次のループで各帰着先をまた帰着させるわけである。

次にループ内部について。長さ $m$ の数列(以下ブロック) $\frac{n}{m}$ 個それぞれに対して処理を行いたいので、 $s$ によって「今何番目のブロックを見ているか」を回している。
各ブロックに対する処理は今までの実装と全く同じである。ただし $s$ 番目のブロックの先頭の index は $s \cdot m$ なので、その分をオフセットとして足しておく必要がある。

## 逆 Fourier 変換

これまでのアルゴリズムを遡ることで、逆 Fourier 変換も同様に実装できる。

これまでのアルゴリズムでは、数列に対して以下の更新をしていた。$a\'$が更新後の数列とする。

$$
\begin{aligned}
a\'\_p                 &= a\_p + a\_{p + \frac{n}{2}} \\\\
a\'\_{p + \frac{n}{2}} &= (a\_p - a\_{p + \frac{n}{2}}) \omega\_n^p \\\\
\end{aligned}
$$

逆変換では更新後の値$a\'\_p, a\'\_{p + \frac{n}{2}}$から更新前の値$a\_p, a\_{p + \frac{n}{2}}$を得る必要があるが、上の等式を変形することで以下の更新式が得られる。

$$
\begin{aligned}
a\_p                 &= \frac{1}{2} (a\'\_p + a\'\_{p + \frac{n}{2}} \omega\_n^{-p}) \\\\
a\_{p + \frac{n}{2}} &= \frac{1}{2} (a\'\_p - a\'\_{p + \frac{n}{2}} \omega\_n^{-p}) \\\\
\end{aligned}
$$

係数に $\frac{1}{2}$ がつくが、これは最後にまとめて $\frac{1}{n}$ を掛けることで代替ができる。

なお注意点として、iufft は ufft の逆操作なので、ufft とは異なり並び替えを **先に** 行わなくてはならない。

実装は以下の通り。ufft と iufft の相違点は以下の通り。

- 外側のループが逆順になった
- 更新式が変わった
- 最後に $\frac{1}{n}$ で割る処理が加わった

また fft と異なり、 ifft では iufft を呼び出す前に並び替えを行う。

```py
# unordered Inverse FFT
def uifft(a):
    n = len(a)

    # m: IFFTを施したい数列(ブロック)の長さ
    # 長さmのブロックがn/m個ある
    m = 2

    while m <= n:
        # ブロックのindex
        for s in range(0, n // m):
            # ブロック内のindex
            for p in range(0, m // 2):
                l = a[s * m + p]
                r = a[s * m + p + m // 2] * omega(m, -p)
                a[s * m + p] = l + r
                a[s * m + p + m // 2] = l - r
        m *= 2

    # 係数1/2の影響をまとめて処理
    for i in range(n):
        a[i] /= n

# iを長さkのbit列と見たとき、それを反転させたものを返す
def rev(i, k):
    # 省略

# IFFT本体
def ifft(a):
    n = len(a)

    # n = 2^kなるkを求める
    k = 0
    while (1 << k) < n:
        k += 1
        
    # 適切に並び替える
    for i in range(n):
        j = rev(i, k)
        if i < j:
            swap(a[i], a[j])

    iufft(a, 0, n)
```

