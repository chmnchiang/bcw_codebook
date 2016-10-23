MX = 100
def calc(x):
	for i in range(MX):
		for j in range(MX):
			y = P**i * Q**j
			Z[i][j] = x // y

	ans = 0
	for i in range(MX):
		for j in range(i):
			ans += Z[i][j] - Z[i+1][j] - Z[i][j+1] + Z[i+1][j+1]
	return ans



with open("jealous.in") as f, open("jealous.out", "w") as fw:
	A, B, P, Q = [int(x) for x in f.readline().split()]

	Z = [ [0 for i in range(MX+1)] for j in range(MX+1)]
	ans = calc(B) - calc(A-1)
	fw.write('%d\n' % ans)

	# print(calc(B) - calc(A-1))
