N = int(input())
lst = [int(x)-1 for x in input().strip().split()][::-1]

lst[-2], lst[-1] = lst[-1], lst[-2]

ans = ((1<<N) - 1) * 2
for i in range(N-1, -1, -1):
	if lst[2*i] != 2 * i:
		if i == 0:
			ans += 1
		else:
			ans += (1<<i) * 2
			lst[2*i-2], lst[2*i-1] = lst[2*i-1], lst[2*i-2]

print(ans)
