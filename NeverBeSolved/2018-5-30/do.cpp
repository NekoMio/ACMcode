#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 100005;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
int du[MAXN], a[MAXN], f[MAXN], dis[MAXN];
bool vis[MAXN];
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
void DFS1(int rt, int fa) {
  if (vis[rt]) f[rt] = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS1(v[i].END, rt);
    f[rt] = min(f[rt], f[v[i].END] + 1);
  }
}
void DFS2(int rt, int fa, int val) {
  f[rt] = min(f[rt], val);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS2(v[i].END, rt, f[rt] + 1);
  }
}
void DFS(int rt, int fa) {
  dis[rt] = dis[fa] + 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
  }
}
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), q = read();
  bool flag = 1;
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
    du[a]++, du[b]++;
    if (du[a] > 2 || du[b] > 2) flag = 0;
  }
  if (flag) {
    int Maxdep = 0;
    for (int i = 1; i <= n; ++i) {
      if (du[i] == 1) {
        DFS(i, 0);
        break;
      }
    }
    for (int i = 1; i <= n; ++i) Maxdep = max(Maxdep, dis[i]);
    while (q--) {
      int k = read();
      for (int i = 1; i <= k; ++i)
        a[i] = read();
      sort(a + 1, a + k + 1, [](const int &x, const int &y) {
        return dis[x] < dis[y];
      });
      int Max = dis[a[1]] - 1;
      for (int i = 2; i <= k; ++i) {
        Max = max(Max, (dis[a[i]] - dis[a[i - 1]]) / 2);
      }
      Max = max(Max, Maxdep - dis[a[k]]);
      printf ("%d\n", Max);
    }
  } else {
    while (q--) {
      int k = read();
      for (int i = 1; i <= n; ++i) f[i] = 0x3f3f3f3f, vis[i] = 0;
      for (int i = 1; i <= k; ++i) vis[read()] = 1;
      DFS1(1, 0);
      DFS2(1, 0, 0x3f3f3f3f);
      int Max = 0;
      for (int i = 1; i <= n; ++i) Max = max(Max, f[i]);
      printf ("%d\n", Max);
    }
  }
}
