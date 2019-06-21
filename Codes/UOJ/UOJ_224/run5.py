for i in range(32):
    print "I"
last = 1
cnt = 32
t = 2
for i in range(31):
    print "< %d 1" %last
    cnt = cnt + 1
    print "+ %d %d" %(cnt, t)
    cnt = cnt + 1
    last = cnt
    t = t + 1
print "O %d" %cnt