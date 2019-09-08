#include <cstdio>
#include <cstdio>
#include <cstring>
#include <iostream>
#define LL long long
using namespace std;
struct China_data {
  LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
  LL extgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }
    LL GCD = extgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
    return GCD;
  }
  LL inv(LL a, LL n) {
    LL x, y;
    int tmp = extgcd(a, n, x, y);
    if (tmp != 1) return -1;
    return (x % n + n) % n;
  }
  bool merge(LL a1, LL n1, LL a2, LL n2, LL& a3, LL& n3) {
    LL GCD = gcd(n1, n2);
    LL c = a2 - a1;
    if (c % GCD) return 0;
    c = (c % n2 + n2) % n2;
    c /= GCD;
    n1 /= GCD;
    n2 /= GCD;
    c *= inv(n1, n2);
    c %= n2;
    c *= n1 * GCD;
    c += a1;
    n3 = n1 * n2 * GCD;
    a3 = (c % n3 + n3) % n3;
    return 1;
  }
  LL operator()(LL* a, LL* b, int n) {
    LL a1 = a[1], n1 = b[1];
    LL a2, n2;
    for (int i = 2; i <= n; i++) {
      LL aa, nn;
      a2 = a[i], n2 = b[i];
      if (!merge(a1, n1, a2, n2, aa, nn)) return -1;
      a1 = aa;
      n1 = nn;
    }
    return (a1 % n1 + n1) % n1;
  }
} China;

long long a, b, c, d, e, f, g, i, m, n;
long long xa[30] = {0}, xb[30] = {0};

void js(long long& j, long long& k) {
  long long l;
  l = j;
  j = k;
  k = l;
}

int main() {
  scanf("%lld", &a);
  for (i = 1; i <= a; i++) {
    scanf("%lld%lld", &xa[i], &xb[i]);
  }
  c = 1;
  d = 1;
  g = 0;
  while (d <= 1000000000000000) {
    f = c + d;
    e = 0;
    for (i = 1; i <= a; i++) {
      if (f % xa[i] != xb[i]) e = 1;
    }
    c = d;
    d = f;
    if (e == 0) {
      g = 1;
      d = 1000000000000001;
    }
  }
  if (g == 1)
    puts("Lbnb!");
  else {
    c = China(xb, xa, a);
    if (c <= 1)
      puts("Tankernb!");
    else
      puts("Zgxnb!");
  }
}