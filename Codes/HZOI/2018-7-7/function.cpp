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
const int MAXN = 1e3 + 10;
int F[MAXN], G[MAXN], H[MAXN];
int MOD;
int pow_mod(register long long a, register int b) {
  register long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int G_f[MAXN], F_f[MAXN], H_f[MAXN];
int tmp[MAXN], f[MAXN][MAXN];
void Init(int n) {
  memset (tmp, 0, sizeof (tmp));
  memset (f, 0, sizeof (f));
  tmp[0] = 1;
  for (register int i = 1; i <= n; ++i) {
    for (register int j = i - 1; j >= 0; --j) {
      tmp[j + 1] = ((long long)tmp[j + 1] + tmp[j]) % MOD;
      tmp[j] = 1ll * tmp[j] * (MOD - i) % MOD;
    }
  }
  for (register int i = 1; i <= n; ++i) {
    memcpy(f[i], tmp, sizeof (f[i]));
    for (register int j = 0, t = pow_mod(MOD - i, MOD - 2); j < n; ++j) {
      f[i][j] = 1ll * f[i][j] * t % MOD;
      f[i][j + 1] = ((long long)f[i][j + 1] - f[i][j] + MOD) % MOD;
    }
  }
}
void Build(int *a, int n, int *ans) {
  memset (ans, 0, sizeof (tmp));
  for (register int i = 1; i <= n; ++i) {
    int Inv = 1;
    for (register int j = 1; j <= n; ++j) if (i != j)
      Inv = 1ll * Inv * (i - j + MOD) % MOD;
    Inv = 1ll * pow_mod(Inv, MOD - 2) * a[i] % MOD;
    for (register int j = 0; j <= n - 1; ++j) {
      ans[j] = (ans[j] + 1ll * Inv * f[i][j]) % MOD;
    }
  } 
}
int Get(int x, int *f, int n) {
  int ans = 0, tmp = 1;
  for (register int i = 0; i <= n; ++i) {
    ans = (ans + 1ll * tmp * f[i]) % MOD;
    tmp = 1ll * tmp * x % MOD;
  }
  return ans;
}
void Calc(int k, int n, int A, int d) {
  Init(k + 5);
  for (register int i = 1; i <= k + 5; ++i) F[i] = pow_mod(i, k);
  for (register int i = 1; i <= k + 5; ++i) F[i] = ((long long)F[i] + F[i - 1]) % MOD;
  Build(F, k + 5, F_f);
  // cerr << Get(10, F_f, k + 5) << " " << F[10] << endl;
  for (register int i = 1; i <= k + 5; ++i) G[i] = ((long long)G[i - 1] + F[i]) % MOD;
  Build(G, k + 5, G_f);
  for (register int i = 0; i <= k + 5; ++i) H[i] = Get((A + 1ll * i * d % MOD) % MOD, G_f, k + 5);
  for (register int i = 1; i <= k + 5; ++i) H[i] = ((long long)H[i] + H[i - 1]) % MOD;
  Build(H, k + 5, H_f);
  printf ("%d %d %d\n", Get(n, F_f, k + 5), Get(n, G_f, k + 5), Get(n, H_f, k + 5));
}
int main() {
  freopen ("function.in", "r", stdin);
  freopen ("function.out", "w", stdout);
  register int T = read();
  while (T--) {
    int k = read(), n = read(), A = read(), d = read(), p = read();
    MOD = p;
    Calc(k, n, A, d);
  }
}
