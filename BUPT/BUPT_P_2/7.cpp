#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int p, q;
};
bool sx(xl j, xl k) { return j.q < k.q; }

int a, b, c, d, e, f, g, i, m, n, r, s;
int xa[5000][5000], xb[5000][5000], xc[5000], xd[5000], xe[5000];
xl w[5000];

void ma(int &j, int k) {
  if (j < k) j = k;
}

int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d%d", &b, &c, &d);
    e = 0;
    for (i = 1; i <= c; i++) {
      e++;
      scanf("%d%d", &w[e].p, &w[e].q);
      w[e].p--;
      for (m = 1; m < e; m++) {
        if ((w[m].p <= w[e].p) && (w[e].q <= w[m].q)) {
          e--;
          m = e + 10;
        } else {
          if ((w[e].p <= w[m].p) && (w[m].q <= w[e].q)) {
            w[m].p = w[e - 1].p;
            w[m].q = w[e - 1].q;
            w[e - 1].p = w[e].p;
            w[e - 1].q = w[e].q;
            e--;
            m--;
          }
        }
      }
    }
    sort(w + 1, w + e + 1, sx);
    f = 0;
    if (e <= d) {
      for (i = 1; i <= e; i++) {
        if ((i == 1) || (w[i - 1].q <= w[i].p))
          f += w[i].q - w[i].p;
        else
          f += w[i].q - w[i - 1].q;
      }
    } else {
      m = 0;
      for (i = 1; i <= e; i++) {
        while (w[m + 1].q <= w[i].p) m++;
        xc[i] = m;
        // printf("%d %d %d %d\n",i,w[i].p,w[i].q,xc[i]);
      }
      xb[1][0] = 0;
      for (i = 1; i <= e; i++) {
        xa[1][i] = w[i].q - w[i].p;
        xb[1][i] = xa[1][i];
        ma(xb[1][i], xb[1][i - 1]);
      }
      f = xb[1][e];
      for (i = 2; i <= d; i++) {
        xb[i][i - 1] = 0;
        r = 1;
        s = 1;
        xd[r] = xa[i - 1][i - 1] - w[i - 1].q;
        xe[r] = i - 1;
        for (m = i; m <= e; m++) {
          // printf("%lld %lld\n",i,m);
          if (w[m - 1].q <= w[m].p)
            xa[i][m] = xa[i - 1][m - 1] + w[m].q - w[m].p;
          else
            xa[i][m] = xa[i - 1][m - 1] + w[m].q - w[m - 1].q;
          if (xc[m] + 1 >= i) ma(xa[i][m], xb[i - 1][xc[m]] + w[m].q - w[m].p);
          while ((r <= s) && (w[xe[r]].q <= w[m].p)) r++;
          if (r <= s) ma(xa[i][m], xd[r] + w[m].q);
          xb[i][m] = xa[i][m];
          ma(xb[i][m], xb[i][m - 1]);
          g = xa[i - 1][m] - w[m].q;
          while ((r <= s) && (g >= xd[s])) s--;
          s++;
          xd[s] = g;
          xe[s] = m;
        }
        ma(f, xb[i][e]);
      }
    }
    printf("Case #%d: %d\n", n, f);
  }
}