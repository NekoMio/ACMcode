#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int r, s, t;
};

int a, b, c, d, e, f, g, m, n, T;
int xa[400000] = {0}, xb[400000] = {0};
int wa[400000] = {0}, wb[400000] = {0};
xl za[400000], zb[400000] = {0}, zc[400000] = {0};

bool sx(xl j, xl k) {
  if (j.r != k.r) return j.r < k.r;
  return j.s < k.s;
}

void sc(int j, int k) {
  int r, s, t;
  // printf("%d %d\n",j,k);
  xa[j] = 1;
  r = xb[j];
  s = wa[r];
  while (r > 0) {
    if (r / 2 != k) {
      if (xa[s] == 0) {
        sc(s, r / 2);
        // printf("%d %d %d\n",j,r/2,b);
        zc[r / 2].t = b;
      } else {
        if (b == 0) {
          b = r / 2;
          za[b].t = s;
        }
        zc[r / 2].t = b;
      }
    }
    r = wb[r];
    s = wa[r];
  }
  if (b == 0) {
    b = k;
    za[b].t = j;
  }
}

int main() {
  long long i, j, k;
  scanf("%d", &T);
  for (k = 1; k <= T; k++) {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
      scanf("%d%d", &a, &b);
      zc[i].r = a;
      zc[i].s = b;
      zc[i].t = i;
      za[i].t = 0;
      zb[2 * i - 1].r = a;
      zb[2 * i - 1].s = i;
      zb[2 * i - 1].t = 1;
      zb[2 * i].r = b;
      zb[2 * i].s = i;
      zb[2 * i].t = 0;
    }
    sort(zb + 1, zb + 2 * n + 1, sx);
    m = 0;
    for (i = 1; i <= 2 * n; i++) {
      if ((i == 1) || (zb[i - 1].r != zb[i].r)) m++;
      // printf("1----%d %d %d\n",zb[i].r,zb[i].s,m);
      if (zb[i].t)
        za[zb[i].s].r = m;
      else
        za[zb[i].s].s = m;
    }
    for (i = 1; i <= m; i++) {
      xa[i] = xb[i] = 0;
    }
    for (i = 1; i <= n; i++) {
      // printf("2----%d %d %d\n",i,za[i].r,za[i].s);
      wa[2 * i + 1] = za[i].r;
      wb[2 * i + 1] = xb[za[i].s];
      xb[za[i].s] = 2 * i + 1;
      wa[2 * i] = za[i].s;
      wb[2 * i] = xb[za[i].r];
      xb[za[i].r] = 2 * i;
    }
    for (i = 1; i <= m; i++) {
      b = 0;
      if (xa[i] == 0) sc(i, 0);
    }
    a = 0;
    b = 0;
    for (i = 1; i <= n; i++) {
      if (zc[i].t == i) a++;
    }
    printf("%d\n", a - 1);
    a = 0;
    for (i = 1; i <= n; i++) {
      if (zc[i].t == i) {
        a++;
        if (a != 1) {
          if (za[i].t == za[i].r)
            printf("%lld %d %d\n", i, zc[i].r, b);
          else
            printf("%lld %d %d\n", i, zc[i].s, b);
        } else
          b = zc[i].r;
      }
    }
  }
}
