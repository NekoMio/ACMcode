#include <algorithm>
#include <cstdio>
using namespace std;
int a, b, c, d, e, f, g, i, m, n;
int x[20000] = {0};

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%d", &x[i]);
  }
  sort(x + 1, x + a + 1);
  b = 0;
  for (i = 1; i <= a; i += 2) {
    b += x[i + 1] - x[i];
  }
  printf("%d\n", b);
}