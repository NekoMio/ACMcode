#include <cstdio>
#include <cstring>

int a, b, c, d, e, f, g, i, m, n, x, h, h1, h2, h3, h4;

void ma(int &j, int k) {
  if (j < k) j = k;
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    h = 0;
    h1 = 0;
    h2 = 0;
    h3 = 0;
    h4 = 0;
    for (i = 1; i <= b; i++) {
      scanf("%d", &x);
      if (x % 10 > 0) c = -1;
      if (x % 100 == 0) ma(h4, x);
      ma(h, x);
      ma(g, x / 100);
      ma(h1, x % 100);
      if (x == 10) h3 = 1;
      if (x % 100 == 30) h3 = 1;
      if (x % 100 == 80) h3 = 1;
      if (x % 20 > 0) h2 = 1;
      if (x % 100 >= 50) d = 1;
      if (x % 50 == 10) e = 1;
      if (x % 50 == 20) ma(f, 1);
      if (x % 50 == 30) ma(f, 1);
      if (x % 50 == 30) e = 1;
      if (x % 50 == 40) f = 2;
    }
    if ((h2 == 0) && (h1 < 80) && (d + e + f >= 3)) {
      d = e = 0;
      f = h1 / 20;
    }
    if ((d + e + f == 4) && (h % 100 == 0))
      g--;
    else {
      if ((e + f == 3) && (h1 == 50))
        d--;
      else {
        if ((h % 100 == 10) && (d + e + f == 4) && (h3 == 0) &&
            (h4 + 10 != h)) {
          g--;
          d = 0;
          f = 3;
          e = 1;
        }
      }
    }
    // printf("%d %d %d %d\n",e,f,h,h1);
    if (c == -1)
      printf("-1\n");
    else
      printf("%d\n", g + d + e + f);
  }
}