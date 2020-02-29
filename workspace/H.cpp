#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 40
using namespace std;
double f[N][N][N][N][4][3];
struct no {
  double da, A[4];
};
bool cmp(no a, no b) { return a.da - b.da > 1e-6; }
int dl[5];
double dfs(int a, int b, int c, int d, int x, int pre) {
  //	cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<x<<' '<<pre<<endl;
  if (f[a][b][c][d][x][0] + f[a][b][c][d][x][1] + f[a][b][c][d][x][2]) {
    return f[a][b][c][d][x][pre];
  }
  if (x == 0 && !a) {
    double xx = dfs(a, b, c, d, x + 1, pre);
    for (int i = 0; i <= 2; i++) f[a][b][c][d][x][i] = f[a][b][c][d][x + 1][i];
    return xx;
  }
  if (x == 1 && !b) {
    double xx = dfs(a, b, c, d, x + 1, pre);
    for (int i = 0; i <= 2; i++) f[a][b][c][d][x][i] = f[a][b][c][d][x + 1][i];
    return xx;
  }
  if (x == 2 && !c) {
    double xx = dfs(a, b, c, d, x + 1, pre);
    for (int i = 0; i <= 2; i++) f[a][b][c][d][x][i] = f[a][b][c][d][x + 1][i];
    return xx;
  }
  if (x == 3 && !d) {
    double xx = dfs(a, b, c, d, 0, pre);
    for (int i = 0; i <= 2; i++) f[a][b][c][d][x][i] = f[a][b][c][d][0][i];
    return xx;
  }
  if (x == 0 || x == 1) {
    double xx, yy;
    if (c == 0)
      xx = -1;
    else
      xx = dfs(a, b, c - 1, d, x + 1, 0);

    if (d == 0)
      yy = -1;
    else
      yy = dfs(a, b, c, d - 1, x + 1, 0);

    if (xx - yy > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = f[a][b][c - 1][d][x + 1][i];
      }
    } else if (yy - xx > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = f[a][b][c][d - 1][x + 1][i];
      }
    } else {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] =
            (f[a][b][c][d - 1][x + 1][i] + f[a][b][c - 1][d][x + 1][i]) * 0.5;
      }
    }
  } else if (x == 2) {
    no A[3];
    if (a == 0) {
      A[0].da = -1;
    } else {
      A[0].da = dfs(a - 1, b, c, d, x + 1, 1);
      for (int i = 0; i < 3; i++) A[0].A[i] = f[a - 1][b][c][d][x + 1][i];
    }
    if (b == 0) {
      A[1].da = -1;
    } else {
      A[1].da = dfs(a, b - 1, c, d, x + 1, 1);
      for (int i = 0; i < 3; i++) A[1].A[i] = f[a][b - 1][c][d][x + 1][i];
    }
    if (d == 0) {
      A[2].da = -1;
    } else {
      A[2].da = dfs(a, b, c, d - 1, x + 1, 1);
      for (int i = 0; i < 3; i++) A[2].A[i] = f[a][b][c][d - 1][x + 1][i];
    }

    sort(A, A + 3, cmp);
    if (A[0].da - A[1].da > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = A[0].A[i];
      }
    } else if (A[0].da - A[2].da > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = (A[0].A[i] + A[1].A[i]) * 0.5;
      }
    } else {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = (A[0].A[i] + A[1].A[i] + A[2].A[i]);
        f[a][b][c][d][x][i] /= 3.0;
      }
    }
  } else if (x == 3) {
    no A[3];
    if (a == 0) {
      A[0].da = -1;
    } else {
      A[0].da = dfs(a - 1, b, c, d, 0, 2);
      for (int i = 0; i < 3; i++) A[0].A[i] = f[a - 1][b][c][d][0][i];
    }
    if (b == 0) {
      A[1].da = -1;
    } else {
      A[1].da = dfs(a, b - 1, c, d, 0, 2);
      for (int i = 0; i < 3; i++) A[1].A[i] = f[a][b - 1][c][d][0][i];
    }
    if (c == 0) {
      A[2].da = -1;
    } else {
      A[2].da = dfs(a, b, c - 1, d, 0, 2);
      for (int i = 0; i < 3; i++) A[2].A[i] = f[a][b][c - 1][d][0][i];
    }
    sort(A, A + 3, cmp);
    if (A[0].da - A[1].da > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = A[0].A[i];
      }
    } else if (A[0].da - A[2].da > 1e-6) {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = (A[0].A[i] + A[1].A[i]) * 0.5;
      }
    } else {
      for (int i = 0; i < 3; i++) {
        f[a][b][c][d][x][i] = (A[0].A[i] + A[1].A[i] + A[2].A[i]);
        f[a][b][c][d][x][i] /= 3.0;
      }
    }
  }
  if (f[a][b][c][d][x][0] + f[a][b][c][d][x][1] + f[a][b][c][d][x][2] < 0.9) {
    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << x << endl;
  }
  return f[a][b][c][d][x][pre];
}
void init() {
  memset(f, 0, sizeof(f));
  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < 40; j++) {
      for (int k = 0; k < 40; k++) {
        f[j][k][0][0][i][0] = 1;
      }
    }
    for (int j = 0; j < 40; j++) {
      for (int k = 0; k < 40; k++) {
        for (int l = 0; l < 40; l++) {
          f[0][j][k][l][i][1] = 1;
        }
      }
    }
    for (int j = 1; j < 40; j++) f[0][0][0][j][i][2] = 1;
  }
}
int main() {
  init();
  dl[0] = dl[1] = 0;
  dl[2] = 1;
  dl[3] = 2;
  int T;
  scanf("%d", &T);

  while (T--) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    dfs(a, b, c, d, 0, 0);
    printf("%.6f %.6f %.6f\n", f[a][b][c][d][0][0], f[a][b][c][d][0][1],
           f[a][b][c][d][0][2]);
  }
  return 0;
}
/*
4
1 1 1 1
1 0 1 1
1 1 1 2
1
2 1 2 6
*/
