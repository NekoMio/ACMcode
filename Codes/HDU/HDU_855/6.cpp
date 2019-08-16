#include <cstdio>

long long a, b, c, d, e, f, i, m, n, r, s, t;
long long xa[300000] = {0}, xb[300000] = {0}, xc[300000] = {0},
          xd[300000] = {0};
long long xpa[300000] = {0}, xpb[300000] = {0}, xpc[300000] = {0},
          xqa[300000] = {0}, xqb[300000] = {0}, xqc[300000] = {0};
long long wa[300000] = {0}, wb[300000] = {0};
long long y = -99999999999;

void sca(long long j) {
  long long k, l, r, s;
  xa[j] = 1;
  k = 0;
  xpa[j] = xpb[j] = xqa[j] = xqb[j] = y;
  r = xb[j];
  s = wa[r];
  while (r > 0) {
    if (xa[s] == 0) {
      k++;
      // printf("%lld %lld\n",j,s);
      sca(s);
      if (xpa[j] < xqa[s]) {
        xpb[j] = xpa[j];
        xpa[j] = xqa[s];
        xpc[j] = s;
      } else {
        if (xpb[j] < xqa[s]) xpb[j] = xqa[s];
      }
      if (xqa[j] < xpa[s]) {
        xqb[j] = xqa[j];
        xqa[j] = xpa[s];
        xqc[j] = s;
      } else {
        if (xqb[j] < xpa[s]) xqb[j] = xpa[s];
      }
    }
    r = wb[r];
    s = wa[r];
  }
  xd[j] = k;
  if (k == 0) {
    xpa[j] = xc[j];
    xqa[j] = -xc[j];
  } else {
    xpa[j] = -xpa[j] + xc[j];
    xqa[j] = -xqa[j] - xc[j];
    xpb[j] = -xpb[j] + xc[j];
    xqb[j] = -xqb[j] - xc[j];
  }
  // printf("%lld %lld %lld %lld %lld %lld %lld
  // %lld\n",j,k,xpa[j],xpb[j],xpc[j],xqa[j],xqb[j],xqc[j]);
  xa[j] = 0;
}

void ma(long long &j, long long k) {
  if (j < k) j = k;
}

void scb(long long j, long long k, long long l) {
  // printf("%lld %lld %lld\n",j,k,l);
  long long r, s, h1, h2, h3;
  xa[j] = 1;
  h3 = l;
  h1 = -l + xc[j];
  h2 = -k - xc[j];
  ma(d, h1);
  if (j == 1) {
    if (xd[j] == 1) {
      h1 = xc[j];
      h2 = -xc[j];
    }
    h3 = y;
  }
  if (xd[j] > 0) {
    r = xb[j];
    s = wa[r];
    while (r > 0) {
      if (xa[s] == 0) {
        k = h1;
        l = h2;
        if (xpc[j] == s)
          ma(k, xpb[j]);
        else
          ma(k, xpa[j]);
        if (xqc[j] == s)
          ma(l, xqb[j]);
        else
          ma(l, xqa[j]);
        scb(s, k, l);
        ma(h3, xqa[s]);
      }
      r = wb[r];
      s = wa[r];
    }
  }
  ma(d, -h3 + xc[j]);
  // printf("%lld %lld %lld %lld %lld\n",j,h1,h2,-h3+xc[j],d);
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld", &b);
    for (i = 1; i <= b; i++) {
      scanf("%lld", &xc[i]);
    }
    for (i = 1; i <= b; i++) {
      scanf("%lld", &c);
      xc[i] -= c;
      xa[i] = xb[i] = xd[i] = 0;
    }
    for (i = 1; i < b; i++) {
      scanf("%lld%lld", &c, &d);
      wa[2 * i - 1] = d;
      wb[2 * i - 1] = xb[c];
      xb[c] = 2 * i - 1;
      wa[2 * i] = c;
      wb[2 * i] = xb[d];
      xb[d] = 2 * i;
    }
    sca(1);
    d = y;
    scb(1, -y, -y);
    if (b == 1) d = xc[1];
    printf("%lld\n", d);
  }
}