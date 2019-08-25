#include <cstdio>
long long a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld", &b, &c);
    d = 0;
    e = 1;
    while ((e <= b) && (e <= c)) {
      if ((b & c & e) > 0) d += e;
      e *= 2;
    }
    if (d == 0) d = 1;
    printf("%lld\n", d);
  }
  return 0;
}