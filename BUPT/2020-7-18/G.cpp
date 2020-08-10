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
const int MAXN = 8e5 + 5;
set<int> st[MAXN];
int tmp[MAXN], p, tp[MAXN];
int fa[MAXN];
bool vis[MAXN];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
void Merge(int x, int y) {
  fa[find(x)] = find(y);
}
void Merge(set<int> &x, set<int> &y) {
  if (x.size() < y.size()) swap(x, y);
  for (auto v : y) {
    // if (vis[find(v)]) continue;
    if (x.count(find(v))) continue;
    x.insert(find(v));
  }
}
int main() {
  // freopen("1.in", "r", stdin);
  int T = read();
  while (T--) {
    int n = read(), m = read();
    for (int i = 0; i < n; i++) fa[i] = i, st[i].clear(), vis[i] = 0;
    for (int i = 1; i <= m; i++) {
      int x = read(), y = read();
      st[x].insert(y);
      st[y].insert(x);
    }
    int q = read();
    while (q--) {
      int o = read();
      if (fa[o] == o) {
        p = 0;
        for (auto x : st[o]) {
          tmp[++p] = x;
          tp[p] = find(x);
          vis[tp[p]] = 1;
          fa[find(tmp[p])] = o;
        }
        // printf ("%d\n", p);
        for (int i = 1; i <= p; i++) {
          Merge(st[o], st[tp[i]]);
        }
      }
      // printf ("%d\n", q);
    }
    for (int i = 0; i < n - 1; i++)
      printf ("%d ", find(i));
    printf ("%d\n", find(n - 1));
  }
}