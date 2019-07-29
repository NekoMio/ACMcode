#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  long long j, k;
};

long long a, b, c, d, e, f, g, i, m, n;
long long r, s, t, r1, s1, t1;
long long x[500000] = {0};
long long wa[500000] = {0}, wc[500000] = {0};
long long za[500000] = {0}, zb[500000] = {0};
xl wb[500000] = {0};

inline long long Get() {
  long long Num = 0, Flag = 1;
  char ch;
  do {
    ch = getchar();
    if (ch == '-') Flag = -Flag;
  } while (ch < '0' || ch > '9');
  do {
    Num = Num * 10 + ch - '0';
    ch = getchar();
  } while (ch >= '0' && ch <= '9');
  return Num * Flag;
}

inline bool sx(xl p, xl q) { return p.j < q.j; }

inline void mi(long long &j, long long k) {
  if (j > k) j = k;
}

inline void ma(long long &j, long long k) {
  if (j < k) j = k;
}
/*
void cj(long long j,long long k,long long l)
{
long long zh=(k+l)/2;
if(k!=l)
{
    cj(2*j,k,zh);
    cj(2*j+1,zh+1,l);
}
z[j]=0;
}

long long qj(long long j,long long k,long long l,long long jw)
{
long long zh=(k+l)/2,gg;
if(k=l) return x[j];
if(jw=zh) return x[2*j];
if(jw<zh) return qj(2*j,k,zh,jw);
gg=x[2*j];
max(gg,qj(2*j+1,zh+1,l,jw));
return gg;
}


void jr(long long j,long long k,long long l,long long jw)
{
long long zh=(k+l)/2;
if(k=l) x[j]=wc[i];
if(jw<=zh) jr(2*j,k,zh,jw);
else jr(2*j+1,zh+1,l,jw);
max(x[j],x[2*j]);
max(x[j],x[2*j+1]);
}*/

inline void cr(long long j, long long k) {
  while (j <= b + 1) {
    ma(za[j], k);
    j = j + zb[j];
  }
}

inline long long qj(long long j) {
  long long k = -1;
  while (j > 0) {
    ma(k, za[j]);
    j = j - zb[j];
  }
  return k;
}

int main() {
  // freopen("1.in","r",stdin);
  // scanf("%lld",&a);
  a = Get();
  for (n = 1; n <= a; n++) {
    // scanf("%lld%lld",&b,&c);
    b = Get();
    c = Get();
    r = -1000000000 * b;
    s = 1000000000 * b;
    wa[0] = 0;
    for (i = 1; i <= b; i++) {
      // scanf("%lld",&x[i]);
      x[i] = Get();
      wa[i] = wa[i - 1] + x[i];
      wb[i].j = -wa[i];
      wb[i].k = i;
    }
    wb[b + 1].j = 0;
    wb[b + 1].k = 0;
    sort(wb + 1, wb + b + 2, sx);
    for (i = 1; i <= b + 1; i++) {
      wc[wb[i].k] = i;
      zb[i] = i & (-i);
    }
    while (r < s) {
      t = (r + s + 10000000000000000 + 10000000000000000) / 2 -
          10000000000000000;
      d = 0;
      e = 0;
      for (i = 1; i <= b + 1; i++) {
        za[i] = -1;
      }
      cr(wc[0], 0);
      for (i = 1; i <= b; i++) {
        f = t - wa[i];
        r1 = 0;
        s1 = b + 1;
        while (r1 < s1) {
          t1 = (r1 + s1 + 10000000000000000 + 10000000000000000 + 1) / 2 -
               10000000000000000;
          if (wb[t1].j > f)
            s1 = t1 - 1;
          else
            r1 = t1;
        }
        x[i] = qj(r1) + 1;
        if (x[i] == 0) x[i] = -1;
        // printf("%lld %lld %lld %lld\n",i,f,r1,x[i]);
        cr(wc[i], x[i]);
        ma(d, x[i]);
      }
      // printf("==%lld %lld %lld %lld\n",r,s,t,d);
      if (d >= c)
        s = t;
      else
        r = t + 1;
    }
    printf("%lld\n", r);
  }
}
#include <cstdio>
#include <algorithm>
using namespace std;

