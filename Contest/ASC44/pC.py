
def mem(f):
    mp = {}
    def nf(*args):
        if args in mp:
            return mp[args]
        else: 
            a = f(*args)
            mp[args] = a
            return a
    return nf

def C(n, m):
    if m < 0 or m > n: return 0
    a,b = 1,1
    for i in range(m):
        a *= n-i
        b *= i+1
    return a//b

def H(n, m):
    return C(n+m-1, m)
@mem
def alpha(n, s):
    if n == 1:
        return 1
    if n == 0:
        return 0
    if s == 0:
        return 0
    ans = 0
    for i in range(1000):
        if n - i * s < 0:
            break
        ans += alpha(n-i*s, s-1) * H(delta(s), i)
    return ans

@mem
def beta(n):
    return alpha(n, n-1)

@mem
def gamma(n, s):
    if n == 1:
        return 1 if s > 0 else 0
    if n == 0:
        return 1
    if s == 0:
        return 0
    ans = 0
    for i in range(1000):
        if n - i * s < 0:
            break
        ans += gamma(n-i*s, s-1) * H(beta(s), i)
        #print "gamma ", n-i*s, s-1, "=" ,gamma(n-i*s, s-1), "*", H(beta(s), i)
    return ans

@mem
def delta(n):
    return gamma(n, n)

#for i in range(5):
#    for j in range(5):
#        print i, j, " = ", gamma(i, j)

#print gamma(2, 1)

for i in range(1, 61):
    #print "ans[" , i, "] = \"", (delta(i)), "\";"
    print 'ans[%d] = "%d"' % (i, delta(i))
