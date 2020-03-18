#include <cstdio>
long long a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%lld", &a);
  for (i = 1; i <= a; i++) {
    scanf("%lld", &b);
    if (b == 1)
      printf("5\n");
    else
      printf("%lld\n", b + 5);
  }
}