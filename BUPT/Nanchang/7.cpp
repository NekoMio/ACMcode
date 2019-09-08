#include <cstdio>
long long a, b, c, d, e, f, i;
int main() {
  scanf("%lld", &a);
  for (i = 1; i <= a; i++) {
    scanf("%lld", &b);
    if (b == 1)
      puts("18000");
    else
      puts("0");
  }
}