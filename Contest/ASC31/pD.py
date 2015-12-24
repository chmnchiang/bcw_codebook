def factor(x):
	r = 1
	for i in range(1, x+1):
		r = r * i
	return r

def calc(n, k):
	ans = 1;

	for i in range(n-k+1, n+1):
		ans *= i
	
	return ans
with open("discuss.in","r") as file:
	z = int(file.read())
ans = 10**1000

for k in range(0, 200):
	fk = factor(k) * z

	cnt = 0
	r = z

	if k > 0:
		ffk = fk
		while(ffk > 0):
			cnt += 1
			ffk //= 10
		cnt = (cnt // k) + 1
		rrr = 10 ** cnt
		r = min(r, rrr)

	l = 2*k

	while( l < r ):
		mid = ( l + r ) // 2

		ret = calc( mid, k )

		if ret < fk :
			l = mid + 1
		else:
			r = mid
		
	if calc( l, k) == fk :
		ans = min( ans, l )

	#print(k, l, calc(l, k), fk)
		
if(ans == 10*1000):
	ans = z

if(ans == 0):
	ans = 1

with open("discuss.out", "w") as file:
	file.write( str(ans) )
