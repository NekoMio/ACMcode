#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%d%d", &b, &c);
    d = 0;
    for (m = 1; m <= b; m++) {
      printf("%c", d + 'a');
      d++;
      if (d == c) d = 0;
    }
    printf("\n");
  }
}