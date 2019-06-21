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
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
const int N = 438744;
int f[MAXN], g[MAXN], ggg[MAXN], Sum[MAXN];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int Inv2 = pow_mod(2, MOD - 2);
int F(int x) {
  return lower_bound(g + 1, g + N + 1, x) - g;
}
int gg(int t, int x) {
  int r = g[t] + 1;
  int ans = ggg[t];
  t++;
  for (int i = r; i <= x; ++i) {
    ans = (ans + 1ll * i * t % MOD) % MOD;
  }
  return ans;
}
int Calc(int x) {
  int t = F(x) - 1;
  return (Sum[t] + gg(t, x)) % MOD;
}
int main() {
  f[1] = 1;
  for (int i = 2; i <= 1000000; ++i)
    f[i] = f[i - f[f[i - 1]]] + 1;
  for (int i = 1; i <= N; ++i)
    g[i] = g[i - 1] + f[i];
  for (int i = 1; i <= N; ++i) {
    int a = g[i - 1] + 1, b = g[i];
    // printf ("%d\n", a + b);
    ggg[i] = (ggg[i - 1] + 1ll * (a + b) * i % MOD * (b - a + 1) % MOD * Inv2 % MOD) % MOD;
  }
  for (int i = 1; i <= N; ++i) Sum[i] = (Sum[i - 1] + ggg[i]) % MOD;
  int T = read();
  while (T--) {
    int n = read();
    printf ("%d\n", Calc(n));
  }
}
