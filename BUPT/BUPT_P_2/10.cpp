#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 2005
using namespace std;
int T, n, m, K;
int zz, a[N];
struct ro {
  int to, next;
  long long l;
} road[N * N];
void build(int x, int y, int z) {
  if (x == y) return;
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  road[zz].l = z;
  a[x] = zz;
}
int S;
long long dis[N];
bool rd[N];
int cnt[N];
queue<int> q1;
bool spfa() {
  memset(cnt, 0, sizeof(cnt));
  while (!q1.empty()) q1.pop();
  q1.push(S);
  memset(dis, 0x3f, sizeof(dis));
  memset(rd, 0, sizeof(rd));
  rd[S] = 1;
  dis[S] = 0;
  cnt[S] = 1;
  while (!q1.empty()) {
    int x = q1.front();
    q1.pop();
    rd[x] = 0;
    for (int i = a[x]; i; i = road[i].next) {
      int y = road[i].to;
      if (dis[y] > dis[x] + road[i].l) {
        dis[y] = dis[x] + road[i].l;
        if (!rd[y]) {
          rd[y] = 1;
          q1.push(y);
          cnt[y]++;
          if (cnt[y] > n) {
            return 0;
          }
        }
      }
    }
  }
  return 1;
}
int main() {
  scanf("%d", &T);
  int js = 0;
  while (T--) {
    js++;
    scanf("%d%d%d", &n, &m, &K);
    zz = 0;
    S = n + 1;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= m; i++) {
      int aa, bb, cc, dd;
      scanf("%d%d%d%d", &aa, &bb, &cc, &dd);
      if (aa == bb && cc == dd) {
        build(aa, cc, K);
        build(cc, aa, -K);
      } else {
        if (aa == cc && bb == dd) {
          build(dd, aa, -K - 1);
        } else {
          build(dd, aa, -K - 1);
          build(bb, cc, K - 1);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      build(S, i, 0);
      if (i != n) build(i + 1, i, -1);
    }
    if (!spfa()) {
      printf("Case #%d: IMPOSSIBLE\n", js);
    } else {
      printf("Case #%d:", js);
      for (int i = 2; i <= n; i++) {
        printf(" %d", dis[i] - dis[i - 1]);
      }
      printf("\n");
    }
  }
  return 0;
}
/*
1
3 3 2
1 1 1 2
2 2 2 3
2 3 3 3
*/