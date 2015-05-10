import random

def r_block(s):
  w = list(s)
  random.shuffle(w)
  return ''.join(w)

def r_random(s):
  w = list(s)
  ww = [w[i*4:(i+1)*4]for i in range(len(w)//4)]
  random.shuffle(ww)
  for i in range(len(ww)):
    random.shuffle(ww[i])
    ww[i] = ''.join(ww[i])
  ww = ''.join(ww)
  ww = list(ww)
  for i in range(len(ww)//10):
    al = random.randint(0, len(ww)-1)
    be = random.randint(0, len(ww)-1)
    tmp = ww[al]
    ww[al] = ww[be]
    ww[be] = tmp
  ww = ''.join(ww)

  return ww

vec = []
for i in range(2, 11):
  s = [l.strip('\n') for l in open('testD/{}.in'.format(i))][0]
  vec.append(r_block(s))
  vec.append(r_random(s))

with open('pD.in', 'w') as f:
  f.write(str(len(vec)) + '\n')
  for i in vec:
    f.write(i + '\n')

