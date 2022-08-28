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
