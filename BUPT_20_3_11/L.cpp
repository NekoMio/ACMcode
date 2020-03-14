#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  int r, s, t;
};

int a, b, c, d, e, f, g, i, m, n, ha, hb, hc;
int x[4010][4010] = {0};
int z[4010] = {0};
xl wa[4010], wb[5000000];

bool sx(xl j, xl k) {
  if (j.s != k.s) return j.s < k.s;
  return j.r > k.r;
}

int main() {
  scanf("%d%d%d%d", &a, &b, &c, &d);
  e = 0;
  f = 0;
  for (i = 1; i <= a; i++) {
    scanf("%d", &wa[i].s);
    e += wa[i].s;
    wa[i].s /= c;
    wa[i].r = i;
  }
  make_heap(wa + 1, wa + a + 1, sx);
  for (i = 1; i <= b; i++) {
    scanf("%d", &z[i]);
    f += z[i];
  }
  if (e >= f) {
    e = 0;
    i = 1;
  } else {
    e = 1;
    i = b + 10;
  }
  ha = hb = 1;
  hc = 0;
  f = 0;
  m = a;
  for (; i <= b; i++) {
    while ((hb <= hc) && ((wb[hb].t + c) == i)) {
      hb++;
      f--;
    }
    while ((ha < hb) && (wb[ha].t + c + d <= i)) {
      if (wb[ha].s > 0) {
        m++;
        wa[m] = wb[ha];
        push_heap(wa + 1, wa + m + 1, sx);
      }
      ha++;
    }

    while ((f < z[i]) && (m > 0)) {
      // printf("%d %d %d %d %d %d\n",i,f,m,wa[m].r,wa[m].s,wa[m].t);
      hc++;
      wb[hc] = wa[1];
      x[wb[hc].r][0]++;
      wb[hc].s--;
      wb[hc].t = x[wb[hc].r][x[wb[hc].r][0]] = i;
      pop_heap(wa + 1, wa + m + 1, sx);
      m--;
      f++;
    }
    if (f != z[i]) {
      e = 1;
      i = b + 10;
    }
  }
  if (e == 1)
    printf("-1\n");
  else {
    printf("1\n");
    for (i = 1; i <= a; i++) {
      e = x[i][0];
      for (m = 1; m <= e; m++) {
        printf("%d ", x[i][m]);
      }
      printf("\n");
    }
  }
}