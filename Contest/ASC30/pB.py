def memorize(fun):
	mem = {}
	def f(*args):
		if args in mem:
			return mem[args]
		res = fun(*args)
		mem[args] = res
		return res
	return f

@memorize
def fact(x):
	if not x: return 1
	return fact(x-1) * x

def C(n, m):
	return fact(n) // fact(m) // fact(n-m)



def calc(n):
	ans = 2**n * fact(n)

	t = -1
	for i in range(1, n+1):
		z = C(n, i) * fact(n-i) * 2**(n-i)
		z *= t
		ans += z
		t *= -1
	return ans

with open('derangements.in') as f, open('derangements.out', 'w') as fw:
	n = int(f.read())
	fw.write('%d\n' % calc(n))
