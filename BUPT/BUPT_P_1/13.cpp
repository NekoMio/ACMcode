#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int p, q;
};
bool sx(xl j, xl k) {
  if (j.p != k.p) return j.p < k.p;
  return j.q < k.q;
}

int a, b, c, d, e, f, g, i, m, n, r, s, t;
int xa[500] = {0}, xb[500] = {0}, xc[500] = {0}, xd[500] = {0};
xl w[500];

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d%d", &b, &c, &d);
    e = 0;
    for (i = 1; i <= b; i++) {
      e++;
      scanf("%d%d", &xa[e], &xb[e]);
      w[e].p = xa[e] * xa[e] + xb[e] * xb[e];
      if (w[e].p > c * c)
        e--;
      else
        w[e].q = xc[e] = i;
    }
    if (b == c) {
      printf("%d\n", e);
      for (i = 1; i < e; i++) {
        printf("%d ", xc[i]);
      }
      printf("%d\n", xc[e]);
    } else {
      sort(w + 1, w + e + 1, sx);
      f = 0;
      g = 2 * d - c;
      if (g < 0)
        g = -1;
      else
        g = g * g;
      for (i = 1; i <= e; i++) {
        if (g >= w[i].p) {
          f++;
          xd[f] = w[i].q;
        }
      }
      if (f == 0) {
        g = c - 2 * d;
        if (g < 0)
          g = -1;
        else
          g = g * g;
        for (i = 1; i <= e; i++) {
          if (w[i].p <= g) {
            f++;
            xd[f] = w[i].q;
          }
        }
        if (f == 0) {
          for (i = 1; i <= e; i++) {
            if (w[1].p == w[i].p) {
              f++;
              xd[f] = w[i].q;
            }
          }
        }
      }
      sort(xd + 1, xd + f + 1);
      printf("%d\n", f);
      for (i = 1; i < f; i++) {
        printf("%d ", xd[i]);
      }
      printf("%d\n", xd[f]);
    }
  }
}