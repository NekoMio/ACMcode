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
const int MOD = 1000000007;
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
char s[100005];
int num[10], F[100005], Inv[100005];
long long C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * Inv[n - m] % MOD * Inv[m] % MOD;
}
long long Solve(int x) {
  int ans = 0;
  for (int i = 0; i <= 3; ++i) {
    ans = (ans + 1ll * C(x - 1, i) * Inv[i + 1] % MOD * F[x] % MOD) % MOD;
  }
  return ans;
}
int d[10];
int f[5][1005];
int Calc(int m) {
  int ans = 0;
  memset(f, 0, sizeof(f));
  f[0][0] = 1;
  for (int i = 1; i <= 4; ++i) {
    int val = max(num[i], num[9 - i]) - min(num[i], num[9 - i]);
    int liv = (max(num[i], num[9 - i]) - min(num[i], num[9 - i])) & 1;
    for (int j = 0; j <= m; ++j) {
      for (int l = 0; l <= m; ++l)
        if (j + l <= m && l >= val && ((l & 1) ^ liv) == 0) {
          f[i][j + l] = (f[i][j + l] +
                         1ll * f[i - 1][j] * C(m - j, l) % MOD *
                             C(l, val + (l - val) / 2) % MOD) %
                        MOD;
        }
    }
  }
  for (int i = 0; i <= m; ++i) {
    for (int l = (num[9] == -1); l <= i; l++) {
      if (l + num[9] <= i - l + num[0]) {
        ans = (ans + f[4][m - i] * C(i, l) % MOD) % MOD;
      }
    }
  }
  return ans;
}
int main() {
  scanf("%s", s + 1);
  F[0] = 1;
  for (int i = 1; i <= 100000; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Inv[100000] = pow_mod(F[100000], MOD - 2);
  for (int i = 100000 - 1; i >= 0; --i)
    Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  int n = strlen(s + 1);
  int m = 0;
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '?')
      m++;
    else
      num[s[i] - '0']++;
  }
  int ans = 0;
  for (int i = 1; i <= 5; ++i) {
    num[i]--, num[10 - i]--;
    ans = (ans + Calc(m)) % MOD;
    num[i]++, num[10 - i]++;
  }
  printf("%d\n", ans);
}
