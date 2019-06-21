#include <bits/stdc++.h>
using namespace std;
#define int long long
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
const int MAXN = 2e6 + 5;
struct edge {
  int END, next, v, c;
  bool vis;
} v[MAXN], e[MAXN];
int first[MAXN], firste[MAXN], p, pp;
void add(int a, int b, int c, int d) {
  // printf ("%d %d %d\n", a, b, c);
  v[p].END = b;
  v[p].v = c;
  v[p].c = d;
  v[p].next = first[a];
  first[a] = p++;
}
void adde(int a, int b, int c, int d) {
  // printf ("%d %d %d\n", a, b, c);
  e[pp].END = b;
  e[pp].v = c;
  e[pp].c = d;
  e[pp].next = firste[a];
  firste[a] = pp++;
}
int dis[MAXN];
bool vis[MAXN];
void Spfa(int S, int E) {
  queue<int> Q;
  Q.push(S);
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  dis[S] = 0;
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[k] + v[i].v < dis[v[i].END]) {
        dis[v[i].END] = dis[k] + v[i].v;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          Q.push(v[i].END);
        }
      }
    }
  }
}
vector<int> R, C[MAXN], N[MAXN], ST[MAXN];
int f[MAXN], tail[MAXN];
int du[MAXN], cnt;
void DFS(int rt, int o = 0) {
  N[cnt].push_back(rt);
  for (int i = firste[rt]; i != -1; i = e[i].next) {
    if (!e[i].vis && (o == 0 || o == e[i].c)) {
      e[i].vis = 1;
      DFS(e[i].END, e[i].c);
      o = e[i].c;
    }
  }
}
signed main() {
  int n = read(), m = read();
  memset(first, -1, sizeof(first));
  memset(firste, -1, sizeof(firste));
  for (int i = 1; i <= m; ++i) {
    int s = read(), now = 0;
    int a = read();
    for (int j = 1; j <= s; ++j) {
      int c = read(), b = read();
      add(a, b, c, i);
      a = b;
    }
  }
  Spfa(1, n);
  for (int i = 1; i <= n; ++i)
    if (dis[i] < 0x3f3f3f3f3f3f3f3f) {
      for (int j = first[i]; j != -1; j = v[j].next) {
        if (dis[v[j].END] == dis[i] + v[j].v) {
          adde(i, v[j].END, v[j].v, v[j].c);
          // fprintf(stderr, "%d\n", v[j].c);
          du[v[j].END]++;
        }
      }
    }
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int k = q.front();
    q.pop();
    R.push_back(k);
    for (int i = firste[k]; i != -1; i = e[i].next) {
      du[e[i].END]--;
      if (du[e[i].END] == 0) q.push(e[i].END);
    }
  }
  for (auto x : R) {
    while (1) {
      cnt++;
      DFS(x);
      if (N[cnt].size() == 1) {
        N[cnt].pop_back();
        cnt--;
        break;
      } else {
        ST[cnt].resize(N[cnt].size() + 1);
        // fprintf (stderr, "%lld %lld\n", x, N[cnt].size());
        // assert(N[cnt].size() == 2);
        for (auto z : N[cnt]) {
          C[z].push_back(cnt);
        }
      }
    }
  }
  for (auto x : R) {
    for (auto z : C[x]) {
      // fprintf (stderr, "%d\n", z);
      while (tail[z] >= 2 &&
             (f[ST[z][tail[z]]] + dis[ST[z][tail[z]]] * dis[ST[z][tail[z]]] -
              f[ST[z][tail[z] - 1]] -
              dis[ST[z][tail[z] - 1]] * dis[ST[z][tail[z] - 1]]) /
                     (dis[ST[z][tail[z]]] - dis[ST[z][tail[z] - 1]]) <
                 2 * dis[x])
        tail[z]--;
      if (tail[z] != 0)
        f[x] = max(f[x], dis[x] * dis[x] - 2 * dis[x] * dis[ST[z][tail[z]]] +
                             f[ST[z][tail[z]]] +
                             dis[ST[z][tail[z]]] * dis[ST[z][tail[z]]]);
      // fprintf (stderr, "%lld\n", f[x]);
    }
    for (auto z : C[x]) {
      while (tail[z] >= 2 &&
             (f[x] + dis[x] * dis[x] - f[ST[z][tail[z]]] -
              dis[ST[z][tail[z]]] * dis[ST[z][tail[z]]]) /
                     (dis[x] - dis[ST[z][tail[z]]]) >
                 (f[ST[z][tail[z]]] +
                  dis[ST[z][tail[z]]] * dis[ST[z][tail[z]]] -
                  f[ST[z][tail[z] - 1]] -
                  dis[ST[z][tail[z] - 1]] * dis[ST[z][tail[z] - 1]]) /
                     (dis[ST[z][tail[z]]] - dis[ST[z][tail[z] - 1]]))
        tail[z]--;
      ST[z][++tail[z]] = x;
    }
  }
  // printf ("Speed Test\n");
  printf("%lld %lld\n", dis[n], f[n]);
}

