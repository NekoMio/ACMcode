#pragma GCC optimize("O3")
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
struct edge {
  int END, next, cap;
}v[5000005];
int first[50005], p;
void Add(int a, int b, int c) {
  v[p].END = b, v[p].cap = c, v[p].next = first[a], first[a] = p++;
  v[p].END = a, v[p].cap = 0, v[p].next = first[b], first[b] = p++;
}
int q[10000005];
int dis[50005];
bool BFS(int S, int E) {
  memset (dis, -1, sizeof (dis));
  int h = 1, t = 0;
  q[++t] = S;
  dis[S] = 0;
  while (h <= t) {
    int k = q[h++];
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] == -1 && v[i].cap) {
        dis[v[i].END] = dis[k] + 1;
        if (v[i].END == E) return 1;
        q[++t] = v[i].END;
      }
    }
  }
  return 0;
}
int DFS(int S, int T, int a) {
  if (S == T || !a) return a;
  int flow = 0, f;
  for (int i = first[S]; i != -1; i = v[i].next) {
    if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, T, min(a, v[i].cap))) > 0) {
      flow += f;
      a -= f;
      v[i].cap -= f;
      v[i ^ 1].cap += f;
      if (!a) break;
    }
  }
  if (!flow) dis[S] = -1;
  return flow;
}
int Dinic(int S, int T) {
  int ans = 0;
  while (BFS(S, T)) ans += DFS(S, T, 0x3f3f3f3f);
  return ans;
}
vector<int> vc[3005];
int pos[3005][3005];
int Index, Id[3005][3005], a[3005];
int main() {
  // freopen ("collection.in", "r", stdin);
  // freopen ("collection.out", "w", stdout);
  int T = read();
  while (T--) {
    memset (first, -1, sizeof (first)), p = 0;
    memset (Id, 0, sizeof (Id));
    memset (pos, 0, sizeof (pos));
    Index = 0;
    int n = read(), m = read();
    for (int i = 1; i <= n; ++i) vc[i].clear();
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= m; ++i) {
      int x = read(), y = read();
      vc[x].push_back(y), vc[y].push_back(x);
      pos[y][vc[y].size()] = vc[x].size(), pos[x][vc[x].size()] = vc[y].size();
    }
    int S = ++Index, T = ++Index;
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= vc[i].size(); ++j)
        Id[i][j] = ++Index;
      Add(S, Id[i][0], 1);
      for (int j = 1; j <= vc[i].size(); ++j)
        Add(Id[i][j - 1], Id[i][j], a[i]);
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= vc[i].size(); ++j)
        Add(Id[i][j], Id[vc[i][j - 1]][pos[i][j]], 1);
    Add(Id[1][vc[1].size()], T, a[1]);
    printf ("%d\n", Dinic(S, T));
    cerr << p << " " << Index << endl;
  }
}
