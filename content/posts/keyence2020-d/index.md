---
title: "キーエンス プログラミング コンテスト 2020 D - Swap and Flip"
date: 2020-01-19
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/keyence2020/tasks/keyence2020_d
  - label: My Submission
    url: https://atcoder.jp/contests/keyence2020/submissions/9574919
---

## 問題

両面に整数が書かれた $n$ 枚のカードがあり， $i$ 枚目の表には $a\_i$ ，裏には $b\_i$ が書かれている．

今からこのカードに対して以下の操作を好きなだけ行う．

- $1 \\leq i \\leq n - 1$ を選ぶ．
- $i$ 枚目と $i + 1$ 枚目を，両方とも裏返してから swap する．

表に書かれた整数からなる数列が単調非減少列になるようにできるか判定し，できるなら最小の操作回数を出力せよ．

### 制約

- $1 \\leq n \\leq 18$
- $1 \\leq a\_i, b\_i \\leq 50 (= X)$

## 考察

$dp\_\{S, x\} =$ 「カードの集合 $S$ が使われていて，末尾が $x$ になる操作回数の最小値」という bitDP を考える．

まず $|S|$ から次のカードが置かれる場所が分かる．ここで「 **カードの表裏は移動距離の偶奇のみで決まる** 」というのがポイント．よって次に置かれるカードを決めたとき，どちらの面が表になるかが決まる．

よって

- 次のカードを全探索
- index から表裏を判定
- $x$ 以上なら転倒数( $S$ 中のそれより index が大きいカードの個数)を加えて遷移

とすればこの DP テーブルは $O(X n\^2 2\^n)$ で埋められる．かなり際どいが一応通る．

転倒数を bitmask+popcount で $O(1)$ にして， $x$ を index で持つか座圧するかすれば $O(n\^2 2\^n)$ に落ちるはず．

## 実装例

これで 1570 ms．

{{<code file="0.cpp" language="cpp">}}
