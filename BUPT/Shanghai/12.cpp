#include <cstdio>

long long a, b, c, d, e, f, g, i, m, n;
long long xa[11][1000010] = {0};

int main() {
  for (i = 2; i <= 10; i++) {
    b = 0;
    for (m = 1; m <= 1000000; m++) {
      if (m % i != 0)
        b++;
      else {
        a = m;
        b = 0;
        while (a > 0) {
          b += a % i;
          a /= i;
        }
      }
      xa[i][m] = xa[i][m - 1] + b;
    }
  }
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld", &b, &c);
    printf("Case #%lld: %lld\n", n, xa[c][b]);
  }
}