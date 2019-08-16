#include <cstdio>
int a, b, c, d, e, f, i, m, n, r, s, t;
int xa[500000] = {0}, xb[500000] = {0};
char w[500000];

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%s", &b, w);
    for (i = 1; i <= b; i++) {
      if (w[i - 1] == 'C')
        xa[i] = 1;
      else
        xa[i] = 0;
    }
    xb[b + 1] = 0;
    for (i = b; i >= 1; i--) {
      xb[i] = xb[i + 1];
      if ((i + 3 <= b) && (xa[i] == 1) && (xa[i + 1] == 1) &&
          (xa[i + 2] == 0) && (xa[i + 3] == 1))
        xb[i]++;
    }
    c = xb[1];
    if ((b >= 3) && (xb[1] == 1) && (xb[2] == 0) && (xb[3] == 1)) c++;
    d = 0;
    for (i = 1; i <= b; i++) {
      if ((i >= 4) && (xa[i - 3] == 1) && (xa[i - 2] == 1) &&
          (xa[i - 1] == 0) && (xa[i] == 1))
        d++;
      e = d + xb[i + 1];
      if ((i + 3 <= b) && (xa[i + 1] == 1) && (xa[i + 2] == 0) &&
          (xa[i + 3] == 1))
        e++;
      if ((i + 2 <= b) && (xa[i] == 1) && (xa[i + 1] == 0) && (xa[i + 2] == 1))
        e++;
      if ((i >= 3) && (xa[i - 2] == 1) && (xa[i - 1] == 1) && (xa[i] == 0)) e++;
      if (c < e) c = e;
      f = d + xb[i + 1];
      if ((i >= 2) && (i + 1 <= b) && (xa[i - 1] == 1) && (xa[i] == 1) &&
          (xa[i + 1] == 1))
        f++;
      if (c < f) c = f;
    }
    printf("%d\n", c);
  }
}