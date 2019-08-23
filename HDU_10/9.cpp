#include <cstdio>
#include <cstring>

int a, b, c, d, e, f, g, i, m, n;
int x[3000][3000] = {0}, w[3000][3000] = {0};

void sc(int j, int k) {
  x[j][k] = 10;
  w[j][k] = -10;
  // printf("1--%d %d\n",j,k);
  f++;
  x[j - 1][k]++;
  if ((j > 1) && (x[j - 1][k] * w[j - 1][k] > 0)) sc(j - 1, k);
  x[j + 1][k]++;
  if ((j < b) && (x[j + 1][k] * w[j + 1][k] > 0)) sc(j + 1, k);
  w[j][k - 1]++;
  if ((k > 1) && (x[j][k - 1] * w[j][k - 1] > 0)) sc(j, k - 1);
  w[j][k + 1]++;
  if ((k < c) && (x[j][k + 1] * w[j][k + 1] > 0)) sc(j, k + 1);
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d%d%d", &b, &c, &g);
    for (i = 1; i <= b; i++) {
      for (m = 1; m <= c; m++) {
        x[i][m] = w[i][m] = 0;
      }
    }
    for (m = 1; m <= g; m++) {
      scanf("%d%d", &d, &e);
      f = 0;
      if (x[d][e] * w[d][e] >= 0) sc(d, e);
      printf("%d\n", f);
    }
  }
}
