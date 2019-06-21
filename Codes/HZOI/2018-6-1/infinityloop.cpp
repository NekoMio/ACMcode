#include <bits/stdc++.h>
using namespace std;
inline void gmin(int &a, int b) { a > b ? a = b : 0; }
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
const int INF = 0x3f3f3f3f;
const int MAXN = 20005;
struct edge {
  int S, END, next, cap, v;
} v[MAXN * 10];
int first[MAXN], p;
void add(int a, int b, int f, int c) {
  v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c,
  first[a] = p++;
  v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v = -c,
  first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  memset(pre, -1, sizeof(pre));
  dis[S] = 0;
  vis[S] = 1;
  queue<int> Q;
  Q.push(S);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (v[i].cap == 0) continue;
      if (dis[v[i].END] > dis[k] + v[i].v) {
        dis[v[i].END] = dis[k] + v[i].v;
        pre[v[i].END] = i;
        if (!vis[v[i].END]) {
          Q.push(v[i].END);
          vis[v[i].END] = 1;
        }
      }
    }
  }
  return dis[E] != 0x3f3f3f3f;
}
int Sum;
int Min_Profit(int S, int T) {
  int ans = 0, flow;
  int F = 0;
  while (Spfa(S, T)) {
    flow = INF;
    for (int i = pre[T]; i != -1; i = pre[v[i].S]) flow = min(flow, v[i].cap);
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      v[i].cap -= flow, v[i ^ 1].cap += flow;
    ans += flow * dis[T];
    F += flow;
  }
  if (Sum != F) return -1;
  else return ans / 3;
}
int a[2005][2005];
int Color[2005][2005];
int ID[2005][2005][7], Index;
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      a[i][j] = read();
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if ((i + j) & 1 )
        Color[i][j] = 1;
      else
        Color[i][j] = 2;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k <= 6; ++k) {
        ID[i][j][k] = ++Index;
      }
    }
  }
  int S = ++Index, T = ++Index;
  Sum = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (Color[i][j] == 1) {
        if (a[i][j] == 1) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 6), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 2) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 6), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 3) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 4) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 6), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 5) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 0, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 0, 0), add(ID[i][j][2], ID[i][j][6], 0, 0);
        } else if (a[i][j] == 6) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 7) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 1), add(ID[i][j][1], ID[i][j][4], 1, 1), add(ID[i][j][2], ID[i][j][5], 1, 4), add(ID[i][j][2], ID[i][j][6], 1, -2);
        } else if (a[i][j] == 8) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 6);
        } else if (a[i][j] == 9) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 10) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 0, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 0, 0), add(ID[i][j][1], ID[i][j][4], 0, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 11) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, -2), add(ID[i][j][1], ID[i][j][4], 1, 4), add(ID[i][j][2], ID[i][j][5], 1, 1), add(ID[i][j][2], ID[i][j][6], 1, 1);
        } else if (a[i][j] == 12) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 13) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 1), add(ID[i][j][1], ID[i][j][4], 1, 1), add(ID[i][j][2], ID[i][j][5], 1, -2), add(ID[i][j][2], ID[i][j][6], 1, 4);
        } else if (a[i][j] == 14) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 4), add(ID[i][j][1], ID[i][j][4], 1, -2), add(ID[i][j][2], ID[i][j][5], 1, 1), add(ID[i][j][2], ID[i][j][6], 1, 1);
        } else if (a[i][j] == 15) { Sum += 4, add(S, ID[i][j][0], 4, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 0);
        }
        if (i > 1) add(ID[i][j][3], ID[i - 1][j][4], 1, 0);
        if (i < n) add(ID[i][j][4], ID[i + 1][j][3], 1, 0);
        if (j > 1) add(ID[i][j][5], ID[i][j - 1][6], 1, 0);
        if (j < m) add(ID[i][j][6], ID[i][j + 1][5], 1, 0);
      } else {
        if (a[i][j] == 1) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 6), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 2) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 6), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 3) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 4) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 6), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 5) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 0, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 0, 0), add(ID[i][j][6], ID[i][j][2], 0, 0);
        } else if (a[i][j] == 6) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 7) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 1), add(ID[i][j][4], ID[i][j][1], 1, 1), add(ID[i][j][5], ID[i][j][2], 1, 4), add(ID[i][j][6], ID[i][j][2], 1, -2);
        } else if (a[i][j] == 8) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 6);
        } else if (a[i][j] == 9) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 10) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 0, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 0, 0), add(ID[i][j][4], ID[i][j][1], 0, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 11) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, -2), add(ID[i][j][4], ID[i][j][1], 1, 4), add(ID[i][j][5], ID[i][j][2], 1, 1), add(ID[i][j][6], ID[i][j][2], 1, 1);
        } else if (a[i][j] == 12) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 13) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 1), add(ID[i][j][4], ID[i][j][1], 1, 1), add(ID[i][j][5], ID[i][j][2], 1, -2), add(ID[i][j][6], ID[i][j][2], 1, 4);
        } else if (a[i][j] == 14) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 4), add(ID[i][j][4], ID[i][j][1], 1, -2), add(ID[i][j][5], ID[i][j][2], 1, 1), add(ID[i][j][6], ID[i][j][2], 1, 1);
        } else if (a[i][j] == 15) { add(ID[i][j][0], T, 4, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 0);
        }
      }
    }
  }
  printf("%d\n", Min_Profit(S, T));
}
#include <bits/stdc++.h>
using namespace std;
inline void gmin(int &a, int b) { a > b ? a = b : 0; }
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
const int INF = 0x3f3f3f3f;
const int MAXN = 20005;
struct edge {
  int S, END, next, cap, v;
} v[MAXN * 10];
int first[MAXN], p;
void add(int a, int b, int f, int c) {
  v[p].END = b, v[p].S = a, v[p].next = first[a], v[p].cap = f, v[p].v = c,
  first[a] = p++;
  v[p].END = a, v[p].S = b, v[p].next = first[b], v[p].cap = 0, v[p].v = -c,
  first[b] = p++;
}
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
bool Spfa(int S, int E) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  memset(pre, -1, sizeof(pre));
  dis[S] = 0;
  vis[S] = 1;
  queue<int> Q;
  Q.push(S);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (v[i].cap == 0) continue;
      if (dis[v[i].END] > dis[k] + v[i].v) {
        dis[v[i].END] = dis[k] + v[i].v;
        pre[v[i].END] = i;
        if (!vis[v[i].END]) {
          Q.push(v[i].END);
          vis[v[i].END] = 1;
        }
      }
    }
  }
  return dis[E] != 0x3f3f3f3f;
}
int Sum;
int Min_Profit(int S, int T) {
  int ans = 0, flow;
  int F = 0;
  while (Spfa(S, T)) {
    flow = INF;
    for (int i = pre[T]; i != -1; i = pre[v[i].S]) flow = min(flow, v[i].cap);
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      v[i].cap -= flow, v[i ^ 1].cap += flow;
    ans += flow * dis[T];
    F += flow;
  }
  if (Sum != F) return -1;
  else return ans / 3;
}
int a[2005][2005];
int Color[2005][2005];
int ID[2005][2005][7], Index;
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      a[i][j] = read();
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if ((i + j) & 1 )
        Color[i][j] = 1;
      else
        Color[i][j] = 2;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k <= 6; ++k) {
        ID[i][j][k] = ++Index;
      }
    }
  }
  int S = ++Index, T = ++Index;
  Sum = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (Color[i][j] == 1) {
        if (a[i][j] == 1) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 6), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 2) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 6), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 3) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 4) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 6), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 5) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 0, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 0, 0), add(ID[i][j][2], ID[i][j][6], 0, 0);
        } else if (a[i][j] == 6) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 3), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 7) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 1), add(ID[i][j][1], ID[i][j][4], 1, 1), add(ID[i][j][2], ID[i][j][5], 1, 4), add(ID[i][j][2], ID[i][j][6], 1, -2);
        } else if (a[i][j] == 8) { Sum += 1, add(S, ID[i][j][0], 1, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 6);
        } else if (a[i][j] == 9) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 3), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 10) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 0, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 0, 0), add(ID[i][j][1], ID[i][j][4], 0, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 0);
        } else if (a[i][j] == 11) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, -2), add(ID[i][j][1], ID[i][j][4], 1, 4), add(ID[i][j][2], ID[i][j][5], 1, 1), add(ID[i][j][2], ID[i][j][6], 1, 1);
        } else if (a[i][j] == 12) { Sum += 2, add(S, ID[i][j][0], 2, 0), add(ID[i][j][0], ID[i][j][1], 1, 0), add(ID[i][j][0], ID[i][j][2], 1, 0), add(ID[i][j][1], ID[i][j][3], 1, 3), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 3);
        } else if (a[i][j] == 13) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 1), add(ID[i][j][1], ID[i][j][4], 1, 1), add(ID[i][j][2], ID[i][j][5], 1, -2), add(ID[i][j][2], ID[i][j][6], 1, 4);
        } else if (a[i][j] == 14) { Sum += 3, add(S, ID[i][j][0], 3, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 4), add(ID[i][j][1], ID[i][j][4], 1, -2), add(ID[i][j][2], ID[i][j][5], 1, 1), add(ID[i][j][2], ID[i][j][6], 1, 1);
        } else if (a[i][j] == 15) { Sum += 4, add(S, ID[i][j][0], 4, 0), add(ID[i][j][0], ID[i][j][1], 2, 0), add(ID[i][j][0], ID[i][j][2], 2, 0), add(ID[i][j][1], ID[i][j][3], 1, 0), add(ID[i][j][1], ID[i][j][4], 1, 0), add(ID[i][j][2], ID[i][j][5], 1, 0), add(ID[i][j][2], ID[i][j][6], 1, 0);
        }
        if (i > 1) add(ID[i][j][3], ID[i - 1][j][4], 1, 0);
        if (i < n) add(ID[i][j][4], ID[i + 1][j][3], 1, 0);
        if (j > 1) add(ID[i][j][5], ID[i][j - 1][6], 1, 0);
        if (j < m) add(ID[i][j][6], ID[i][j + 1][5], 1, 0);
      } else {
        if (a[i][j] == 1) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 6), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 2) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 6), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 3) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 4) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 6), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 5) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 0, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 0, 0), add(ID[i][j][6], ID[i][j][2], 0, 0);
        } else if (a[i][j] == 6) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 3), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 7) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 1), add(ID[i][j][4], ID[i][j][1], 1, 1), add(ID[i][j][5], ID[i][j][2], 1, 4), add(ID[i][j][6], ID[i][j][2], 1, -2);
        } else if (a[i][j] == 8) { add(ID[i][j][0], T, 1, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 6);
        } else if (a[i][j] == 9) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 3), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 10) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 0, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 0, 0), add(ID[i][j][4], ID[i][j][1], 0, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 0);
        } else if (a[i][j] == 11) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, -2), add(ID[i][j][4], ID[i][j][1], 1, 4), add(ID[i][j][5], ID[i][j][2], 1, 1), add(ID[i][j][6], ID[i][j][2], 1, 1);
        } else if (a[i][j] == 12) { add(ID[i][j][0], T, 2, 0), add(ID[i][j][1], ID[i][j][0], 1, 0), add(ID[i][j][2], ID[i][j][0], 1, 0), add(ID[i][j][3], ID[i][j][1], 1, 3), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 3);
        } else if (a[i][j] == 13) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 1), add(ID[i][j][4], ID[i][j][1], 1, 1), add(ID[i][j][5], ID[i][j][2], 1, -2), add(ID[i][j][6], ID[i][j][2], 1, 4);
        } else if (a[i][j] == 14) { add(ID[i][j][0], T, 3, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 4), add(ID[i][j][4], ID[i][j][1], 1, -2), add(ID[i][j][5], ID[i][j][2], 1, 1), add(ID[i][j][6], ID[i][j][2], 1, 1);
        } else if (a[i][j] == 15) { add(ID[i][j][0], T, 4, 0), add(ID[i][j][1], ID[i][j][0], 2, 0), add(ID[i][j][2], ID[i][j][0], 2, 0), add(ID[i][j][3], ID[i][j][1], 1, 0), add(ID[i][j][4], ID[i][j][1], 1, 0), add(ID[i][j][5], ID[i][j][2], 1, 0), add(ID[i][j][6], ID[i][j][2], 1, 0);
        }
      }
    }
  }
  printf("%d\n", Min_Profit(S, T));
}
