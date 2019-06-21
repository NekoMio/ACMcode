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
const int MAXN = 100005;
const int MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int F[MAXN], Inv[MAXN];
int C(int n, int m) {
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
struct edge {
  int END, next;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int Fa[MAXN + 1], n, m, t, w, powt[MAXN + 1], P, Invn, SumC0, SumC1, Cnt;
int find(int x) {
  if (Fa[x] != x) Fa[x] = find(Fa[x]);
  return Fa[x];
}
struct data {
  int a, b;
  int tp;
} e[MAXN * 3];
int dep[MAXN], top[MAXN], id[MAXN], fa[MAXN], son[MAXN], size[MAXN], Index;
void DFS1(int rt, int f) {
  size[rt] = 1;
  fa[rt] = f;
  dep[rt] = dep[f] + 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == f) continue;
    DFS1(v[i].END, rt);
    size[rt] += size[v[i].END];
    if (size[v[i].END] > size[son[rt]]) son[rt] = v[i].END;
  }
}
void DFS2(int rt, int f, int t) {
  id[rt] = ++Index;
  top[rt] = t;
  if (son[rt]) DFS2(son[rt], rt, t);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == f || v[i].END == son[rt]) continue;
    DFS2(v[i].END, rt, v[i].END);
  }
}
struct Node {
  Node *ch[2];
  int Sum, tag, l, r;
  Node(int _l = 0, int _r = 0) {
    ch[0] = ch[1] = NULL;
    Sum = tag = 0;
    l = _l, r = _r;
  }
  void Pushup() {
    Sum = 0;
    if (ch[0]) Sum += ch[0]->Sum;
    if (ch[1]) Sum += ch[1]->Sum;
  }
  void Pushdown() {
    if (tag) {
      if (ch[0]) ch[0]->Pushtag(tag);
      if (ch[1]) ch[1]->Pushtag(tag);
      tag = 0;
    }
  }
  void Pushtag(int c) {
    Sum += c * (r - l + 1);
    tag += c;
  }
} * root;
void Build(Node *&rt, int l = 1, int r = n) {
  rt = new Node(l, r);
  if (l == r) return;
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
  rt->Pushup();
}
void Update(Node *rt, int L, int R, int l = 1, int r = n) {
  // if (l == 1 && r == n) fprintf (stderr, "%d %d\n", L, R);
  // if (rt == NULL) rt = new Node(l, r);
  if (L <= l && R >= r) {
    rt->Pushtag(1);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Update(rt->ch[0], L, R, l, mid);
  if (R > mid) Update(rt->ch[1], L, R, mid + 1, r);
  rt->Pushup();
}
int Query(Node *rt, int L, int R, int l = 1, int r = n) {
  // if (rt == NULL) return 0;
  if (L <= l && R >= r) {
    return rt->Sum;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  int ans = 0;
  if (L <= mid) ans += Query(rt->ch[0], L, R, l, mid);
  if (R > mid) ans += Query(rt->ch[1], L, R, mid + 1, r);
  rt->Pushup();
  return ans;
}
int Query(int a, int b) {
  int ans = 0;
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    ans += Query(root, id[top[a]], id[a]);
    a = fa[top[a]];
  }
  if (a != b) {
    if (dep[a] > dep[b]) swap(a, b);
    ans += Query(root, id[a] + 1, id[b]);
  }
  return ans;
}
int Update(int a, int b) {
  int ans = 0;
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) swap(a, b);
    Update(root, id[top[a]], id[a]);
    ans += id[a] - id[top[a]] + 1;
	  a = fa[top[a]];
  }
  if (a != b) {
    if (dep[a] > dep[b]) swap(a, b);
    Update(root, id[a] + 1, id[b]);
    ans += id[b] - id[a];
  }
  return ans + 1;
}
int CalcC0(int x) { return 1ll * powt[n - x] * Invn % MOD; }
int CalcC1(int x) {
  int ans = 0;
  for (int i = 0; i <= x; ++i) {
    if (i & 1)
      ans = (ans - 1ll * C(x, i) * powt[n - i] % MOD * Invn % MOD + MOD) % MOD;
    else
      ans = (ans + 1ll * C(x, i) * powt[n - i] % MOD * Invn % MOD) % MOD;
  }
  return ans;
}
int Calc0() {
  return (((n - P + MOD) % MOD - 1ll * Cnt * powt[n - 2] % MOD * Invn % MOD +
           SumC0) %
              MOD +
          MOD) %
         MOD;
}
int PE;
int Calc1() { return ((P - 1ll * Cnt * PE % MOD + SumC1) % MOD + MOD) % MOD; }
int CC[MAXN * 3];
int main() {
  // freopen ("test/cactus3.in", "r", stdin);
  // freopen ("cactus.out", "w", stdout);
  memset (first, -1, sizeof (first));
  n = read(), m = read(), t = read(), w = read();
  Build(root);
  F[0] = 1;
  for (int i = 1; i <= n; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[n] = pow_mod(F[n], MOD - 2);
  for (int i = n - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  for (int i = 1; i <= n; ++i) Fa[i] = i;
  for (int i = 1; i <= n; ++i) powt[i] = pow_mod(i, t);
  Invn = pow_mod(powt[n], MOD - 2);
  PE = ((1ll - 2ll * pow_mod(1ll * (n - 1) * pow_mod(n, MOD - 2) % MOD, t) +
         pow_mod(1ll * (n - 2) * pow_mod(n, MOD - 2) % MOD, t)) %
            MOD +
        MOD) %
       MOD;
  P = 1ll * n * (((1 - pow_mod(1ll * (n - 1) * pow_mod(n, MOD - 2) % MOD, t)) % MOD + MOD) % MOD) % MOD;
  for (int i = 1; i <= m; ++i) {
    e[i].a = read(), e[i].b = read();
  }
  for (int i = 1; i <= m; ++i) {
  	// printf ("%d %d\n", find(e[i].a), find(e[i].b));
    if (find(e[i].a) != find(e[i].b)) {
      Fa[find(e[i].a)] = find(e[i].b);
      e[i].tp = 1;
      add(e[i].a, e[i].b);
      add(e[i].b, e[i].a);
    }
  }
  for (int i = 1; i <= n; ++i) {
  	if (!id[i]) {
      DFS1(i, 0);
      DFS2(i, 0, i);
	}
  }
  for (int i = 1; i <= m; ++i) {
    if (!e[i].tp) {
      if (!Query(e[i].a, e[i].b)) {
        e[i].tp = -1;
        CC[i] = Update(e[i].a, e[i].b);
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    if (e[i].tp) {
      Cnt++;
      if (e[i].tp == -1) {
        printf ("%d==%d\n", i, CC[i]);
        SumC1 = (SumC1 + CalcC1(CC[i])) % MOD;
        SumC0 = (SumC0 + CalcC0(CC[i])) % MOD;
      }
    }
    int Ans = Calc0();
    if (w == 1) Ans = (Ans + Calc1()) % MOD;
    printf("%d\n", Ans);
  }
}
