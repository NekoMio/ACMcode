#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%d", &a);
  b = 1;
  for (i = 2; i <= 100; i += 2) {
    for (m = 2; m <= 100; m += 2) {
      if (i + m == a) b = 2;
    }
  }
  if (b == 2)
    printf("YES");
  else
    printf("NO");
}