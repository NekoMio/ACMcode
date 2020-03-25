#pragma GCC optimize("O2")
#include <cstdio>

long long a, b, c, d, e, f, g, i, m, n;
long long xa[1000200] = {0}, xb[2000200] = {0}, xc[2000200] = {0};
long long w[1000200] = {0};
long long y = 1000000007;

long long zh(long long j, long long k) {
  return xb[j] * xc[j - k] % y * xc[k] % y;
}

long long km(long long j, long long k) {
  if (j == 0) return 1;
  if (j == 1) return k;
  long long l = km(j / 2, k);
  l = l * l % y;
  if (j & 1) l = l * k % y;
  return l;
}

int main() {
  xa[0] = 0;
  xa[1] = 1;
  xb[0] = 1;
  xb[1] = 1;
  xc[0] = 1;
  xc[1] = 1;
  for (i = 2; i <= 1000000; i++) {
    xa[i] = (xa[i - 1] + xa[i - 2]) % (y - 1);
  }
  for (i = 2; i <= 2000000; i++) {
    xb[i] = xb[i - 1] * i % y;
    xc[i] = (y - y / i) * xc[y % i] % y;
  }
  for (i = 2; i <= 2000000; i++) {
    xc[i] = xc[i - 1] * xc[i] % y;
  }
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld", &b, &c);
    d = 0;
    for (i = b; i >= 1; i--) {
      if (b % i == 0) {
        e = zh(b / i + c - 1, c - 1);
        // printf("%lld\n",e);
        for (m = i * 2; m <= b; m += i) {
          e = (e + y - w[m]) % y;
        }
        d += (km(xa[i], 2) % y + y - 1) % y * e % y;
        d %= y;
        w[i] = e;
        // printf("%lld %lld %lld\n",i,e,d);
      } else
        w[i] = 0;
    }
    // printf("%lld\n",d);
    d *= km(y - 2, zh(b + c - 1, c - 1)) % y;
    d %= y;
    printf("%lld\n", d);
  }
}