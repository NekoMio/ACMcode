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
const int MOD = 1e9 + 7;
int n;
char s[4][2005];
int Max = 4000;
int Sumf[2][4005], Sumg[2][4005];
int f[2][4005], g[2][4005], num[2005], F[4005], Inv[4005];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
bool Judge() {
  if (s[1][1] == 'x' || s[3][1] == 'x' || s[1][n] == 'x' || s[3][n] == 'x') return 0;
  for (int i = 2; i <= n; ++i) if (s[1][i] == 'x' && s[1][i - 1] == 'x') return 0;
  for (int i = 2; i <= n; ++i) if (s[3][i] == 'x' && s[3][i - 1] == 'x') return 0;
  return 1;
}
int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD; 
}
int SumG(int x, int l, int r) {
  if (l < 0) return Sumg[x][r];
  else return (Sumg[x][r] - Sumg[x][l] + MOD) % MOD;
}
int Update(int l, int r, int &tot) {
  tot = 0;
  if (l > r) return 1;
  // for (int i = l; i <= r; ++i) tot += num[i] + 1;
  memset (f, 0, sizeof (f));
  memset (g, 0, sizeof (g));
  int now = 0;
  tot = num[l] + 1;
  // f[0][0] = 1;
  f[0][num[l] + 1] = F[num[l]];
  for (int i = 1; i <= num[l]; ++i) {
    g[0][num[l] - i + 1] = C(tot - (num[l] - i + 1), i) * F[num[l]] * (s[2][l - 1] != 0) % MOD;
  }
  for (int j = 1; j <= Max; ++j) {
    Sumf[now][j] = (Sumf[now][j - 1] + f[now][j]) % MOD;
    Sumg[now][j] = (Sumg[now][j - 1] + g[now][j]) % MOD;
  }
  for (int i = l + 1; i <= r; ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    memset (g[now], 0, sizeof (g[now]));
    memset (Sumf[now], 0, sizeof (Sumf[now]));
    memset (Sumg[now], 0, sizeof (Sumg[now]));
    for (int j = num[i] + 1; j <= tot + num[i] + 1; ++j) {
      f[now][j] = (f[now][j] + 1ll * Sumf[now ^ 1][Max] * C(j - 1, num[i]) % MOD * F[num[i]] % MOD) % MOD;
      f[now][j] = (f[now][j] + 1ll * SumG(now ^ 1, j - num[i] - 1, Max) * C(j - 1, num[i]) % MOD * F[num[i]] % MOD) % MOD;
    }
    for (int k = 1; k <= num[i]; ++k) {
      for (int j = num[i] - k + 1; j <= tot + num[i] + 1; ++j) {
        g[now][j] = (g[now][j] + 1ll * C(tot + num[i] + 1 - j, k) * F[num[i]] % MOD * Sumf[now ^ 1][j - (num[i] - k) - 1] % MOD * C(j - 1, num[i] - k) % MOD) % MOD;
      }
    }
    tot += num[i] + 1;
    for (int j = 1; j <= Max; ++j) {
      Sumf[now][j] = (Sumf[now][j - 1] + f[now][j]) % MOD;
      Sumg[now][j] = (Sumg[now][j - 1] + g[now][j]) % MOD;
    }
  }
  int ans = 0;
  for (int i = 1; i <= tot; ++i) ans = ((ans + f[now][i]) % MOD + g[now][i] * (s[2][r + 1] != 0)) % MOD;
  return ans;
}
int main() {
  n = read();
  F[0] = 1;
  for (int i = 1; i <= Max; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[Max] = pow_mod(F[Max], MOD - 2);
  for (int i = Max - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  for (int i = 1; i <= 3; ++i)
    scanf ("%s", s[i] + 1);
  if (!Judge()) return printf ("0\n"), 0;
  for (int i = 1; i <= n; ++i) num[i] = (s[1][i] == 'x') + (s[3][i] == 'x');
  int ans = 1;
  int nm = 0;
  for (int i = 1; i <= n; ++i) {
    int l = i;
    while (s[2][i] == 'x') i++;
    int r = i - 1;
    if (l <= r) {
      int d;
      int t = Update(l, r, d);
      ans = 1ll * ans * t % MOD * C(nm + d, d) % MOD;
      nm = nm + d;
    }
  }
  int d = 0;
  for (int i = 1; i <= n; ++i) {
    if (s[2][i] != 'x') d += num[i];
  }
  ans = 1ll * ans * C(nm + d, d) % MOD * F[d] % MOD;
  printf ("%d\n", ans);
}
