def get(x):
  cnt=0
  while x:
    x /= 2
    cnt = cnt + 1
  return cnt
def Get2(x, cnt):
  for i in range(cnt):
    if (x & (1 << i)) == 0:
      tmp = x & ((1 << i) - 1)
      x -= tmp
      x /= 2
      return x + tmp
  return x
T = input()
while T:
  T = T - 1
  n,m=raw_input().split();
  n=int(n)
  m=int(m)
  cnt = get(n)
  if m == 2:
    print Get2(n, cnt)
  else:
    ans = 0
    while cnt:
      cnt = cnt - 1
      if ((1 << cnt) - 1) * m < n:
        n -= min(m, n / (1 << cnt)) << cnt
        ans |= (1 << cnt)
    if n != 0:
      ans |= 1
    print ans