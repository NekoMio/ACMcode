#include <bits/stdc++.h>
using namespace std;
template<typename tp>
inline tp read() {
  tp x = 0, f = 1;
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
const int MOD = 1e9 + 7;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
long long val[MAXN];
int f[MAXN];
long long tmp[100], tpr[100], num[100];
int tot;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
long long mul(long long a, long long b, long long z) {
  return (a * b - (long long)(((long double)a * b + 0.5) / (long double)z) * z + z) % z;
}
long long pow_mod(long long a, long long b, long long p) {
  a %= p;
  long long ans = 1;
  while (b) {
    if (b & 1) ans = mul(ans, a, p);
    b >>= 1;
    a = mul(a, a, p);
  }
  return ans;
}
bool Miller_Rabin(long long x) {
  if (x == 1) return 0;
  for (int i = 0; i <= 9; ++i) {
    if (x == prime[i]) return 1;
    if (x % prime[i] == 0) return 0;
  }
  long long y = x - 1;
  int k = 0;
  for (; !(y & 1); y >>= 1) k++;
  for (int i = 0; i < 10; ++i) {
    long long z = rand() % (x - 1) + 1;
    long long c = pow_mod(z, y, x), d;
    for (int j = 0; j < k; ++j, c = d)
      if ((d = mul(c, c, x)) == 1 && c != 1 && c != x - 1)
        return 0;
    if (d != 1) return 0;
  }
  return 1;
}
long long Pollard_Rho(long long x, int y) {
  long long i = 1, k = 2, c = rand() % (x - 1) + 1;
  long long d = c;
  while (1) {
    i++;
    c = (mul(c, c, x) + y) % x;
    long long g = __gcd((d - c + x) % x, x);
    if (g != 1 && g != x) return g;
    if (c == d) return x;
    if (i == k) d = c, k <<= 1;
  }
}
void Divide(long long x, int c) {
  if (x == 1) return;
  if (Miller_Rabin(x)) return tmp[++tot] = x, void();
  long long z = x, tp = c;
  while (z >= x) z = Pollard_Rho(z, c--);
  Divide(z, tp), Divide(x / z, tp);
}
int id, cnt;
struct Node {
  Node *ch[70];
  int Sum;
  Node() {
    Sum = 0;
    memset (ch, 0, sizeof (ch));
  }
}*root;
void Build(Node *&rt, int dep) {
  rt = new Node();
  if (dep == cnt + 1) return;
  for (int i = 0; i <= num[dep]; ++i) {
    Build(rt->ch[i], dep + 1);
  }
}
int Num[100];
void dfs(Node *rt, int dep, int &ans) {
  if (dep == cnt + 1) {
    ans = (ans + rt->Sum) % MOD;
    return;
  }
  if (dep <= id) {
    dfs(rt->ch[Num[dep]], dep + 1, ans);
  } else {
    for (int i = Num[dep]; i <= num[dep]; ++i)
      dfs(rt->ch[i], dep + 1, ans);
  }
}
void dfs_add(Node *rt, int dep, int x) {
  if (dep == cnt + 1) {
    rt->Sum = (rt->Sum + x) % MOD;
    return;
  }
  if (dep <= id) {
    for (int i = 0; i <= Num[dep]; ++i)
      dfs_add(rt->ch[i], dep + 1, x);
  } else {
    dfs_add(rt->ch[Num[dep]], dep + 1, x);
  }
}
void dfs_sub(Node *rt, int dep, int x) {
  if (dep == cnt + 1) {
    rt->Sum = (rt->Sum - x + MOD) % MOD;
    return;
  }
  if (dep <= id) {
    for (int i = 0; i <= Num[dep]; ++i)
      dfs_sub(rt->ch[i], dep + 1, x);
  } else {
    dfs_sub(rt->ch[Num[dep]], dep + 1, x);
  }
}
void Update(int x) {
  memset (Num, 0, sizeof (Num));
  long long t = val[x];
  for (int i = 1; i <= cnt; ++i)
    while (t % tpr[i] == 0)
      Num[i]++, t /= tpr[i];
  if (x != 1) {
    f[x] = 0;
    dfs(root, 1, f[x]);
  }
  dfs_add(root, 1, f[x]);
}
void Remove(int x) {
  memset (Num, 0, sizeof (Num));
  long long t = val[x];
  for (int i = 1; i <= cnt; ++i)
    while (t % tpr[i] == 0)
      Num[i]++, t /= tpr[i];
  dfs_sub(root, 1, f[x]);
}
void DFS(int rt, int fa) {
  Update(rt);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
  }
  Remove(rt);
}
int main() {
  srand(200);
  // freopen ("walk.in", "r", stdin);
  // freopen ("walk.out", "w", stdout);
  memset (first, -1, sizeof (first));
  int n = read<int>();
  for (int i = 1; i < n; ++i) {
    int a = read<int>(), b = read<int>();
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= n; ++i)
    val[i] = read<long long>();
  Divide(val[1], 1000000);
  sort(tmp + 1, tmp + tot + 1);
  for (int i = 1; i <= tot; ++i) {
    if (tpr[cnt] != tmp[i]) tpr[++cnt] = tmp[i], num[cnt] = 1;
    else num[cnt]++;
  }
  long long Min = 0x3f3f3f3f3f3f3f3f, M = 1;
  long long All = 1;
  for (int i = 1; i <= cnt; ++i) All = All * (num[i] + 1);
  for (int i = 1; i <= cnt; ++i) {
    M = M * (num[i] + 1);
    if (M + All / M < Min) {
      Min = M + All / M;
      id = i;
    }
  }
  f[1] = 1;
  Build(root, 1);
  DFS(1, 0);
  assert(f[1] != 0);
  for (int i = 1; i <= n; ++i)
    printf ("%d\n", f[i]);
}
