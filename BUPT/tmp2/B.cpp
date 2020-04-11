#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#define N 400005
using namespace std;
int n, m, T;
int zz, a[N];
struct ro {
  int to, next;
} road[N * 4];
void build(int x, int y) {
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  a[x] = zz;
}
int L[N], D[N], bel[N], zz2, top, st[N], zz3;
bool rd[N];
int dfn[N], low[N];
void dfs(int x) {
  zz2++;
  dfn[x] = low[x] = zz2;
  rd[x] = 1;
  top++;
  st[top] = x;
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (!dfn[y]) {
      dfs(y);
      low[x] = min(low[x], low[y]);
    } else if (rd[y]) {
      low[x] = min(low[x], dfn[y]);
    }
  }
  if (dfn[x] == low[x]) {
    int v;
    zz3++;
    do {
      v = st[top];
      bel[v] = zz3;
      top--;
      rd[v] = 0;
    } while (dfn[v] != low[v]);
  }
}
int fa[N], mx[N], mn[N];
int find(int x) {
  if (fa[x] == x) return x;
  return fa[x] = find(fa[x]);
}
void hb(int x, int y) {
  int xx = find(x), yy = find(y);
  if (xx != yy) {
    fa[yy] = xx;
    mx[xx] = max(mx[xx], mx[yy]);
    mn[xx] = min(mn[xx], mn[yy]);
  }
}
int dl[N], dl2[N];
struct no {
  int mx, mn;
  int bh;
  bool friend operator<(const no &A, const no &B) { return A.mx < B.mx; }
} node[N * 2];
int zz4;
bool cmp(no a, no b) { return a.mn < b.mn; }
long long Mx[N];
priority_queue<no> q1;
int main() {
  scanf("%d", &T);
  int cc = 0;
  while (T--) {
    cc++;
    scanf("%d%d", &n, &m);
    zz = 0;
    zz4 = 0;
    top = 0;
    memset(a, 0, sizeof(a));
    zz2 = zz3 = 0;
    memset(bel, 0, sizeof(bel));
    memset(st, 0, sizeof(st));
    memset(rd, 0, sizeof(rd));
    memset(dl2, 0, sizeof(dl2));
    memset(dl, 0, sizeof(dl));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(Mx, 0, sizeof(Mx));
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      build(x, y + n);
      build(x + n, y);
      build(y + n, x);
      build(y, x + n);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &L[i], &D[i]);
    }
    for (int i = 1; i <= n * 2; i++) {
      if (!dfn[i]) {
        dfs(i);
      }
    }
    bool yx = 0;
    for (int i = 1; i <= n; i++) {
      if (bel[i] == bel[i + n]) {
        printf("Case %d: IMPOSSIBLE\n", cc);
        yx = 1;
        break;
      }
    }
    if (yx) continue;
    for (int i = 1; i <= n * 2; i++) fa[i] = i;
    for (int i = 1; i <= n; i++)
      mx[i] = mn[i] = L[i], mx[i + n] = mn[i + n] = D[i];
    for (int i = 1; i <= n * 2; i++) {
      for (int j = a[i]; j; j = road[j].next) {
        int y = road[j].to;
        hb(i, y);
      }
    }
    for (int i = 1; i <= n * 2; i++) {
      if (find(i) == i) {
        zz4++;
        dl2[i] = zz4;
        node[zz4].bh = zz4;
        node[zz4].mx = mx[i];
        node[zz4].mn = mn[i];
      }
    }

    for (int i = 1; i <= n * 2; i++) {
      if (find(i) == i) {
        if (i <= n) dl[dl2[i]] = dl2[find(i + n)];
        if (i > n) dl[dl2[i]] = dl2[find(i - n)];
      }
    }

    sort(node + 1, node + zz4 + 1, cmp);
    memset(rd, 0, sizeof(rd));
    while (!q1.empty()) q1.pop();
    Mx[zz4] = node[zz4].mx;
    rd[node[zz4].bh] = 1;
    q1.push(node[zz4]);
    for (int i = zz4 - 1; i; i--) {
      rd[node[i].bh] = 1;
      int y = dl[node[i].bh];
      if (rd[y]) {
        if (node[i].mx < node[y].mx) {
          if (q1.top().bh == y) {
            q1.pop();
            q1.push(node[i]);
          }
        }
      } else {
        q1.push(node[i]);
      }
      Mx[i] = q1.top().mx;
    }
    memset(rd, 0, sizeof(rd));
    long long ans = 1e10;
    for (int i = 1; i <= zz4; i++) {
      rd[node[i].bh] = 1;

      ans = min(ans, Mx[i] - node[i].mn);
      if (rd[dl[node[i].bh]]) {
        break;
      }
    }
    printf("Case %d: %lld\n", cc, ans);
  }
  return 0;
}
/*
1
3 1
1 2
1 2
3 4
5 6

4 3
1 2
2 3
1 3
1 2
3 4
5 6
7 8
2 0
2 1
3 5
*/