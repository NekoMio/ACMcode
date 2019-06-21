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
bool flag[55][55];
int a[55][55], Index, id[55][55][4], n;
bool Judge(int x, int y) {
  if (x <= 0 || x > n) return 0;
  if (y <= 0 || y > n) return 0;
  return 1;
}
const int MAXN = 5005;
const int MAXM = 500005;
struct edge {
  int S, END, next, cap, v;
}v[MAXM];
int first[MAXN], p;
void add(int a, int b, int f, int c) {
  v[p].END = b, v[p].S = a, v[p].v = c, v[p].cap = f, v[p].next = first[a], first[a] = p++;
  v[p].END = a, v[p].S = b, v[p].v =-c, v[p].cap = 0, v[p].next = first[b], first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
int q[10000005];
bool Spfa(int S, int E) {
  int h = 1, t = 0;
  memset (dis, 0x80, sizeof (dis));
  memset (pre, -1, sizeof (pre));
  q[++t] = S;
  dis[S] = 0;
  while (h <= t) {
    int k = q[h++];
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] < dis[k] + v[i].v && v[i].cap) {
        dis[v[i].END] = dis[k] + v[i].v;
        pre[v[i].END] = i;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          q[++t] = v[i].END;
        }
      }
    }
  }
  return dis[E] != (int)0x80808080;
}
int Calc(int S, int T, int m) {
  int ans = 0;
  while (Spfa(S, T) && m) {
    int flow = m;
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      flow = min(flow, v[i].cap);
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      v[i].cap -= flow, v[i ^ 1].cap += flow;
    if (dis[T] < 0) break;
    ans = ans + flow * dis[T];
    m -= flow;
  }
  return ans;
}
int main() {
  // freopen ("marshland.in", "r", stdin);
  // freopen ("marshland.out", "w", stdout);
  memset (first, -1, sizeof (first));
  n = read();
  int m = read(), k = read();
  int Sum = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      a[i][j] = read();
      Sum = Sum + a[i][j];
    }
  for (int i = 1; i <= k; ++i) {
    int x = read(), y = read();
    flag[x][y] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      id[i][j][1] = ++Index;
      id[i][j][2] = ++Index;
      if ((i + j) & 1) add(id[i][j][1], id[i][j][2], 1, a[i][j]);
    }
  }
  int S = ++Index, T = ++Index;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (!flag[i][j] && !((i + j) & 1)) {
        if (i & 1) {
          add(S, id[i][j][1], 1, 0);
          if (Judge(i - 1, j)) add(id[i][j][1], id[i - 1][j][1], 1, 0);
          if (Judge(i, j - 1)) add(id[i][j][1], id[i][j - 1][1], 1, 0);
          if (Judge(i + 1, j)) add(id[i][j][1], id[i + 1][j][1], 1, 0);
          if (Judge(i, j + 1)) add(id[i][j][1], id[i][j + 1][1], 1, 0);
        } else {
          add(id[i][j][1], T, 1, 0);
          if (Judge(i - 1, j)) add(id[i - 1][j][2], id[i][j][1], 1, 0);
          if (Judge(i, j - 1)) add(id[i][j - 1][2], id[i][j][1], 1, 0);
          if (Judge(i + 1, j)) add(id[i + 1][j][2], id[i][j][1], 1, 0);
          if (Judge(i, j + 1)) add(id[i][j + 1][2], id[i][j][1], 1, 0);
        }
      }
    }
  }
  printf ("%d\n", Sum - Calc(S, T, m));
}
