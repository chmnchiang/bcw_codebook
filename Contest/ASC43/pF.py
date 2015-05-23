from fractions import Fraction

def make_perm(N):
  st = []
  mps = {}

  def dfs(a, res):
    if res == 0:
      tp = tuple(a)
      mps[tp] = len(st)
      st.append(tp)
    ms = 1
    if len(a) >= 1:
      ms = a[-1]
    for j in range(ms, 1000):
      if j > res:
        break
      b = a[:]
      b.append(j)
      dfs(b, res-j)
  dfs([], N)
  return st, mps

def make_minlex(tp):
  lst = []
  cnt = 1
  for i in tp:
    lst += list(range(cnt+1, cnt+i))
    lst += [cnt]
    cnt += i
  return lst

def get_cyc_conf(perm):
  ret = []
  vis = [0]*len(perm)
  for i in range(len(perm)):
    if vis[i]:
      continue
    cur = i
    cnt = 0
    while True:
      vis[cur] = True
      cur = perm[cur] - 1
      cnt += 1
      if cur == i:
        break
    ret.append(cnt)
  ret.sort()
  return tuple(ret)

def make_matrix(N, st, mps):
  L = len(st)
  ret = []
  for i in range(L):
    ret.append([0]*L)
  for i in range(L):
    perm = make_minlex(st[i])
    for j in range(N):
      for k in range(N):
        perm2 = perm[:]
        tmp = perm2[j]
        perm2[j] = perm2[k]
        perm2[k] = tmp
        cyc = get_cyc_conf(perm2)
        idx = mps[cyc]
        ret[idx][i] += 1
  return ret 

def get_str(N, st, gs, vec2, step):
  idx = 0
  L = len(st)

  vec = vec2
  perm = list(range(1, N+1))
  ret = ''
  #for i in perm:
  #  ret += '{} '.format(i)
  #ret = ret[:-1] + '\n'

  prob = vec[idx] * Fraction(1, N**(2*step))
  ret += '{}/{}'.format(prob.numerator, prob.denominator)

  return ret

def matmul(A, b):
  L = len(b)
  vec = [0]*L
  for i in range(L):
    for j in range(L):
      vec[i] += A[i][j] * b[j]
  return vec  

def fact(x):
  ans = 1
  for i in range(1, x+1):
    ans *= i
  return ans

def C(a, b):
  return fact(a) // (fact(b) * fact(a-b))

def grpsize(N, st):
  ret = []
  for tp in st:
    ans = fact(N)
    bns = 1
    for i in tp:
      bns *= i
    ans //= bns

    st = {}
    for i in tp:
      if i not in st:
        st[i] = 0
      st[i] += 1
    for i in st:
      c = st[i]
      ans //= fact(c)

    ret.append(ans)
  return ret

#f = open('pFo.txt', 'w')

inp = []
st = set()
f = open('frequent.in')
for ln in f:
  if ln == '':
    continue
  a, b = [int(x) for x in ln.split()]
  if(a == 0):
    break
  st.add(a)
  inp.append((a, b))
f.close()

ans = []
for i in range(15):
  ans.append([0]*400)

for N in st:
  print(N)
  st, mps = make_perm(N)
  gs = grpsize(N, st)
  mat = make_matrix(N, st, mps)

  L = len(st)
  vec = [0]*L
  vec[0] = 1

  for t in range(301):
    s = get_str(N, st, gs, vec, t)
    #f.write('ans[{}][{}] = \"{}\";\n'.format(N, t, s))
    ans[N][t] = s
    vec = matmul(mat, vec)

f = open('frequent.out', 'w')
for a, b in inp:
  s = ans[a][b]
  f.write(' '.join(map(str, range(1, a+1))))
  f.write('\n')
  f.write(s)
  f.write('\n')

f.close()

