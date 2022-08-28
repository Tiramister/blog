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
