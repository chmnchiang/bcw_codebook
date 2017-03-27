N = 100
K, X = map(int, raw_input().strip().split())

def f(a, b, c):
	return a*a+b*b+c*c-K*(a*b+b*c+c*a)-1

def insq(q, a, b, c):
	q.append((a, b, c))
	q.append((a, c, b))
	q.append((b, c, a))
	q.append((b, a, c))
	q.append((c, a, b))
	q.append((c, b, a))

A, B, C = 0, 1, K

st = set()
nst = set()
queue = []
insq(queue, A, B, C)

for i in range(-N, N):
	for j in range(i+1, N):
		#for d in range(0, 100):
		#	if i*i+j*j+d*K*(i+j)+d*d == K*i*j+1:
		#		print(i, j, d)
		#continue
		ss = K*K*(i+j)*(i+j) + 4 * (K*i*j+1-i*i-j*j)
		if ss < 0: continue
		ss = int(ss**0.5)
		kk = (K * (i+j) + ss) // 2
		for k in range(kk, kk+1):
			if i*i+j*j+k*k == K*(i*j+j*k+k*i) + 1:
				z = k-K*(i+j)
				#print(i, j, k, f(i, j, k))
				insq(queue, i, j, k)

#print('=========')

cnt = 0
idx = 0
for i in range(1000000):
	if idx >= len(queue):
		break
	a, b, c = queue[idx]
	idx += 1
	if (a, b, c) in st:
		continue
	st.add((a, b, c))
	if a > 0 and b > 0 and c > 0 and a not in nst and b not in nst and c not in nst:
		cnt += 1
#		print(cnt, a, b, c, ':', f(a, b, c))
		print a, b, c
		nst.add(a)
		nst.add(b)
		nst.add(c)
		if cnt >= X:
			exit(0)

	d, e, g = a, b, K*(a+b)-c
	insq(queue, d, e, g)


