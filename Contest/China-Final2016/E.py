from fractions import Fraction

T = int(input())

for t in range(1, T+1):
	N = int(input())
	arr = []
	for j in range(N):
		x, y = map(float, input().split(':'))
		x = int(x * 1000 + 0.1)
		y = int(y * 1000 + 0.1)
		c = Fraction(x, x+y)
		arr.append(c)

	arr.sort()

	ans = 0
	tot = 0
	for i in range(N):
		tot += arr[i]
		if tot < 1:
			ans += 1
		else:
			break

	print('Case #%d: %d' % (t, ans))

