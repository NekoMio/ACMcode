#include <algorithm>
#include <cstdio>
using namespace std;

long long a, b, c, d, e, f, g, i, m, n;
long long x[3000] = {0};
long long wa[200000] = {0}, wb[200000] = {0};
long long y = 1000000007;

int main() {
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld", &b);
    c = 0;
    for (i = 1; i <= b; i++) {
      scanf("%lld", &x[i]);
      c += x[i];
    }
    sort(x + 1, x + b + 1);
    wa[0] = 1;
    for (i = 1; i <= c; i++) {
      wa[i] = wb[i] = 0;
    }
    d = 0;
    e = 0;
    for (i = b; i >= 1; i--) {
      d += x[i];
      for (m = d; m >= x[i]; m--) {
        wb[m] += wa[m - x[i]];
        wb[m] %= y;
      }
      f = (c + x[i]) / 2;
      if (f > d) f = d;
      // printf("1--%d %d %d\n",i,x[i],f);
      for (m = (c + 1) / 2; m <= f; m++) {
        e += wb[m];
        while (e >= y) e -= y;
        // printf("2--%d %d %d\n",m,wb[m],e);
      }
      for (m = d; m >= x[i]; m--) {
        wa[m] += wb[m];
        wb[m] = 0;
      }
    }
    printf("%lld\n", e % y);
  }
}