#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  double x, y;
};

int a, b, c, d, e, f, g, i, m, n;
int w[100000] = {0};
double ha, hb;
double eq = 0.0000001;
xl x[100000], z;

bool sx(xl j, xl k) {
  if ((j.x == 0) && (k.x == 0)) return j.y > k.y;
  if (j.x == 0) return 0;
  if (k.x == 0) return 1;
  if (j.x * k.y != j.y * k.x) return j.x * k.y > j.y * k.x;
  return j.x < k.x;
}

double mia(xl j, xl k, xl l) {
  return (j.x - l.x) * (k.y - l.y) - (j.y - l.y) * (k.x - l.x);
}

int qj(xl j, xl k, xl l) {
  double h = mia(j, k, l);
  if (h > eq) return 1;
  if (h < -eq) return 2;
  return 0;
}

void ma(double &j, double k) {
  if (k < 0) k = -k;
  if (j < k) j = k;
}

int main() {
  int j, k, l;
  scanf("%d", &n);
  scanf("%lf%lf", &x[1].x, &x[1].y);
  z = x[1];
  for (i = 2; i <= n; i++) {
    scanf("%lf%lf", &x[i].x, &x[i].y);
    if (z.x > x[i].x)
      z = x[i];
    else {
      if ((z.x == x[i].x) && (z.y > x[i].y)) z = x[i];
    }
  }
  for (i = 1; i <= n; i++) {
    x[i].x -= z.x;
    x[i].y -= z.y;
  }
  sort(x + 1, x + n + 1, sx);
  a = 1;
  w[1] = 0;
  for (i = 1; i <= n; i++) {
    b = 0;
    for (j = 0; j <= n; j++) {
      if ((j != i) && (j != w[a])) b |= qj(x[j], x[i], x[w[a]]);
    }
    // printf("%d %d %lf %lf\n",i,b,x[i].x,x[i].y);
    if (b < 3) {
      a++;
      w[a] = i;
    }
  }
  ha = 0;
  for (i = 1; i <= a; i++) {
    // printf("%d\n",w[i]);
    k = i + 2;
    for (j = i + 1; j <= a; j++) {
      while ((k < a) && (mia(x[w[i]], x[w[j]], x[w[k]]) <=
                         mia(x[w[i]], x[w[j]], x[w[k + 1]])))
        k++;
      ma(ha, mia(x[w[i]], x[w[j]], x[w[k]]));
      // printf("%d %d %d %lf\n",w[i],w[j],w[k],mia(x[w[i]],x[w[j]],x[w[k]]));
    }
  }
  printf("%.6lf\n", ha * 0.5);
}