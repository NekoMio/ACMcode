#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    d = 0;
    for (i = 1; i <= b; i++) {
      scanf("%d", &c);
      d = d + c + c / 10;
      if (c % 10 != 0) d++;
    }
    printf("Case #%d: %d\n", n, d);
  }
}