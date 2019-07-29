#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
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
const int MAXN = 100005, MAXM = 200005;
struct edge {
  int END, next;
} v[MAXM * 2];
int first[MAXN], p, pre[MAXN];
queue<int> Q;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;

  v[p].END = a;
  v[p].next = pre[b];
  pre[b] = p++;
}
int du[MAXN], e[MAXN], fa[MAXN][20], dep[MAXN];
int lca(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  int d = dep[a] - dep[b];
  for (int i = 19; i >= 0; i--)
    if (d & (1 << i)) d -= (1 << i), a = fa[a][i];
  if (a == b) return a;
  for (int i = 19; i >= 0; i--)
    if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
  return fa[a][0];
}
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read();
    memset(first, -1, sizeof(first));
    memset(pre, -1, sizeof(pre));
    memset(du, 0, sizeof(du));
    memset(fa, 0, sizeof(fa));
    memset(dep, 0, sizeof(dep));
    p = 0;
    for (int i = 1; i <= m; i++) {
      int a = read(), b = read();
      add(b, a);
      du[a]++;
    }
    for (int i = 1; i <= n; i++)
      if (!du[i]) {
        add(n + 1, i);
        du[i]++;
      }
    Q.push(++n);
    int t = 0;
    while (!Q.empty()) {
      int k = Q.front();
      e[++t] = k;
      Q.pop();
      for (int i = first[k]; i != -1; i = v[i].next) {
        du[v[i].END]--;
        if (du[v[i].END] == 0) Q.push(v[i].END);
      }
    }
    for (int i = 1; i <= n; i++) {
      int k = e[i], x = 0;
      for (int i = pre[k]; i != -1; i = v[i].next) {
        if (x == 0)
          x = v[i].END;
        else
          x = lca(x, v[i].END);
      }
      fa[k][0] = x;
      dep[k] = dep[x] + 1;
      for (int i = 1; i <= 19; i++) fa[k][i] = fa[fa[k][i - 1]][i - 1];
    }
    int q = read();
    while (q--) {
      int a = read(), b = read();
      printf("%d\n", dep[a] + dep[b] - dep[lca(a, b)] - 1);
    }
  }
}