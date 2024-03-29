---
title: "AtCoder Grand Contest 003 D - Anticube"
date: 2019-02-11
tags: [atcoder]
---

[D - Anticube](https://atcoder.jp/contests/agc003/tasks/agc003_d)

## 概要

紙に $N$ 個の整数 $s\_1, s\_2, \dots, s\_N$ が書かれている。
これから以下の条件を満たすように、いくつかの整数に丸をつける。

- $i \\neq j$ かつ $s\_i$ と $s\_j$ 両方に丸がつけられているならば、 $s\_i \cdot s\_j$ は立方数でない。

最大でいくつの整数に丸をつけられるか求めよ。

### 制約

- $1 \\leq N \\leq 10\^5$
- $1 \\leq s\_i \\leq 10\^\{10\}$

## 考察

積が立方数であるか否かだけが重要なので、素因数分解したときの指数を 3 で割った余りに置き換えても問題ない。
そこで、整数の **標準形** を以下のように定義する。

{{<framed>}}
**標準形**
: 整数 $n$ を素因数分解したものを $p\_1\^\{e\_1\} \\cdot p\_2\^\{e\_2\} \\cdot \\cdots \\cdot p\_k\^\{e\_k\}$ とする。  
このとき、 $p\_1\^\{e\_1 \\bmod\{3\}\} \\cdot p\_2\^\{e\_2 \\bmod\{3\}\} \\cdot \\cdots \\cdot p\_k\^\{e\_k \\bmod\{3\}\}$ を $n$ の **標準形** と定める。

例えば $2160 = 2\^4 \\cdot 3\^3 \\cdot 5\^1$ の標準形は $2\^1 \\cdot 3\^0 \\cdot 5\^1 = 10$ である。
{{</framed>}}

以降、 $s\_i$ は全て標準形とする。

$x, y$ が標準形であるとき、$xy$ が立方数となるのは $y$ が $x$ の **補数** である場合に限られる。

{{<framed>}}
**補数**
: 整数 $n = p\_1\^\{e\_1\} \\cdot p\_2\^\{e\_2\} \\cdot \\cdots \\cdot p\_k\^\{e\_k\}$ は標準形とする。すなわち任意の $i$ について $e\_i = 1, 2$ である。
このとき、 $p\_1\^\{3 - e\_1\} \\cdot p\_2\^\{3 - e\_2\} \\cdot \\cdots \\cdot p\_k\^\{3 - e\_k\}$ を $n$ の **補数** と定める。  
定義から、 $n$ の補数も標準形となる。

例えば $50 = 2\^1 \\cdot 5\^2$ の補数は $2\^2 \\cdot 5\^1 = 20$ である。また $1$ の補数は $1$ である。
{{</framed>}}

標準形の整数とその補数をペアにしたとき、これらのうち一方しか丸をつけることができない。
よって標準形が同じものをグループにし、ペアのうち要素数が多いグループを貪欲に選べばそれが最適解となる。

ただし標準形が $1$ のグループだけは例外で、ここからは 1 つだけ選ぶことができる。

### 高速化

しかし、これを愚直に実装すると間に合わない。
素因数分解の計算量が $O(\\sqrt\{s\_i\})$ であることから、全体の計算量は $O(N \\sqrt\{s\_i\})$ になってしまうからだ。そこで何らかの高速化をする必要がある。

まず標準化だが、「立方数で割る」という方針にすることで高速化できる。
前計算で、素数の立方であり、 $10\^\{10\}$ 以下であるものを列挙する。そのような立方数は $325$ 個ある。
後はこの立方数で割れるだけ割ることで、標準形が求まる。

あとは補数を高速に求める必要があるのだが、この方法が思いつかなかった。予め $10\^5$ 以下の素数を列挙したものをダメ元で出してみたら、なんか間に合った。

## 実装例

[提出 #4228704 - AtCoder Grand Contest 003](https://atcoder.jp/contests/agc003/submissions/4228704)

```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;

template <typename T, typename U>
T mypow(T b, U n) {
    if (n == 0) return 1;
    if (n == 1) return b /* % MOD */;
    if (n % 2 == 0) {
        return mypow(b * b /* % MOD */, n / 2);
    } else {
        return mypow(b, n - 1) * b /* % MOD */;
    }
}

vector<ll> primes, cubes;

// 10^5以下の素数と、10^10以下の立方数を列挙する
void precalc() {
    bool isp[100010];
    fill(isp, isp + 100010, true);

    for (ll i = 2; i * i < 1e10; ++i) {
        if (!isp[i]) continue;
        primes.push_back(i);
        for (ll j = 2; i * j <= 100000; ++j) isp[i * j] = false;
    }

    for (ll p : primes) {
        if (p * p * p > 1e10) break;
        cubes.push_back(p * p * p);
    }
}

// 標準形に変換
ll delcube(ll n) {
    for (ll c : cubes) {
        while (n % c == 0) n /= c;
    }
    return n;
}

// 標準形の補数を求める
ll anticube(ll n) {
    ll ret = 1;

    for (ll p : primes) {
        if (p * p > n) break;
        if (n % p > 0) continue;

        int c = 0;
        while (n % p == 0) {
            n /= p;
            ++c;
        }
        ret *= mypow(p, 3 - c);
    }

    // 最後に残ったnは素数か1
    // 素数なら指数は1
    ret *= mypow(n, 2);
    return ret;
}

int main() {
    precalc();

    int N;
    cin >> N;

    // 標準形をキーに、その個数を保持する
    map<ll, int> cnt;
    for (int i = 0; i < N; ++i) {
        ll s;
        cin >> s;
        s = delcube(s);
        if (cnt.count(s) == 0) cnt[s] = 0;
        ++cnt[s];
    }

    int ans = 0;
    for (auto p : cnt) {
        if (p.second == 0) continue;
        if (p.first == 1) {  // 立方数の集合は例外
            ++ans;
            continue;
        }

        ll opp = anticube(p.first);

        // 補数集合と、大きい方を選ぶ
        if (cnt.count(opp)) {
            ans += max(cnt[p.first], cnt[opp]);
            cnt[p.first] = cnt[opp] = 0;
        } else {
            ans += cnt[p.first];
        }
    }

    cout << ans << endl;
    return 0;
}

```
