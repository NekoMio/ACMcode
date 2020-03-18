#include <cstdio>
long long a, b, c, d, e, f, g, i, m, n;
long long ra, rb, rc, sa, sb, sc;

long long cd(long long j, long long k) {
  if (j < 0) return cd(-j, k);
  if (j < k) return cd(k, j);
  if (k == 0) return j;
  return cd(k, j % k);
}

int main() {
  scanf("%lld", &a);
  for (i = 1; i <= a; i++) {
    scanf("%lld%lld%lld%lld%lld%lld", &ra, &rb, &rc, &sa, &sb, &sc);
    b = ra * sb + rb * sc + rc * sa - rb * sa - rc * sb - ra * sc;
    c = ra + rb + rc;
    d = cd(b, c);
    b /= d;
    c /= d;
    if (c == 1)
      printf("%lld\n", b);
    else
      printf("%lld/%lld\n", b, c);
  }
}