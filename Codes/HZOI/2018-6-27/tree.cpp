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
const int MAXN = 3e5 + 5;
int w[MAXN];
struct data {
  int a, b;
}c[MAXN];
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int f[MAXN][21], dep[MAXN], L[MAXN], R[MAXN], Index;
int Id[MAXN];
void DFS(int rt, int fa) {
  f[rt][0] = fa;
  L[rt] = ++Index;
  Id[Index] = rt;
  dep[rt] = dep[fa] + 1;
  for (int i = 1; i <= 20; ++i) f[rt][i] = f[f[rt][i - 1]][i - 1];
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
  }
  R[rt] = Index;
}
long long Sum[MAXN << 2];
long long Add[MAXN << 2];
void Pushup(int rt) {
  Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}
void Pushdown(int rt, int l, int mid, int r) {
  if (Add[rt]) {
    Add[rt << 1] += Add[rt];
    Add[rt << 1 | 1] += Add[rt];
    Sum[rt << 1] += 1ll * Add[rt] * (mid - l + 1);
    Sum[rt << 1 | 1] += 1ll * Add[rt] * (r - mid);
    Add[rt] = 0;
  }
}
void Build(int l, int r, int rt) {
  if (l == r) {
    Sum[rt] = w[Id[l]];
    return;
  }
  int mid = l + r >> 1;
  Build(l, mid, rt << 1);
  Build(mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
void Update(int L, int R, int c, int l, int r, int rt) {
  if (L <= l && R >= r) {
    Add[rt] += c;
    Sum[rt] += 1ll * c * (r - l + 1);
    return;
  }
  int mid = l + r >> 1;
  Pushdown(rt, l, mid, r);
  if (L <= mid) Update(L, R, c, l, mid, rt << 1);
  if (R > mid) Update(L, R, c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
long long Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r)
    return Sum[rt];
  int mid = l + r >> 1;
  Pushdown(rt, l, mid, r);
  long long ans = 0;
  if (L <= mid) ans += Query(L, R, l, mid, rt << 1);
  if (R > mid) ans += Query(L, R, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
  return ans;
}
int rt, lst = 1;
int CalcLca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int d = dep[x] - dep[y];
  for (int i = 20; i >= 0; --i)
    if (d & (1 << i))
      d -= (1 << i), x = f[x][i];
  if (x == y) return x;
  for (int i = 20; i >= 0; --i)
    if (f[x][i] != f[y][i])
      x = f[x][i], y = f[y][i];
  return f[x][0];
}
int F[MAXN], Dep[MAXN];
void dfs(int rt, int fa) {
  Dep[rt] = Dep[fa] + 1;
  F[rt] = fa;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    dfs(v[i].END, rt);
  }
}
int t[4];
bool cmp(const int &a, const int &b) {
  return dep[a] < dep[b];
}
int LCA(int x, int y) {
  if (x == y) return x;
  if (rt == 1) return CalcLca(x, y);
  else {
    t[1] = CalcLca(x, y);
    t[2] = CalcLca(x, rt);
    t[3] = CalcLca(y, rt);
    sort(t + 1, t + 4, cmp);
    return t[3];
  }
}
bool in(int x, int c) {
  if (L[c] <= L[x] && L[x] <= R[c]) return 1;
  return 0;
}
int Calc(int x, int lca) {
  int d = dep[x] - dep[lca] - 1;
  for (int i = 20; i >= 0; --i)
    if (d & (1 << i))
      x = f[x][i];
  return x;
}
void Update(int x, int y, int c) {
  int lca = LCA(x, y);
  if (lca == rt) Update(1, Index, c, 1, Index, 1);
  else if (!in(rt, lca)) Update(L[lca], R[lca], c, 1, Index, 1);
  else {
    int t = Calc(rt, lca);
    Update(L[t], R[t], -c, 1, Index, 1);
    Update(1, Index, c, 1, Index, 1);
  }
}
long long Query(int x) {
  if (rt == x) return Sum[1];
  if (!in(rt, x)) return Query(L[x], R[x], 1, Index, 1);
  long long ans = Sum[1];
  int t = Calc(rt, x);
  return ans - Query(L[t], R[t], 1, Index, 1);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen ("test/tree2.in", "r", stdin);
  freopen ("test/tree.out", "w", stdout);
#endif
  memset (first, -1, sizeof (first));
  int n = read(), q = read();
  for (int i = 1; i <= n; ++i)
    w[i] = read();
  for (int i = 1; i <= n - 1; ++i) {
    c[i].a = read(), c[i].b = read();
    add(c[i].a, c[i].b);
    add(c[i].b, c[i].a);
  }
  DFS(1, 0);
  rt = 1;
  Build(1, n, 1);
  for (int i = 1; i <= q; ++i) {
    int op = read();
    if (op == 1) {
      rt = read();
    } else if (op == 2) {
      int a = read(), b = read(), c = read();
      Update(a, b, c);
    } else {
      int x = read();
      printf ("%lld\n", Query(x));
    }
  }
}
