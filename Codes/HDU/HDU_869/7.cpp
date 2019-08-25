#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
bool x[1300][1300];

void sc(int h1, int h2, int h3, int h4, bool j) {
  int h5, h6;
  // printf("%d %d %d %d\n",h1,h2,h3,h4);
  if (h1 == h2)
    x[h1][h3] = j;
  else {
    h5 = (h1 + h2) / 2;
    h6 = (h3 + h4) / 2;
    sc(h1, h5, h3, h6, j);
    sc(h5 + 1, h2, h3, h6, j ^ 1);
    sc(h1, h5, h6 + 1, h4, j);
    sc(h5 + 1, h2, h6 + 1, h4, j);
  }
}

int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    c = 1;
    for (i = 1; i <= b; i++) {
      c *= 2;
    }
    sc(1, c, 1, c, 1);
    for (i = 1; i <= c; i++) {
      for (m = 1; m <= c; m++) {
        if (x[i][m] == 1)
          putchar('C');
        else
          putchar('P');
      }
      putchar('\n');
    }
  }
  return 0;
}