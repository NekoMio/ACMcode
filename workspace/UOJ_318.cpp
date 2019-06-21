#include <bits/stdc++.h>
// #define int long long
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
const int MAXN = 1005;
const int MAXM = 1000005;
const int INF = 0x7fffffff;
struct edge {
  int S, END, next, cap, cost;
} v[MAXM << 1];
int first[MAXM], p;
void add(int a, int b, int f, int c) {
  // printf ("%d %d %d %d\n", a, b, f, c);
  v[p].S = a, v[p].END = b, v[p].next = first[a], v[p].cap = f, v[p].cost = c,
  first[a] = p++;
  v[p].S = b, v[p].END = a, v[p].next = first[b], v[p].cap = 0, v[p].cost = -c,
  first[b] = p++;
}
int dis[MAXM], pre[MAXM];
bool vis[MAXM];
bool Spfa(int S, int E) {
  memset(dis, -1, sizeof(dis));
  memset(pre, -1, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  queue<int> Q;
  Q.push(S);
  vis[S] = 1;
  dis[S] = 0;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for (int i = first[u]; i != -1; i = v[i].next) {
      if (!v[i].cap) continue;
      if (dis[v[i].END] < dis[u] + v[i].cost) {
        dis[v[i].END] = dis[u] + v[i].cost;
        pre[v[i].END] = i;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          Q.push(v[i].END);
        }
      }
    }
  }
  return dis[E] != -1;
}
long long ans[MAXN];
long long Max_Profit(int S, int T, int m) {
  long long tmp = 0;
  int flow;
  while (m && Spfa(S, T)) {
    flow = m;
    for (int i = pre[T]; i != -1; i = pre[v[i].S]) flow = min(flow, v[i].cap);
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      v[i].cap -= flow, v[i ^ 1].cap += flow;
    tmp += 1ll * dis[T] * flow;
    m -= flow;
  }
  return tmp;
}
struct data {
  int a, s, c, x;
} d[MAXN];
int Index, day[MAXN], P[MAXN];
signed main() {
#ifndef ONLINE_JUDGE
  freopen ("workspace/vegetables1.in", "r", stdin);
  freopen ("workspace/vegetables.out", "w", stdout);
#endif
  memset (first, -1, sizeof (first));
  int n = read(), m = read(), k = read();
  for (int i = 1; i <= n; ++i) {
    d[i].a = read(), d[i].s = read(), d[i].c = read(), d[i].x = read();
  }
  int Max = 0;
  for (int i = 1; i <= k; ++i) {
    P[i] = read();
    Max = max(Max, P[i]);
  }
  int S = ++Index, T = ++Index;
  for (int i = 1; i <= Max; ++i) {
    day[i] = ++Index;
    add(day[i], T, m, 0);
  }
  for (int i = 1; i <= n; ++i) {
    add(S, ++Index, d[i].c - 1, d[i].a);
    add(S, Index, 1, d[i].a + d[i].s);
    add(Index, day[1], INF, 0);
    for (int j = 1; j * d[i].x < d[i].c && j + 1 <= Max; ++j) {
      add(Index, Index + 1, d[i].c - d[i].x * j, 0);
      add(Index + 1, day[j + 1], INF, 0);
      ++Index;
    }
  }
  for (int i = 1; i <= Max; ++i)
    ans[i] = Max_Profit(S, T, m) + ans[i - 1];
  for (int i = 1; i <= k; ++i) {
    printf ("%lld\n", ans[P[i]]);
  }
}