struct xl {
  long long j, k;
};

long long a, b, c, d, e, f, g, i, m, n;
long long r, s, t, r1, s1, t1;
long long x[500000] = {0};
long long wa[500000] = {0}, wc[500000] = {0};
long long za[500000] = {0}, zb[500000] = {0};
xl wb[500000] = {0};

inline long long Get() {
  long long Num = 0, Flag = 1;
  char ch;
  do {
    ch = getchar();
    if (ch == '-') Flag = -Flag;
  } while (ch < '0' || ch > '9');
  do {
    Num = Num * 10 + ch - '0';
    ch = getchar();
  } while (ch >= '0' && ch <= '9');
  return Num * Flag;
}

inline bool sx(xl p, xl q) { return p.j < q.j; }

inline void mi(long long &j, long long k) {
  if (j > k) j = k;
}

inline void ma(long long &j, long long k) {
  if (j < k) j = k;
}
/*
void cj(long long j,long long k,long long l)
{
long long zh=(k+l)/2;
if(k!=l)
{
    cj(2*j,k,zh);
    cj(2*j+1,zh+1,l);
}
z[j]=0;
}

long long qj(long long j,long long k,long long l,long long jw)
{
long long zh=(k+l)/2,gg;
if(k=l) return x[j];
if(jw=zh) return x[2*j];
if(jw<zh) return qj(2*j,k,zh,jw);
gg=x[2*j];
max(gg,qj(2*j+1,zh+1,l,jw));
return gg;
}


void jr(long long j,long long k,long long l,long long jw)
{
long long zh=(k+l)/2;
if(k=l) x[j]=wc[i];
if(jw<=zh) jr(2*j,k,zh,jw);
else jr(2*j+1,zh+1,l,jw);
max(x[j],x[2*j]);
max(x[j],x[2*j+1]);
}*/

inline void cr(long long j, long long k) {
  while (j <= b + 1) {
    ma(za[j], k);
    j = j + zb[j];
  }
}

inline long long qj(long long j) {
  long long k = -1;
  while (j > 0) {
    ma(k, za[j]);
    j = j - zb[j];
  }
  return k;
}

int main() {
  // freopen("1.in","r",stdin);
  // scanf("%lld",&a);
  a = Get();
  for (n = 1; n <= a; n++) {
    // scanf("%lld%lld",&b,&c);
    b = Get();
    c = Get();
    r = -1000000000 * b;
    s = 1000000000 * b;
    wa[0] = 0;
    for (i = 1; i <= b; i++) {
      // scanf("%lld",&x[i]);
      x[i] = Get();
      wa[i] = wa[i - 1] + x[i];
      wb[i].j = -wa[i];
      wb[i].k = i;
    }
    wb[b + 1].j = 0;
    wb[b + 1].k = 0;
    sort(wb + 1, wb + b + 2, sx);
    for (i = 1; i <= b + 1; i++) {
      wc[wb[i].k] = i;
      zb[i] = i & (-i);
    }
    while (r < s) {
      t = (r + s + 10000000000000000 + 10000000000000000) / 2 -
          10000000000000000;
      d = 0;
      e = 0;
      for (i = 1; i <= b + 1; i++) {
        za[i] = -1;
      }
      cr(wc[0], 0);
      for (i = 1; i <= b; i++) {
        f = t - wa[i];
        r1 = 0;
        s1 = b + 1;
        while (r1 < s1) {
          t1 = (r1 + s1 + 10000000000000000 + 10000000000000000 + 1) / 2 -
               10000000000000000;
          if (wb[t1].j > f)
            s1 = t1 - 1;
          else
            r1 = t1;
        }
        x[i] = qj(r1) + 1;
        if (x[i] == 0) x[i] = -1;
        // printf("%lld %lld %lld %lld\n",i,f,r1,x[i]);
        cr(wc[i], x[i]);
        ma(d, x[i]);
      }
      // printf("==%lld %lld %lld %lld\n",r,s,t,d);
      if (d >= c)
        s = t;
      else
        r = t + 1;
    }
    printf("%lld\n", r);
  