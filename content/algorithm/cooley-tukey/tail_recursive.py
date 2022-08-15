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
