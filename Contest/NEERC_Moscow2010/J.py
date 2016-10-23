x, y = input().split(' ')

def toi(a):
	zz = a.split('.')
	if len(zz) == 1:
		return int(zz[0]) * 10**10


	ll = 10 - len(zz[1])
	return (int(zz[0]) * 10 ** len(zz[1]) + int(zz[1])) * 10 ** (ll)


a, b = toi(x), toi(y)

print(a//b)
