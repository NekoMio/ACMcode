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
const int MAXM = 1000;
const int MAXN = 205;
struct edge {
  int END, next;
} v[MAXN];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
const int MOD = 1e9 + 7;
int bin[MAXN], fa[MAXN];
bool flag[MAXN];
int size[MAXN], dep[MAXN];
int a[MAXN], m, n;
int f[MAXN][2], Sum[MAXN][2];
int ans = 0;
void DP(int s, int len) {
  for (int i = s - 1; i <= m; ++i)
    f[i][0] = f[i][1] = Sum[i][0] = Sum[i][1] = 0;
  f[s][0] = Sum[s][0] = a[s];
  for (int i = s + 1; i <= m; ++i) {
    if (i - len >= s)
      f[i][1] =
          (f[i][1] + 1ll * a[i] * (f[i - len][0] + f[i - len][1]) % MOD) % MOD;
    int lst = max(s, i - len + 1) - 1;
    f[i][0] =
        (f[i][0] + 1ll * a[i] * (Sum[i - 1][0] + MOD - Sum[lst][0]) % MOD) %
        MOD;
    f[i][1] =
        (f[i][1] + 1ll * a[i] * (Sum[i - 1][1] + MOD - Sum[lst][1]) % MOD) %
        MOD;
    Sum[i][0] = (Sum[i - 1][0] + f[i][0]) % MOD;
    Sum[i][1] = (Sum[i - 1][1] + f[i][1]) % MOD;
    ans = (ans + 1ll * min(i - s, m - len) * f[i][1] % MOD) % MOD;
  }
}
void DFS(int rt) {
  size[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa[rt]) continue;
    int u = v[i].END;
    if (dep[u]) {
      if (dep[u] > dep[rt]) {
        int lst = 0;
        m = 0;
        for (int i = u; i != rt; lst = i, i = fa[i]) {
          a[++m] = bin[size[i] - size[lst]], flag[i] = 1;
        }
        a[++m] = bin[n - size[lst]];
        for (int len = 1; len < m; ++len) {
          for (int s = 1; s <= m - len; ++s) {
            DP(s, len);
          }
        }
      }
      continue;
    }
    dep[u] = dep[rt] + 1;
    fa[u] = rt;
    DFS(u);
    size[rt] += size[u];
  }
}
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int main() {
  n = read();
  int V = read();
  memset(first, -1, sizeof(first));
  for (int i = 1; i <= V; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  bin[0] = 1;
  for (int i = 1; i <= n; ++i) bin[i] = 1ll * bin[i - 1] * 2 % MOD;
  for (int i = 1; i <= n; ++i) bin[i]--;
  dep[1] = 1;
  DFS(1);
  for (int i = 2; i <= n; ++i) {
    if (!flag[i]) {
      ans = (ans + 1ll * bin[size[i]] * bin[n - size[i]] % MOD) % MOD;
    }
  }
  ans = 1ll * ans * pow_mod(bin[n] + 1, MOD - 2) % MOD;
  printf("%d\n", ans);
}
