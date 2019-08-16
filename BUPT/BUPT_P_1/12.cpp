#include <cstdio>
int a, b, c, d, e, f, i, m, n, r, s, t;
int x[200000] = {0};
char w[200000];

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d%s", &b, &c, w);
    for (i = 1; i <= b; i++) {
      if (w[i - 1] == 'L')
        x[i] = -1;
      else
        x[i] = 1;
    }
    d = 0;
    e = 0;
    for (m = c; m < b; m++) {
      if (x[m] != 1) d++;
    }
    for (m = c; m > 1; m--) {
      if (x[m] == 1) e++;
    }
    if (d < e)
      printf("%d\n", d);
    else
      printf("%d\n", e);
  }
}