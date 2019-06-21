n,m=raw_input().split()  
n = int(n)
m = int(m)
c1 = 1
c2 = 1
for i in range(1, m + 1):
    c1 = c1 * (n + m - i + 1)
for i in range(1, m + 1):
    c1 = c1 / i
for i in range(1, m):
    c2 = c2 * (n + m - i + 1)
for i in range(1, m):
    c2 = c2 / i
print c1 - c2