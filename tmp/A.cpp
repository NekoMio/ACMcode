#include <cstdio>

int a, b, c, d, e, f, g;
int i, m, n;
int x[300000] = {0}, w[300000] = {0}, wb[300000] = {0};
bool z[300000] = {0};

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  b = 0;
  for (i = 1; i <= 200200; i *= 2) {
    z[i] = 1;
    b++;
    wb[b] = i;
  }
  for (i = 2; i <= 200000; i++) {
    if (z[i + 1] == 1)
      x[i] = i + 1;
    else {
      b = 1;
      c = i;
      while (c & 1) {
        b++;
        c /= 2;
      }
      x[i] = wb[b];
    }
  }
  for (m = 1; m <= a; m++) {
    scanf("%d", &b);
    if (z[b + 1] == 1) {
      puts("1");
      for (i = 2; i < b; i++) {
        printf("%d ", x[i]);
      }
      puts("1");
    } else {
      puts("0");
      for (i = 2; i <= b; i++) {
        printf("%d ", x[i]);
      }
      puts("");
    }
  }
  return 0;
}