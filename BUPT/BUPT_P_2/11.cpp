#include <cstdio>
unsigned long long a, b, c, d, e, f, g, i, m, n;
int main() {
  scanf("%llu", &a);
  for (n = 1; n <= a; n++) {
    scanf("%llu", &b);
    if (b == 0) c = 1;
    if (b == 1) c = 9;
    if (b == 2) c = 41;
    if (b == 3) c = 109;
    if (b == 4) c = 205;
    if (b == 5) c = 325;
    if (b == 6) c = 473;
    if (b == 7) c = 649;
    if (b == 8) c = 853;
    if (b == 9) c = 1085;
    if (b >= 10) {
      c = (b - 9) * (b - 8) * 14 + (b - 9) * 232 + 1085;
    }
    printf("Case #%llu: %llu\n", n, c);
  }
}