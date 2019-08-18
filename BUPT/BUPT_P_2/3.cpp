#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d%d", &b, &c, &d);
    if (b > c)
      printf("Case #%d: %d\n", n, d);
    else {
      for (i = d; i >= 0; i--) {
        if (i * c * 11 - i * b * 9 <= (d - i) * b * 11) {
          printf("Case #%d: %d\n", n, i);
          i = -10;
        }
      }
    }
  }
}