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
const int MAXN = 1e6;
const int MOD = 1000000007;
int F[MAXN + 2], Inv[MAXN + 2];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int C(int n, int m) {
  return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
struct data {
  int x, y;
} vc[10005];
int cnt;
int main() {
  // freopen ("hongkong.in", "r", stdin);
  // freopen ("hongkong.out", "w", stdout);
  int n = read(), m = read(), k = read();
  F[0] = 1;
  for (int i = 1; i <= MAXN; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[MAXN] = pow_mod(F[MAXN], MOD - 2);
  for (int i = MAXN - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  while (m--) {
    int op = read();
    if (op == 0) {
      int x = read(), y = read();
      vc[++cnt] = (data){x, y};
    } else {
      int x = read();
      int ans = 0;
      for (int i = 1; i <= cnt; ++i)
        if (vc[i].x <= x)
          ans = (ans + 1ll * C(x - vc[i].x + k - 1, k - 1) * vc[i].y % MOD) % MOD;
      printf ("%d\n", ans);
    }
  }
}
