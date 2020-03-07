#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%d", &b);
    if (b <= 7)
      printf("1\n");
    else
      printf("%d\n", b / 3);
  }
}