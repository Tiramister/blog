import random


# aはnの証人となる(= nは素数でないと分かる)ならTrue
def witness(n, a):
    t, u = 0, n - 1
    while u & 1 == 0:
        t += 1
        u >>= 1
    # n-1 = 2^t * u

    x = pow(a, u, n)
    # x_0 = a^u mod n

    for _ in range(t):
        y = x * x % n
        # x_{i+1} = (x_i)^2 mod n

        if y == 1:
            # (x^2 mod n) = 1

            if x != 1 and x != n - 1:
                return True
            else:
                # 以降全て1なのでOK
                return False
        x = y

    # x_t = (a^{n-1} mod n) != 1
    return True


# nが素数か判定 試行回数s
def miller_rabin(n, s):
    # 自明なケースを処理
    if n == 1:
        return False
    if n % 2 == 0:
        return n == 2

    for _ in range(s):
        a = random.randint(1, n - 1)
        if witness(n, a):
            return False
    return True
