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
const int MAXN = 2e4 + 5;
struct Point {
  long long x, y;
  long long operator * (const Point &a) const {
    return x * a.y - y * a.x;
  }
}a[MAXN], c;
struct edge {
  int S, END, next, cap, v;
}v[5000005];
int first[MAXN], p, head[MAXN];
void add(int a, int b, int f, int c) {
  cerr << a << " " << b << " " << f << " " << c << endl;
  v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c, first[a] = p++;
  v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v =-c, first[b] = p++;
}
int dis[MAXN];
bool vis[MAXN];
int q[20000005];
bool Spfa(int S, int T) {
  memset (dis, 0x3f, sizeof (dis));
  dis[S] = 0;
  int h = 1, t = 0;
  q[++t] = S;
  while (h <= t) {
    int k = q[h++];
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] > dis[k] + v[i].v && v[i].cap) {
        dis[v[i].END] = dis[k] + v[i].v;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          q[++t] = v[i].END;
        }
      }
    }
  }
  return dis[T] != 0x3f3f3f3f;
}
int DFS(int S, int T, int a, int &ans) {
  if (S == T) return a;
  int flow = 0, f;
  vis[S] = 1;
  for (int i = first[S]; i != -1; i = v[i].next) {
    if ((v[i].cap) && (!vis[v[i].END]) && (dis[v[i].END] == dis[S] + v[i].v) && (f = DFS(v[i].END, T, min(v[i].cap, a), ans))) {
      v[i].cap -= f;
      v[i ^ 1].cap += f;
      flow += f;
      a -= f;
      ans = ans + f * v[i].v;
      if (!a) break;
    }
  }
  vis[S] = 0;
  if (!flow) dis[S] = 0x3f3f3f3f;
  return flow;
}
int Min_Profit(int S, int T) {
  int ans = 0;
  while (Spfa(S, T)) {
    DFS(S, T, 0x3f3f3f3f, ans);
  }
  return ans;
}
int C[MAXN], du[MAXN], w[MAXN];
int fa[MAXN];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
bool Judge(int n) {
  for (int i = 1; i <= n; ++i)
    if (C[i] & 1) return 0;
  int t = find(1);
  for (int i = 2; i <= n; ++i)
    if (t != find(i) && C[i] != 0)
      return 0;
  return 1;
}
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i)
    a[i].x = read(), a[i].y = read();
  int Sum = 0;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    int x = read(), y = read();
    if (a[x] * a[y] > 0) swap(x, y);
    du[x]++, du[y]--;
    C[x]++, C[y]++;
    w[i] = (a[x].y > 0) && (a[y].y <= 0);
    add(x, y, 1, w[i]);
    Sum += w[i];
    if (find(x) != find(y)) fa[find(x)] = find(y);
  }
  if (!Judge(n)) return printf ("-1\n"), 0;
  int S = 0, T = n + 1;
  for (int i = 1; i <= n; ++i) {
    if (du[i] != 0) {
      if (du[i] > 0)
        add(S, i, du[i] / 2, 0);
      else if (du[i] < 0)
        add(i, T, - du[i] / 2, 0);
    }
  }
  printf ("%d\n", Sum - 2 * Min_Profit(S, T));
}
