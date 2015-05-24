from random import randint, sample

N = 8
MX = 20
def search():
  ls = sample(range(1, MX+1), N)
  ls = sorted(ls)


  for k in range(1, ls[0]):
    ans = [ls[0]-k]
    addl = [x+y for x in ls for y in ls if x < y]
    fg = True
    for i in range(1, N):
      mn = min(addl)
      t = mn - ans[0]
      for j in range(i):
        s = t + ans[j]
        if s not in addl:
          fg = False
          break
        addl.remove(s)
      if not fg: break
      ans.append(t)
    if fg:
      print(fg, ls, ans)
      return True
  return False


print(N)
while not search():
  pass
