#include <cstdio>

long long a, b, c, d, e, f, g, i, m, n;

long long pd(long long j, long long k) {
  if (k == 0) return j;
  if (j < k) return pd(k, j);
  return pd(k, j % k);
}

int main() {
  // freopen("1.txt","r",stdin);
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld", &b, &c);
    d = 0;
    g = 1000;
    for (m = 1; m <= g; m++) {
      e = b ^ m;
      if (pd(e, m) == 1) {
        d = 1;
        for (i = 1; i < m; i++) {
          if (pd(i, e) == 1) {
            d++;
            if (d > c) i = m + 10;
          }
        }
        if (d == c) {
          printf("%lld\n", e);
          // printf("   %lld\n",m);
          m = g + 100;
        } else
          d = 0;
      }
    }
    if (d == 0) printf("-1\n");
  }
}