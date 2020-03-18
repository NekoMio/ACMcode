#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 55
using namespace std;
int T, m, n, Q;
int f[101][N][N];
int F[101][N][N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    memset(F, 0x3f, sizeof(F));
    for (int i = 1; i <= m; i++) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      if (z < f[1][x][y]) f[1][x][y] = z;
    }
    scanf("%d", &Q);
    for (int i = 2; i <= 100; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          for (int l = 1; l <= n; l++) {
            f[i][k][l] = min(f[i][k][l], f[i - 1][k][j] + f[1][j][l]);
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) F[1][i][j] = f[100][i][j];
    }
    for (int i = 2; i <= 100; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          for (int l = 1; l <= n; l++) {
            F[i][k][l] = min(F[i][k][l], F[i - 1][k][j] + F[1][j][l]);
          }
        }
      }
    }
    for (int i = 99; i; i--) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          f[i][j][k] = min(f[i][j][k], f[i + 1][j][k]);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          F[100][j][k] = min(F[100][j][k], F[100][j][i] + f[1][i][k]);
        }
      }
    }
    for (int i = 99; i; i--) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          F[i][j][k] = min(F[i][j][k], F[i + 1][j][k]);
          for (int l = 1; l <= n; l++) {
            F[i][j][k] = min(F[i][j][k], F[i][j][l] + f[1][l][k]);
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        f[100][i][j] = min(f[100][i][j], F[1][i][j]);
      }
    }
    for (int i = 99; i; i--) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          f[i][j][k] = min(f[i][j][k], f[i + 1][j][k]);
        }
      }
    }
    for (int i = 1; i <= Q; i++) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      int ans = 0x7fffffff;
      if ((z / 100) && (z % 100))
        for (int j = 1; j <= n; j++)
          ans = min(ans, F[z / 100][x][j] + f[z % 100][j][y]);
      else if (z / 100)
        ans = F[z / 100][x][y];
      else
        ans = f[z][x][y];
      if (ans > 1e8) ans = -1;
      printf("%d\n", ans);
    }
  }
  return 0;
}
/*
2
3 3
1 2 1
2 3 10
3 1 100
3
1 1 101
1 2 1
1 3 1
2 1
1 2 1
1
2 1 1
*/