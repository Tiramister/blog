---
title: "AtCoder Grand Contest 036 A - Triangle"
date: 2019-07-23
tags: [atcoder]
---

[A - Triangle](https://atcoder.jp/contests/agc036/tasks/agc036_a)

## 問題

正整数 $S$ に対し、以下を満たす整数 $X\_i, Y\_i \\, (i = 1, 2, 3)$ を 1 つ求めよ。

- $0 \\leq X\_i, Y\_i \\leq 10\^9$
- 3 点 $(X\_i, Y\_i)$ がなす三角形の面積は $S / 2$

### 制約

- $1 \\leq S \\leq 10\^\{18\}$

## 考察

自由変数が多い構築問題では、どれだけ都合の良いように自由変数を固定できるかが肝となる。

まず $X\_1 = Y\_1 = 0$ と固定する。すると、三角形の面積は外積で与えられるので $|X\_2 Y\_3 - X\_3 Y\_2| = S$ が必要十分条件となる[^1]。この絶対値は外しても問題ない。

[^1]: 作る三角形の面積が $S$ ではなく $S/2$ であることに注意。

ここで $X\_3 = 0$ と簡略化してしまうと、 $S = X\_2 Y\_3$ となり、 $S$ が大きい素数の場合に構築不能になってしまう。そこで $X\_3 = 1$ と固定し、 $X\_2 Y\_3 = S + Y\_2$ を満たす $X\_2, Y\_2, X\_3$ を探すことにする。

$S$ が最大のケースを考えると、 $X\_2 = Y\_3 = 10\^9$ 以外に解は存在しない。このケースに対処するためには、 $S + Y\_2$ を近くの平方数に近づけたら上手く行きそうである。すなわち、 $Z$ を $Z\^2 \\lt S$ を満たす最大の整数としたとき、

$$
X\_2 = Y\_3 = Z + 1, Y\_2 = (Z + 1)\^2 - S
$$

とすれば良さそうである。しかし $S = Z\^2 + 1$ のケースで $Y\_2=2Z$ となり、制約を超えてしまう。

そこで $Z (Z + 1)$ を間に挟んで、 $S$ がこれ以下である場合には

$$
X\_2 = Z, Y\_3 = Z + 1, Y\_2 = Z(Z + 1) - S
$$

としてみる。これで $Y\_2$ は高々 $Z$ となり[^2]、制約を満たすことができる。

[^2]:
    $S \\leq Z (Z + 1)$ の場合、 $Y\_2 = Z(Z + 1) - S \\lt Z (Z + 1) - Z\^2 = Z$ 。  
    $S \\gt Z (Z + 1)$ の場合、 $Y\_2 = (Z + 1)\^2 - S \\lt (Z + 1)\^2 - Z(Z + 1) = Z + 1$ 。

## 実装例

提出時には不要だが、以下のように assert をかけておくと予期しないバグに気づけて便利。

[提出 #6512335 - AtCoder Grand Contest 036](https://atcoder.jp/contests/agc036/submissions/6512335)

```cpp
using namespace std;
using lint = long long;

// Z * Z < Sを満たす最小のZを求める
lint sqrti(lint S) {
    lint ok = 0, ng = 1e9 + 1;
    while (ng - ok > 1) {
        lint mid = (ok + ng) / 2;
        (mid * mid < S ? ok : ng) = mid;
    }
    return ok;
}

int main() {
    lint S;
    cin >> S;
    lint Z = sqrti(S);

    vector<lint> X(3), Y(3);
    X[0] = Y[0] = 0, X[2] = 1;

    if (S <= Z * (Z + 1)) {
        Y[1] = Z * (Z + 1) - S;
        X[1] = Z, Y[2] = Z + 1;
    } else {
        Y[1] = (Z + 1) * (Z + 1) - S;
        X[1] = Y[2] = Z + 1;
    }

    assert(X[1] * Y[2] - X[2] * Y[1] == S);
    for (int i = 0; i < 3; ++i) {
        assert(X[i] <= 1e9);
        assert(Y[i] <= 1e9);
        cout << X[i] << " " << Y[i] << " ";
    }
    cout << endl;
    return 0;
}
```

