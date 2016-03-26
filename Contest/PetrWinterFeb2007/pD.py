MAXN = 1010

comb = [1]

def make_comb(N):
    global comb
    for i in range(1, N+1):
        v = []
        v.append(1)
        for j in range(1, i):
            v.append(comb[j-1] + comb[j])
        v.append(1)
        comb = v

fact = [1]
for i in range(1, MAXN):
    fact.append(fact[-1] * i)

def fn(N, x):
    return comb[x] * (-2)**x * 2 * N * fact[2*N-x-1]

def calc(N):
    if N == 1:
        return 0
    ans = 0
    for i in range(N+1):
        ans += fn(N, i)
    return ans

f = open('numbers.in')
N = int(list(f)[0])
make_comb(N)
ans = calc(N)
g = open('numbers.out', 'w')
g.write(str(ans) + '\n')
g.close()
