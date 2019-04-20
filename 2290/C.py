def mul(a, b):
    c = [[0, 0], [0, 0]]
    for i in range(2):
        for j in range(2):
            for k in range(2):
                c[i][k] += a[i][j] * b[j][k]
    return c

def pow(a, k):
    ret = [[1, 0], [0, 1]]
    while k:
        if k & 1:
            ret = mul(ret, a)
        a = mul(a, a)
        k >>= 1
    return ret

def F(k):
    return pow([[1, 1], [1, 0]], k - 1)[0][0]

def FF(k):
    return F(F(k))

a = []

for i in range(1, 100):
    p = FF(i)
    if len(str(p)) < 100000:
        a.append(p)
    else:
        break

all = len(a)

# print(a[:10])

def dfs(now, target):
    # print(lev, now, len(str(target)))
    if target == 0:
        return []
    # if now >= all:
    #     return None
    LIM = 6
    for i in range(now, LIM):
        if a[i] > target:
            return None
        store = dfs(i + 1, target - a[i])
        if store is not None:
            store.append(i + 1)
            return store
    if a[LIM] <= target:
        ret = []
        for i in range(len(a) - 1, LIM - 1, -1):
            if (i + 1 >= len(a) or a[i + 1] > target) and (a[i] <= target):
                ret.append(i + 1)
                target -= a[i]
        if target == 0:
            return ret
    return None


T = int(input())
for _ in range(T):
    n = int(input())
    answer = dfs(0, n)
    if answer is None:
        print(-1)
    else:
        print(" ".join(map(str, sorted(answer))))