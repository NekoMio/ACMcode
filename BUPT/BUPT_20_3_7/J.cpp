#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;

int main() {
  scanf("%d%d%d", &a, &b, &c);
  a++;
  c--;
  if (b > a) b = a;
  if (b > c) b = c;
  printf("%d", 3 * b);
}