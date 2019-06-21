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
const int MOD = 2003;
int Num[10];
int pow_mod(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int n, K, L, F;
int c[2005], d[2005];
void times(int *a, int *b) {
  for (int i = 0; i <= MOD; ++i) {
    c[i] = a[i];
    d[i] = b[i];
  }
  for (int i = 0; i <= MOD; ++i) a[i] = 0;
  for (int i = 0; i <= MOD; ++i) {
    for (int j = 0; j <= MOD; ++j) if (i + j <= MOD) {
      a[i + j] = (a[i + j] + c[i] * d[j]) % MOD;
    }
  }
}
int DP[1005][2005];
int ans[2005], a[2005], Fac[2005];
int main() {
  n = read(), K = read(), L = read(), F = read();
  DP[0][0] = 1;
  for (int i = 1; i <= F; ++i) {
    DP[i][0] = 0;
    for (int j = 1; j <= i; ++j) {
      DP[i][j] = (j * DP[i - 1][j] % MOD + DP[i - 1][j - 1]) % MOD;
    }
  }
  for (int i = 0; i <= F; ++i) a[i] = DP[F][i];
  Fac[0] = 1;
  for (int i = 1; i <= MOD; ++i) Fac[i] = Fac[i - 1] * i % MOD;
  ans[0] = 1;
  int b = L;
  while (b) {
    if (b & 1) times(ans, a);
    b >>= 1;
    times(a, a);
  }
  int C = 1, pK = 1;
  int Ans = 0;
  for (int i = 0; i < MOD; ++i) {
    Ans = (Ans + C * Fac[i] % MOD * pow_mod(pK, MOD - 2) % MOD * ans[i] % MOD) % MOD;
    C = 1ll * C * (n - i) % MOD * pow_mod(i + 1, MOD - 2) % MOD;
    pK = 1ll * pK * K % MOD;
  }
  printf ("%d\n", Ans);
}
