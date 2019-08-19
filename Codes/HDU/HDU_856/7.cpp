#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 100005
using namespace std;
int n, T, a[N];
struct ro {
  int to, next;
} road[N * 2];
int zz;
void build(int x, int y) {
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  a[x] = zz;
}
int fa[N];
int f[3][N][2], F[2][N][2];
void update(int x, int y, int z) {
  if (y > f[0][x][0]) {
    f[2][x][0] = f[1][x][0];
    f[2][x][1] = f[1][x][1];

    f[1][x][0] = f[0][x][0];
    f[1][x][1] = f[0][x][1];

    f[0][x][0] = y;
    f[0][x][1] = z;
  } else if (y > f[1][x][0]) {
    f[2][x][0] = f[1][x][0];
    f[2][x][1] = f[1][x][1];

    f[1][x][0] = y;
    f[1][x][1] = z;
  } else if (y > f[2][x][0]) {
    f[2][x][0] = y;
    f[2][x][1] = z;
  }
}
void update2(int x, int y, int z) {
  if (y > F[0][x][0]) {
    F[1][x][0] = F[0][x][0];
    F[1][x][1] = F[0][x][1];

    F[0][x][0] = y;
    F[0][x][1] = z;
  } else if (y > F[1][x][0]) {
    F[1][x][0] = y;
    F[1][x][1] = z;
  }
}
void dfs1(int x) {
  f[0][x][0] = -1;
  f[1][x][0] = -1;
  f[2][x][0] = -1;

  f[0][x][1] = -1;
  f[1][x][1] = -1;
  f[2][x][1] = -1;

  F[0][x][0] = -1;
  F[0][x][1] = -1;
  F[1][x][0] = -1;
  F[1][x][1] = -1;
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    fa[y] = x;
    dfs1(y);
    update(x, f[0][y][0] + 1, i / 2);
    int mx = F[0][y][0];
    if (f[1][y][0] == -1)
      mx = max(mx, f[0][y][0]);
    else
      mx = max(f[0][y][0] + f[1][y][0] - 1, mx);
    update2(x, mx, y);
  }
  if (f[0][x][0] == -1) f[0][x][0] = 1;
}
void dfs2(int x) {
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    if (i / 2 == f[0][x][1]) {
      if (f[1][x][0] != -1)
        update(y, f[1][x][0] + 1, i / 2);
      else
        update(y, 2, i / 2);
    } else {
      if (f[0][x][0] != -1)
        update(y, f[0][x][0] + 1, i / 2);
      else
        update(y, 2, i / 2);
    }
    int mx = 0;
    if (y == F[0][x][1]) {
      if (F[1][x][0] == -1)
        mx = 1;
      else
        mx = F[1][x][0];
    } else {
      if (F[0][x][0] == -1)
        mx = 1;
      else
        mx = F[0][x][0];
    }

    if (f[0][x][1] == i / 2) {
      if (f[1][x][0] == -1)
        mx = max(mx, 1);
      else if (f[2][x][0] == -1)
        mx = max(mx, f[1][x][0]);
      else
        mx = max(mx, f[1][x][0] + f[2][x][0] - 1);
    } else if (f[1][x][1] == i / 2) {
      if (f[2][x][0] == -1)
        mx = max(mx, f[0][x][0]);
      else
        mx = max(f[0][x][0] + f[2][x][0] - 1, mx);
    } else {
      if (f[0][x][0] == -1)
        mx = max(mx, 1);
      else if (f[1][x][0] == -1)
        mx = max(mx, f[0][x][0]);
      else
        mx = max(mx, f[0][x][0] + f[1][x][0] - 1);
    }
    update2(y, mx, x);
  }
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    dfs2(y);
  }
}
int A[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    zz = 1;
    memset(a, 0, sizeof(a));
    memset(fa, 0, sizeof(fa));
    memset(A, 0, sizeof(A));
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      build(x, y);
      build(y, x);
    }
    memset(F, 0, sizeof(F));
    memset(f, 0, sizeof(f));

    dfs1(1);
    //    for(int i=1;i<=n;i++) cout<<F[0][i][0]<<' '<<F[1][i][0]<<endl;
    dfs2(1);
    for (int i = 1; i < n; i++) {
      int x, y;
      x = road[i * 2].to;
      y = road[i * 2 + 1].to;
      if (fa[x] == y) swap(x, y);
      int mx1, mx2;

      if (i == f[0][y][1]) {
        if (f[1][y][0] == -1)
          mx1 = 1;
        else if (f[2][y][0] == -1)
          mx1 = f[1][y][0];
        else
          mx1 = f[1][y][0] + f[2][y][0] - 1;
      } else if (i == f[1][y][1]) {
        if (f[2][y][0] == -1)
          mx1 = f[0][y][0];
        else
          mx1 = f[0][y][0] + f[2][y][0] - 1;
      } else {
        if (f[0][y][0] == -1)
          mx1 = 1;
        else if (f[1][y][0] == -1)
          mx1 = f[0][y][0];
        else
          mx1 = f[0][y][0] + f[1][y][0] - 1;
      }
      if (x == F[0][y][1])
        mx1 = max(mx1, F[1][y][0]);
      else
        mx1 = max(mx1, F[0][y][0]);

      if (i == f[0][x][1]) {
        if (f[1][x][0] == -1)
          mx2 = 1;
        else if (f[2][x][0] == -1)
          mx2 = f[1][x][0];
        else
          mx2 = f[1][x][0] + f[2][x][0] - 1;
      } else if (i == f[1][x][1]) {
        if (f[2][x][0] == -1)
          mx2 = f[0][x][0];
        else
          mx2 = f[0][x][0] + f[2][x][0] - 1;
      } else {
        if (f[0][x][0] == -1)
          mx2 = 1;
        else if (f[1][x][0] == -1)
          mx2 = f[0][x][0];
        else
          mx2 = f[0][x][0] + f[1][x][0] - 1;
      }

      if (y == F[0][x][1])
        mx2 = max(mx2, F[1][x][0]);
      else
        mx2 = max(mx2, F[0][x][0]);
      A[mx1] = max(A[mx1], mx2);
      A[mx2] = max(A[mx2], mx1);
    }
    for (int i = n - 1; i; i--) A[i] = max(A[i], A[i + 1]);
    long long ans = 0;
    for (int i = 1; i <= n - 1; i++) ans += A[i];
    printf("%lld\n", ans);
  }
  return 0;
}
