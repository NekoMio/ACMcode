#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int r, s, t;
};

int a, b, c, d, e, f, g, i, m, n;
int xa[3000000] = {0}, xb[3000000] = {0};
int za[300000] = {0}, zb[300000] = {0}, zc[300000] = {0};
xl w[300000] = {0};

bool sx(xl j, xl k) {
  if (j.r != k.r) return j.r < k.r;
  return j.s < k.s;
}

void ma(int &j, int k) {
  if (j < k) j = k;
}

int maa(int &j, int k) {
  if (j < k) return k;
  return j;
}

void xf(int j) {
  xa[2 * j] += xb[j];
  xb[2 * j] += xb[j];
  xa[2 * j + 1] += xb[j];
  xb[2 * j + 1] += xb[j];
  xb[j] = 0;
}

void tj(int j, int k, int l, int p, int o) {
  int q = (k + l) / 2;
  if ((za[p] <= k) && (l <= zb[p])) {
    xa[j] += o;
    xb[j] += o;
  } else {
    xf(j);
    if (za[p] <= q) tj(2 * j, k, q, p, o);
    if (q < zb[p]) tj(2 * j + 1, q + 1, l, p, o);
    xa[j] = maa(xa[2 * j], xa[2 * j + 1]);
  }
  // printf("1--------%d %d %d\n",k,l,xa[j]);
}

void bl(int j, int k, int l) {
  int q = (k + l) / 2;
  if (k == l)
    zc[k] = xa[j];
  else {
    xf(j);
    bl(2 * j, k, q);
    bl(2 * j + 1, q + 1, l);
  }
}

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%d%d%d%d", &b, &c, &d, &e);
    w[2 * i - 1].r = c;
    w[2 * i - 1].s = 1;
    w[2 * i - 1].t = i;
    w[2 * i].r = e;
    w[2 * i].s = 0;
    w[2 * i].t = i;
  }
  sort(w + 1, w + 2 * a + 1, sx);
  c = w[1].r;
  d = 1;
  for (i = 1; i <= 2 * a; i++) {
    if (c != w[i].r) {
      d++;
      c = w[i].r;
    }
    if (w[i].s == 0)
      za[w[i].t] = w[i].r = d;
    else
      zb[w[i].t] = w[i].r = d;
    // printf("%d %d %d %d\n",i,w[i].r,w[i].s,w[i].t);
  }
  for (i = 1; i <= a; i++) {
    tj(1, 1, d, i, 1);
  }
  bl(1, 1, d);
  w[2 * a + 1].r = d + 1;
  m = 1;
  c = 0;
  for (i = 1; i <= d; i++) {
    while ((w[m].r == i) && (w[m].s == 0)) {
      tj(1, 1, d, w[m].t, -1);
      m++;
    }
    ma(c, xa[1] + zc[i]);
    // printf("%d %d %d %d\n",i,m,xa[1],zc[i]);
    while ((w[m].r == i) && (w[m].s == 1)) {
      tj(1, 1, d, w[m].t, 1);
      m++;
    }
  }
  printf("%d\n", c);
}