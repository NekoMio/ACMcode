#include <cmath>
#include <cstdio>
long long a, b, c, d, e, f, i, m, n, h;
long long r, s, t;
long long x[2000000] = {0};
bool w[10000050] = {0};

void gcd(long long j, long long k) {
  if (k == 0) {
    r = 1;
    s = 0;
  } else {
    gcd(k, j % k);
    t = r;
    r = s;
    s = t - j / k * s;
  }
}

long long kc(long long j, long long k) {
  if (k == 0) return 0;
  if (k == 1) return j;
  long long l = kc(j, k / 2);
  l = l + l;
  if (l >= b) l -= b;
  if (k & 1) {
    l += j;
    if (l >= b) l -= b;
  }
  return l;
}

int main() {
  scanf("%lld", &a);
  h = 0;
  for (i = 2; i <= 10000000; i++) {
    if (!w[i]) {
      h++;
      x[h] = i;
    }
    for (m = 1; (m <= h) && (i * x[m] <= 10000000); m++) {
      w[i * x[m]] = 1;
      if (i % x[m] == 0) m = h + 10;
    }
  }
  for (i = 1; i <= a; i++) {
    scanf("%lld", &b);
    c = b - 1;
    d = b;
    e = 1;
    while (e == 1) {
      e = 2;
      d--;
      f = sqrt(d) + 1;
      for (n = 1; (n <= h) && (x[n] <= f); n++) {
        if (d % x[n] == 0) {
          e = 1;
          n = h + 1;
        }
      }
      if (e == 1) {
        gcd(d, b);
        while (r < 0) r += b;
        c = kc(c, r);
      }
    }
    printf("%lld\n", c);
  }
#include <cstdio>
#include <cmath>
long long a,b,c,d,e,f,i,m,n,h;
  long long r, s, t;
  long long x[2000000] = {0};
  bool w[10000050] = {0};

  void gcd(long long j, long long k) {
    if (k == 0) {
      r = 1;
      s = 0;
    } else {
      gcd(k, j % k);
      t = r;
      r = s;
      s = t - j / k * s;
    }
  }

  long long kc(long long j, long long k) {
    if (k == 0) return 0;
    if (k == 1) return j;
    long long l = kc(j, k / 2);
    l = l + l;
    if (l >= b) l -= b;
    if (k & 1) {
      l += j;
      if (l >= b) l -= b;
    }
    return l;
  }

  int main() {
    scanf("%lld", &a);
    h = 0;
    for (i = 2; i <= 10000000; i++) {
      if (!w[i]) {
        h++;
        x[h] = i;
      }
      for (m = 1; (m <= h) && (i * x[m] <= 10000000); m++) {
        w[i * x[m]] = 1;
        if (i % x[m] == 0) m = h + 10;
      }
    }
    for (i = 1; i <= a; i++) {
      scanf("%lld", &b);
      c = b - 1;
      d = b;
      e = 1;
      while (e == 1) {
        e = 2;
        d--;
        f = sqrt(d) + 1;
        for (n = 1; (n <= h) && (x[n] <= f); n++) {
          if (d % x[n] == 0) {
            e = 1;
            n = h + 1;
          }
        }
        if (e == 1) {
          gcd(d, b);
          while (r < 0) r += b;
          c = kc(c, r);
        }
      }
      printf("%lld\n", c);
    