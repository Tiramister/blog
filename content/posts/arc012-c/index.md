---
title: "AtCoder Regular Contest 012 C - 五目並べチェッカー"
date: 2019-10-28
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/arc012/tasks/arc012_3
  - label: My Submission
    url: https://atcoder.jp/contests/arc012/submissions/8186625
---

## 問題

$19 \\times 19$ の黒石と白石が置かれた盤面が与えられるので，
それが五目並べの盤面として妥当か判定せよ．
ただし黒石が先手とする．

## 考察

極力実装が楽なように問題の条件を言い換えた結果，以下のような判定方法にたどり着いた．

- まず石の個数の差から，その盤面が valid かどうか判定する．
  - valid かつ、どちらも五目揃っていなければ対戦中なので OK．
- どちらかが揃っている場合， **その一手前では揃っていない** ．よって全ての碁石に対して，それを取り除いた盤面が対戦中のものか調べる。
  - もしそのような石がなければ，揃った上でもう一手打っているので NG．

## 実装例

{{<code file="0.cpp" language="cpp">}}
