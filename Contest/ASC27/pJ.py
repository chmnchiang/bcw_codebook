#FILEIO

f = open('separable.in', 'r')

MAXN = 111
M, N = map(int, list(f)[0].split())

fact = [1]
for i in range(1, MAXN):
	fact.append(fact[-1] * i)

def comb(a, b):
	return fact[a] // (fact[a-b] * fact[b])

def ca(m, n):
	res = 2*(n-1) + (m-1)**n
	for i in range(1, n):
		for j in range(i+1, n):
			res += 4 * (m-1)**(j-i)
	for i in range(1, n):
		res += 4 * (m-1)**i
	return res

def calc(m, n):
	D = n-1
	Dp = m-1
	C = 2*(n-1)
	Cp = 2*(m-1)
	B = comb(m+n, n) - 2
	A = ca(m, n)
	Ap = ca(n, m)

	return 2*A + 2*Ap - 4*B - C - Cp + 2*D + 2*Dp

ans = calc(M, N) // 2

f = open('separable.out', 'w')

f.write(str(ans) + '\n')
f.close()
