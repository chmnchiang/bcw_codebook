

def check(d):
    b = '0' * len(d) + bin(int(d))[2:]
    # print(d, '/', b)
    return b[-len(d):] == d

cur = ['']
vec = ['0']
for i in range(161):
    # print(i, cur)
    nxt = []
    for c in cur:
        z = '0' + c
        if check(z):
            nxt.append(z)
    for c in cur:
        z = '1' + c
        if check(z):
            nxt.append(z)
            vec.append(z)
    cur = nxt[:]

N = int(open('binary.in', 'r').read())
ans = vec[N]

with open('binary.out', 'w') as f:
    f.write(str(ans) + '\n')
