#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
char s[MAXN];
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
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int pre[55][55], Suf[55][55], Sum[MAXN][55], Inv[MAXN][55];
int Calc(int l, int r) {
  int ans = 0;
  for (int i = 0; i <= 52; ++i) {
    ans = (ans + 1ll * Sum[r][i] * Inv[l - 1][i] % MOD) % MOD;
  }
  return (Sum[r][52] - ans + MOD) % MOD;
}
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    if (s[i] <= 'z' && s[i] >= 'a') 
      s[i] = s[i] - 'a';
    else s[i] = s[i] - 'A' + 26;
  }
  for (int i = 0; i <= 52; ++i)
    pre[i][i] = Suf[i][i] = Sum[0][i] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= 52; ++j) {
      Sum[i][j] = (((Sum[i - 1][j] * 2) % MOD - pre[s[i]][j]) % MOD + MOD) % MOD;
      pre[s[i]][j] = Sum[i - 1][j];
      Inv[i][j] = Suf[s[i]][j];
      Suf[s[i]][j] = (((Suf[s[i]][j] * 2) % MOD - Inv[i - 1][j]) % MOD + MOD) % MOD;
    }
  }
  int Q = read(), a = read(), b = read(), p = read(), q = read(), r = read();
  int ans = 0;
  for (int i = 1; i <= Q; ++i) {
    int tmp = a;
    a = (1ll * a * p + 1ll * q * b + ans + r) % MOD;
    b = (1ll * b * p + 1ll * q * tmp + ans + r) % MOD;
    int l = min(a % n, b % n) + 1;
    int r = max(a % n, b % n) + 1;
    ans = Calc(l, r) % MOD;
  }
  printf ("%d\n", ans);
}