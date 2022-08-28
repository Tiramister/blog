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
