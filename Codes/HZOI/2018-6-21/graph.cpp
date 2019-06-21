#pragma GCC optimize("O2")
#include <algorithm>
#include <cstdio>
#include <cstring>
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
const int MOD = 1004535809;
const int MAXN = 2e5 + 5;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int Inv, N, rev[MAXN];
void Init(int x) {
  N = 1;
  while (N < (x << 1)) N <<= 1;
  Inv = pow_mod(N, MOD - 2);
  for (int i = 1; i <= N; ++i)
    if (i & 1) rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else rev[i] = (rev[i >> 1] >> 1);
}
void FFt(int *a, int op) {
  int w, wn, t;
  for (int i = 1; i < N; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 2; k <= N; k <<= 1) {
    wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
    for (int j = 0; j < N; j += k) {
      w = 1;
      for (int i = 0; i < (k >> 1); i++, w = 1ll * w * wn % MOD) {
        t = 1ll * a[i + j + (k >> 1)] * w % MOD;
        a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
        a[i + j] = (a[i + j] + t) % MOD;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < N; i++) a[i] = 1ll * a[i] * Inv % MOD;
}
int tmp[MAXN];
void Get_Inv(int dep, int *a, int *b)
{
    if (dep == 1)
        return b[0] = pow_mod(a[0], MOD - 2), void();
    Get_Inv((dep + 1) >> 1, a, b);
    Init(dep + 1);
    copy(a, a + dep, tmp);
    fill(tmp + dep, tmp + N, 0);
    FFt(tmp, 1);
    FFt(b, 1);
    for (int i = 0; i < N; ++i)
        b[i] = b[i] * ((2 - 1ll * b[i] * tmp[i] % MOD + MOD) % MOD) % MOD;
    FFt(b, -1);
    fill(b + dep, b + N, 0);
}
int F[MAXN], F_Inv[MAXN], C[MAXN], G[MAXN], G_Inv[MAXN], g[16][MAXN], bin[MAXN], bin_Inv[MAXN];
int S[20][20];
int c(int n, int m) {
  return 1ll * F[n] * F_Inv[m] % MOD * F_Inv[n - m] % MOD;
}
int CalcS(int n, int m) {
  int ans = 0;
  for (int k = 0; k <= m; ++k) {
    if (k & 1) ans = (ans - 1ll * c(m, k) * pow_mod(m - k, n) % MOD + MOD) % MOD;
    else ans = (ans + 1ll * c(m, k) * pow_mod(m - k, n) % MOD) % MOD;
  }
  return 1ll * ans * F_Inv[m] % MOD;
}
int main() {
  freopen ("1.txt", "r", stdin);
  int n = 5e4;
  F[0] = 1;
  for (int i = 1; i <= n; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  F_Inv[n] = pow_mod(F[n], MOD - 2);
  for (int i = n - 1; i >= 0; --i) F_Inv[i] = 1ll * F_Inv[i + 1] * (i + 1) % MOD;
  for (int i = 0; i <= n; ++i)
    G[i] = (i < 2) ? 1 : pow_mod(2, 1ll * i * (i - 1) / 2) * F_Inv[i] % MOD;
  for (int i = 0; i <= n; ++i) C[i] = 1ll * i * G[i] % MOD;
  Get_Inv(n + 1, G, G_Inv);
  Init(n + 1);
  FFt(G_Inv, 1), FFt(C, 1);
  for (int i = 0; i < N; ++i) C[i] = 1ll * C[i] * G_Inv[i] % MOD;
  FFt(C, -1);
  for (int i = 1; i <= n; ++i) g[1][i] = 1ll * C[i] * F[i - 1] % MOD * F_Inv[i] % MOD;
  for (int i = n + 1; i < N; ++i) g[1][i] = C[i] = 0;
  FFt(g[1], 1), FFt(C, 1);
  for (int i = 2; i <= 15; ++i) {
    for (int j = 0; j < N; ++j)
      g[i][j] = 1ll * g[i - 1][j] * C[j] % MOD;
    FFt(g[i], -1);
    for (int j = 0; j <= n; ++j)
      g[i][j] = 1ll * g[i][j] * F[j - 1] % MOD * F_Inv[j] % MOD;
    for (int j = n + 1; j < N; ++j) g[i][j] = 0;
    // for (int j = 0; j <= 10; ++j) fprintf (stderr, "%lld ", 1ll * g[i][j] * F[j] % MOD);
    // fprintf (stderr, "\n");
    FFt(g[i], 1);
  }
  // G[0] = 0;
  FFt(G, 1);
  for (int i = 1; i <= 15; ++i) {
    for (int j = 0; j < N; ++j)
      g[i][j] = 1ll * g[i][j] * G[j] % MOD;
    FFt(g[i], -1);
    // for (int j = 1; j <= 10; ++j) {
    //   fprintf (stderr, "%d ", g[i][j]);
    // }
    // fprintf (stderr, "\n");
    for (int j = 1; j <= n; ++j)
      g[i][j] = 1ll * g[i][j] * F[j] % MOD;
  }
  int T = read();
  for (int i = 1; i <= 15; ++i)
    for (int j = 1; j <= i; ++j)
      S[i][j] = CalcS(i, j);
  bin[0] = 1;
  for (int i = 1; i <= n; ++i) bin[i] = bin[i - 1] * 2 % MOD:
  bin_Inv = pow_mod()
  while (T--) {
    int m = read(), k = read();
    int ans = 0;
    for (int i = 1; i <= k; ++i)
      ans = (ans + 1ll * S[k][i] * F[i] % MOD * g[i][m] % MOD) % MOD;
    printf ("%lld\n", 1ll * ans * pow_mod(pow_mod(2, (m * (m - 1) / 2) % MOD), MOD - 2) % MOD);
  }
}
