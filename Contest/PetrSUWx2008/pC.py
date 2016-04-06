from fractions import Fraction
import copy
import random

P = 10**70 + 33
P2 = P // 2

def gauss_elim(N, arrr, brrr):
	A = copy.deepcopy(arrr)
	b = copy.deepcopy(brrr)
	for i in xrange(N):
		if b[i] < 0:
			b[i] += P
		for j in xrange(N):
			if A[i][j] < 0:
				A[i][j] += P

	zzz = 1
	det = 1
	for i in xrange(N):
		piv = -1
		for j in xrange(i, N):
			if A[j][i] != 0:
				if piv == -1:
					piv = j
					break
		if piv == -1:
			return 0, b
		if piv != i:
			tmp = A[piv]
			A[piv] = A[i]
			A[i] = tmp
			tmp = b[piv]
			b[piv] = b[i]
			b[i] = tmp
			det = (det * (P-1)) % P
		prat = A[i][i]
#		det = (det * prat) % P
		for j in xrange(N):
			if j <= i:
				continue
			rat = A[j][i]
			if rat == 0:
				continue
			for k in xrange(N):
				A[j][k] = (A[j][k] * prat) % P
			b[j] = (b[j] * prat) % P
			zzz = (zzz * prat) % P
			for k in xrange(N):
				A[j][k] -= rat * A[i][k]
				A[j][k] %= P
				if A[j][k] < 0:
					A[j][k] += P
			b[j] -= rat * b[i]
			b[j] %= P
			if b[j] < 0:
				b[j] += P
#		print(A)

	for i in xrange(N):
		det = (det * A[i][i]) % P
	det = (det * pow(zzz, P-2, P)) % P

	if det > P2:
		det -= P
	for i in xrange(N):
		if b[i] > P2:
			b[i] -= P

#	print 'X', det
	
	return det, b

def gauss_elim2(N, arrr, brrr):
	A = copy.deepcopy(arrr)
	b = copy.deepcopy(brrr)
	for i in xrange(N):
		if b[i] < 0:
			b[i] += P
		for j in xrange(N):
			if A[i][j] < 0:
				A[i][j] += P

	det = 1
	for i in xrange(N):
		piv = -1
		for j in xrange(i, N):
			if A[j][i] != 0:
				if piv == -1:
					piv = j
					break
		if piv == -1:
			return 0, b
		if piv != i:
			tmp = A[piv]
			A[piv] = A[i]
			A[i] = tmp
			tmp = b[piv]
			b[piv] = b[i]
			b[i] = tmp
			det = (det * (P-1)) % P
		rat = A[i][i]
		irat = pow(rat, P-2, P)
		for j in xrange(N):
			A[i][j] = (A[i][j] * irat) % P
		b[i] = (b[i] * irat) % P
		det = (det * rat) % P
		for j in xrange(N):
			if i == j:
				continue
			rat = A[j][i]
			if rat == 0:
				continue
			for k in xrange(N):
				A[j][k] -= rat * A[i][k]
				A[j][k] %= P
				if A[j][k] < 0:
					A[j][k] += P
			b[j] -= rat * b[i]
			b[j] %= P
			if b[j] < 0:
				b[j] += P
#		print(A)

	if det > P2:
		det -= P
	for i in xrange(N):
		if b[i] > P2:
			b[i] -= P
	
	return det, b


f = open('ballistic.in')
l = list(f)
N = int(l[0])
l = l[1:]
arr = [list(map(int, x.split())) for x in l]

if False:
	N = 20
	arr = []
	for i in xrange(N):
		arr.append([])
		for j in xrange(N):
			arr[i].append(random.randint(-1000,1000))
#print(arr)


detlist = []
zero = [0] * N
dmlist = range(1, N+2)
for i in dmlist:
	narr = copy.deepcopy(arr)
	for j in xrange(N):
		narr[j][j] -= i
	a, b = gauss_elim(N, narr, zero)
	detlist.append(a)

crr = []
for i in dmlist:
	crr.append([i**j for j in xrange(N+1)])

a, b = gauss_elim2(N+1, crr, detlist)

ans = b[::-1]
f = open('ballistic.out', 'w')
for x in ans:
	f.write(str(x) + '\n')
f.close()
