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
const int MAXN = 505;
const int INF = 0x3f3f3f3f;
struct edge {
  int END, next, cap;
}v[MAXN * MAXN * 5];
int first[3 * MAXN], p;
void add(int a, int b, int c) {
  v[p].END = b, v[p].next = first[a], v[p].cap = c, first[a] = p++;
  v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[MAXN * 3];
bool vis[MAXN * 3];
bool BFS(int S, int E) {
  queue<int> Q;
  memset (vis, 0, sizeof(vis));
  memset (dis, 0, sizeof(dis));
  vis[S] = 1;
  dis[S] = 0;
  Q.push(S);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (!vis[v[i].END] && v[i].cap > 0) {
        vis[v[i].END] = 1;
        dis[v[i].END] = dis[k] + 1;
        Q.push(v[i].END);
      }
    }
  }
  return vis[E];
}
int DFS(int S, int E, int a) {
  if (S == E || a == 0) return a;
  int flow = 0, f;
  for (int i = first[S]; i != -1; i = v[i].next) {
    if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0) {
      a -= f;
      flow += f;
      v[i].cap -= f;
      v[i ^ 1].cap += f;
      if (a == 0) break;
    }
  }
  if (!flow) dis[S] = -1;
  return flow;
}
int Dinic(int S, int E) {
  int ans = 0;
  while (BFS(S, E)) {
    ans += DFS(S, E, INF);
  }
  return ans;
}
int main() {
  int n = read(), m = read(), k = read();
  memset (first, -1, sizeof (first));
  int S = 0, p = n + m + 1, T = n + m + 2;
  add(S, p, n + k);
  for (int i = 1; i <= n; i++) add(p, i, 2);
  for (int i = 1; i <= n; i++) {
    int c = read();
    for (int j = 1; j <= c; j++) {
      int d = read();
      add(i, d + n, 1);
    }
  }
  for (int i = 1; i <= m; i++) add(i + n, T, 1);
  printf ("%d\n", Dinic(S, T));
  while (1);
}