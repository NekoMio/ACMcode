#include <algorithm>
#include <cstdio>
using namespace std;

int a, b, c, d, e, f, g, i, m, n;
int x[3000] = {0};

int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d", &b, &c);
    for (i = 1; i <= c; i++) {
      scanf("%d%d", &d, &e);
      x[2 * i - 1] = d;
      x[2 * i] = e + 1;
    }
    sort(x + 1, x + 2 * c + 1);
    d = 0;
    for (i = 1; i <= c; i++) {
      d += x[2 * i] - x[2 * i - 1];
    }
    printf("Case #%d: %d\n", n, d);
  }
}