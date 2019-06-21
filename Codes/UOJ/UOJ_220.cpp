#pragma GCC optimize("O2")
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
const int MAXN = 1e5 + 5;
const int MOD = 999983;
struct Hash_Table {
  struct edge {
    int next, x, y;
    int ans;
  }v[MAXN * 24];
  int first[MOD + 1], p;
  void clear() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  Hash_Table() { clear(); }
  bool count(int x, int y) {
    int H = (1ll * x * 7717 + 1ll * y * 19991) % MOD;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].x == x && v[i].y == y) {
        return 1;
      }
    }
    return 0;    
  }
  int &operator () (int x, int y) {
    int H = (1ll * x * 7717 + 1ll * y * 19991) % MOD;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].x == x && v[i].y == y) {
        return v[i].ans;
      }
    }
    v[p].x = x, v[p].y = y;
    v[p].next = first[H];
    first[H] = p++;
    return v[p - 1].ans = 0;
  }
}mp1, mp2;
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
struct edge {
  int END, next;
}v[MAXN * 100];
int first[MAXN * 25], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
void Link(int a, int b) {
  add(a, b);
  add(b, a);
}
int dfn[MAXN * 25], low[MAXN * 25], Index;
bool iscut[MAXN * 25];
void Tarjan(int x, int fa) {
  dfn[x] = low[x] = ++Index;
  int S = 0;
  for (int i = first[x]; i != -1; i = v[i].next) {
    if (!dfn[v[i].END]) {
      S++;
      Tarjan(v[i].END, x);
      low[x] = min(low[v[i].END], low[x]);
      if (low[v[i].END] >= dfn[x])
        iscut[x] = 1;
    } else {
      low[x] = min(dfn[v[i].END], low[x]);
    }
  }
  if (S == 1 && fa == -1) iscut[x] = 0;
}
int Id, n, m, c;
bool flag[MAXN * 25];
void Build(int x, int y) {
  for (int i = -2; i <= 2; ++i) {
    for (int j = -2; j <= 2; ++j) {
      if (i == 0 && j == 0) continue;
      int nx = x + i, ny = y + j;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (mp1.count(nx, ny)) continue;
      if (mp2.count(nx, ny)) {
        if (abs(i) <= 1 && abs(j) <= 1) flag[mp2(nx, ny)] = 1;
      } else {
        mp2(nx, ny) = ++Id;
        if (abs(i) <= 1 && abs(j) <= 1) flag[Id] = 1;
        for (int k = 0; k <= 3; ++k) {
          int nnx = nx + dx[k], nny = ny + dy[k];
          if (nnx < 1 || nnx > n || nny < 1 || nny > m) continue;
          if (mp1.count(nnx, nny)) continue;
          if (!mp2.count(nnx, nny)) continue;
          Link(Id, mp2(nnx, nny));
        }
      }
    }
  }
}
int fa[MAXN * 25];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
void Init() {
  for (int i = 0; i < mp2.p; ++i) fa[mp2.v[i].ans] = mp2.v[i].ans;
  for (int i = 0; i < mp2.p; ++i) {
    int x = mp2.v[i].ans;
    for (int j = first[x]; j != -1; j = v[j].next)
      if (find(x) != find(v[j].END))
        fa[find(x)] = find(v[j].END);
  }
}
#define Paii pair<int, int>
int tp[50];
static int ID[MAXN * 25];
bool check(int x, int y, int id) {
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue;
      int nx = x + i, ny = y + j;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (!mp1.count(nx, ny)) continue;
      int tmp = ID[mp1(nx, ny)];
      if (ID[id] == -1) {
        ID[id] = tmp;
      } else if (tmp != -1 && ID[id] != tmp) {
        return 0;
      }
    }
  }
  for (int i = -2; i <= 2; ++i) {
    for (int j = -2; j <= 2; ++j) {
      if (i == 0 && j == 0) continue;
      int nx = x + i, ny = y + j;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (mp1.count(nx, ny)) continue;
      int tmp = find(mp2(nx, ny));
      if (ID[id] == -1) {
        ID[id] = tmp;
      } else if (ID[id] != tmp)
        return 0;
    }
  }
  return 1;
}
int Calc() {
  n = read(), m = read(), c = read();
  mp1.clear(), mp2.clear();
  Id = 0;
  for (int i = 1; i <= c; ++i) {
    int x = read(), y = read();
    mp1(x, y) = i - 1;
  }
  if (1ll * n * m - c <= 1) return -1;
  if (1ll * n * m == 2) return -1;
  memset (first, -1, sizeof (first)), p = 0;
  memset (flag, 0, sizeof (flag));
  for (int i = 0; i < mp1.p; ++i)
    Build(mp1.v[i].x, mp1.v[i].y);
  Init();
  
  // static Paii X[MAXN * 25];
  for (int i = 0; i < mp1.p; ++i)
    ID[i] = -1;
  for (int i = 0; i < mp1.p; ++i) {
    if (!check(mp1.v[i].x, mp1.v[i].y, i))
      return 0;
  }
  if (n * m - c == 2 && mp2.p == 2) {
    if (v[first[1]].END == 2) return -1;
  }
  if (n == 1 || m == 1) return 1;
  for (int i = 1; i <= Id; ++i) {
    dfn[i] = low[i] = iscut[i] = 0;
  }
  Index = 0;
  for (int i = 1; i <= Id; ++i)
    if (!dfn[i])
      Tarjan(i, -1);
  for (int i = 1; i <= Id; ++i) {
    if (iscut[i] && flag[i]) {
      return 1;
    }
  }
  return 2;
}
int main() {
  int T = read();
  while (T--) {
    printf ("%d\n", Calc());
  }
}
