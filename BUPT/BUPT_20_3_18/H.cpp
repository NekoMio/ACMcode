#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 100005
using namespace std;
int T, n, zz, a[N];
struct ro {
  int to, next;
} road[N * 2];
void build(int x, int y) {
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  a[x] = zz;
}
int A[N], B[N], fa[N];
long long F[N][2];
int ans[N];
bool cmp1(int x, int y) { return F[x][1] > F[y][1]; }
bool cmp2(int x, int y) { return F[x][0] < F[y][0]; }
bool cmp3(int x, int y) { return F[x][0] + F[x][1] > F[y][0] + F[y][1]; }
void dfs(int x) {
  F[x][0] = A[x];
  F[x][1] = B[x] - A[x];
  int cnt = 0;
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    fa[y] = x;
    dfs(y);
    F[x][1] += F[y][1];
    cnt++;
    ans[cnt] = y;
  }
  if (!cnt) return;
  sort(ans + 1, ans + cnt + 1, cmp1);
  int bj = 0;
  for (int i = 1; i <= cnt; i++) {
    if (F[ans[i]][1] > 0) {
      bj = i;
    }
  }
  long long nw = B[x];
  if (bj) {
    sort(ans + 1, ans + bj + 1, cmp2);
    for (int i = 1; i <= bj; i++) {
      if (F[ans[i]][0] > nw) {
        F[x][0] += F[ans[i]][0] - nw;
        nw = F[ans[i]][0];
      }
      nw += F[ans[i]][1];
    }
  }
  if (bj != cnt) {
    sort(ans + bj + 1, ans + cnt + 1, cmp3);

    for (int i = bj + 1; i <= cnt; i++) {
      if (F[ans[i]][0] > nw) {
        F[x][0] += F[ans[i]][0] - nw;
        nw = F[ans[i]][0];
      }
      nw += F[ans[i]][1];
    }
  }
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
      scanf("%d%d", &A[i], &B[i]);
      a[i] = 0;
      fa[i] = 0;
      F[i][0] = F[i][1] = 0;
    }
    F[1][0] = F[1][1] = 0;
    a[1] = 0;
    zz = 0;
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      build(x, y);
      build(y, x);
    }
    dfs(1);

    printf("%lld\n", F[1][0]);
  }
  return 0;
}
/*
2
4
2 6
5 4
6 2
1 2
2 3
3 4
4
2 6
5 4
6 2
1 2
2 3
3 4
*/