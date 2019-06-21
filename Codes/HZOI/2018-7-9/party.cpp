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
const int MAXN = 300005;
int fa[MAXN], a[MAXN];
struct edge {
  int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int dep[MAXN], top[MAXN], size[MAXN], son[MAXN], id[MAXN], Index, pos[MAXN];
int f[MAXN][20];
void DFS1(int rt, int ff) {
  dep[rt] = dep[ff] + 1;
  size[rt] = 1;
  f[rt][0] = ff;
  for (int i = 1; i <= 19; ++i) f[rt][i] = f[f[rt][i - 1]][i - 1];
  for (int i = first[rt]; i != -1; i = v[i].next) {
    DFS1(v[i].END, rt);
    size[rt] += size[v[i].END];
    if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
  }
}
bitset<1001> root[MAXN << 2], Sum[MAXN];
void DFS2(int rt, bitset<1001> &bt, int Tp) {
  top[rt] = Tp;
  id[rt] = ++Index;
  pos[Index] = rt;
  Sum[rt] = bt;
  bitset<1001> tp = bt;
  if (son[rt]) {
    tp.set(a[son[rt]], 1);
    DFS2(son[rt], tp, Tp);
  }
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == son[rt]) continue;
    tp.reset();
    tp.set(a[v[i].END], 1);
    DFS2(v[i].END, tp, v[i].END);
  }
}
int LCA(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  int d = dep[a] - dep[b];
  for (int i = 0; i <= 19; ++i)
    if (d & (1 << i))
      a = f[a][i], d -= (1 << i);
  if (a == b) return a;
  for (int i = 19; i >= 0; --i)
    if (f[a][i] != f[b][i])
      a = f[a][i], b = f[b][i];
  return f[a][0];
}
void Pushup(int rt) {
  root[rt] = root[rt << 1] | root[rt << 1 | 1];
}
void Build(int l, int r, int rt) {
  if (l == r) {
    root[rt].set(a[pos[l]], 1);
    return;
  }
  int mid = l + r >> 1;
  Build(l, mid, rt << 1);
  Build(mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
void Query(int L, int R, int l, int r, int rt, bitset<1001> &ans) {
  if (L <= l && R >= r)
    return ans |= root[rt], void();
  int mid = l + r >> 1;
  if (L <= mid) Query(L, R, l, mid, rt << 1, ans);
  if (R > mid) Query(L, R, mid + 1, r, rt << 1 | 1, ans);
}
int t[6];
bitset<1001> b[6];
int main() {
  // freopen ("party.in", "r", stdin);
  // freopen ("party.out", "w", stdout);
  memset (first, -1, sizeof (first));
  int n = read(), m = read(), q = read();
  for (int i = 2; i <= n; ++i) {
    fa[i] = read();
    add(fa[i], i);
  }
  for (int i = 1; i <= n; ++i) a[i] = read();
  DFS1(1, 0);
  bitset<1001> to_dfs;
  to_dfs.set(a[1], 1);
  DFS2(1, to_dfs, 1);
  Build(1, n, 1);
  while (q--) {
    int c = read();
    for (int i = 1; i <= c; ++i)
      t[i] = read(), b[i].reset();
    int lca = LCA(t[1], t[2]);
    for (int i = 3; i <= c; ++i) lca = LCA(lca, t[i]);
    for (int i = 1; i <= c; ++i) {
      while (top[t[i]] != top[lca]) {
        b[i] |= Sum[t[i]];
        t[i] = fa[top[t[i]]];
      }
      Query(id[lca], id[t[i]], 1, n, 1, b[i]);
    }
    int N = (1 << c) - 1;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= N; ++i) {
      bitset<1001> tmp(0);
      int tp = 0;
      for (int j = 1; j <= c; ++j) {
        if (i & (1 << (j - 1))) {
          tmp = tmp | b[j];
          tp++;
        }
      }
      ans = min(ans, (int)tmp.count() / tp);
    }
    printf ("%d\n", ans * c);
  }
}
