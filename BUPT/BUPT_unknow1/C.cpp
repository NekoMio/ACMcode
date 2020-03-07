#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int r, s;
};

bool sx1(xl j, xl k) {
  if (j.r != k.r) return j.r < k.r;
  return j.s < k.s;
}

bool sx2(xl j, xl k) {
  if ((j.r == 0) || (k.r == 0)) {
    if (j.r == 0) {
      if (k.r == 0) return j.s < k.s;
      return 0;
    }
    return 1;
  }
  if (j.s * k.r != j.r * k.s) return j.s * k.r < j.r * k.s;
  return j.s < k.s;
}

int a, b, c, d, e, f, g, i, m, n, h, o, p, q;
int w[100][100];
xl xa[100], xb[100];

int zh(int j) {
  if (j < 0) return -j;
  return j;
}

int mj(xl j, xl k) { return zh(j.r * k.s - j.s * k.r); }

int mmj(xl j, xl k, xl l) {
  return zh((j.r - l.r) * (k.s - l.s) - (j.s - l.s) * (j.r - l.r));
}

int pd(xl j, xl k, xl l) {
  if (j.s * l.r == j.r * l.s) return 1;
  if (k.s * l.r == k.r * l.s) return 1;
  if ((k.s - j.s) * (l.r - j.r) == (k.r - j.r) * (l.s - l.s)) return 1;
  if (mj(j, k) >= mj(j, l) + mj(k, l) + mmj(j, k, l)) return 0;
  return 1;
}

int ma(int &j, int k) {
  if (j < k) j = k;
}

int main() {
  // freopen("1.in","r",stdin);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    for (i = 1; i <= b; i++) {
      scanf("%d%d", &xa[i].r, &xa[i].s);
    }
    c = 1;
    sort(xa + 1, xa + b + 1, sx1);
    for (i = 2; i <= b; i++) {
      if ((xa[i - 1].r != xa[i].r) || (xa[i - 1].s != xa[i].s)) {
        c++;
        xa[c] = xa[i];
      }
    }
    b = c;
    h = 0;
    for (i = 1; i <= b; i++) {
      c = 0;
      for (m = 1; m <= b; m++) {
        if ((m != i) && ((xa[m].r > xa[i].r) ||
                         ((xa[m].r == xa[i].r) && (xa[m].s > xa[i].s)))) {
          c++;
          xb[c].r = xa[m].r - xa[i].r;
          xb[c].s = xa[m].s - xa[i].s;
        }
      }
      if (c > 1) {
        sort(xb + 1, xb + c + 1, sx2);
        for (p = 1; p <= c; p++) {
          // printf("%d %d %d %d\n",i,p,xb[p].r,xb[p].s);
          for (q = 1; q <= c; q++) {
            w[q][p] = -1;
          }
        }
        for (p = 2; p <= c; p++) {
          for (q = 1; q < p; q++) {
            d = mj(xb[q], xb[p]);
            // printf("1---%d %d %d\n",p,q,d);
            for (o = q + 1; o < p; o++) {
              // printf("%d\n",o);
              if (pd(xb[q], xb[p], xb[o]) == 0) {
                d = 0;
                o = p + 10;
              }
            }
            // printf("2---%d\n",d);
            if (d > 0) {
              w[q][p] = d;
              if (xb[q - 1].s * xb[q].r != xb[q - 1].r * xb[q].s) {
                for (o = 1; o < q; o++) {
                  // printf("pd %d %d %d\n",o,q,p);
                  if (pd(xb[o], xb[p], xb[q])) ma(w[q][p], d + w[o][q]);
                }
              }
              ma(h, w[q][p]);
              // printf("%d %d %d %d %d\n",p,q,d,w[q][p],h);
            }
          }
        }
      }
    }
    printf("%.1lf\n", 0.5 * h);
  }
}