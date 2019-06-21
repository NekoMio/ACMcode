#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
int f[100005][15], n, a[20], Inv[20];
int g[1100005];
int tmp[15], ftmp[15], gtmp[15], LCM;
const int MOD = 1e9 + 7;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
inline int lcm(int a, int b) { return 1ll * a * b / __gcd(a, b); }
void Build(int *a, int k) {
  for (int i = 0; i <= n; ++i) tmp[i] = g[i * LCM + k];
  memset(ftmp, 0, sizeof(ftmp));
  ftmp[0] = 1;
  for (int i = 0; i <= n; ++i) {
    for (int j = i; j >= 0; j--) {
      ftmp[j + 1] = (ftmp[j + 1] + ftmp[j]) % MOD;
      ftmp[j] = 1ll * ftmp[j] * (MOD - i) % MOD;
    }
  }
  for (int i = 0; i <= n; ++i) {
    memcpy(gtmp, ftmp, sizeof(gtmp));
    if (i == 0) {
      for (int j = 0; j <= n + 1; ++j)
        gtmp[j] = gtmp[j + 1];
    } else {
      for (int j = 0; j <= n; ++j) {
        gtmp[j] = 1ll * gtmp[j] * Inv[i] % MOD;
        gtmp[j + 1] = (gtmp[j + 1] - gtmp[j] + MOD) % MOD;
      }
    }
    int div = 1;
    for (int j = 0; j <= n; ++j) {
      if (j != i) div = 1ll * div * (i - j + MOD) % MOD;
    }
    div = pow_mod(div, MOD - 2);
    for (int j = 0; j <= n; ++j) {
      a[j] = (a[j] + 1ll * gtmp[j] * div % MOD * tmp[i] % MOD) % MOD;
    }
  }
}
void Init() {
  LCM = a[1];
  int N = 1100000;
  g[0] = 1;
  for (int j = 1; j <= n; ++j)
    for (int i = a[j]; i <= N; ++i) g[i] = (g[i] + g[i - a[j]]) % MOD;
  for (int i = 1; i <= n; ++i) Inv[i] = pow_mod(MOD - i, MOD - 2);
  for (int i = 2; i <= n; ++i) LCM = lcm(a[i], LCM);
  for (int j = LCM; j <= N; ++j) g[j] = (g[j] + g[j - LCM]) % MOD;
  for (int i = 0; i < LCM; ++i) Build(f[i], i);
}
int F(int x, int k) {
  int ans = 0;
  for (int i = 0, t = 1; i <= n; ++i, t = 1ll * t * x % MOD) {
    ans = (ans + 1ll * t * f[k][i] % MOD) % MOD;
  }
  return ans;
}
int Calc(long long x) {
  int ans = 0;
  for (int i = 0; i < LCM; ++i) {
    if (x >= i) {
      long long a = (x - i) / LCM;
      ans = (ans + F(a % MOD, i)) % MOD;
    }
  }
  return ans;
}
int main() {
  n = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  Init();
  long long L = read(), R = read();
  printf("%d\n", (Calc(R) - Calc(L - 1) + MOD) % MOD);
}
