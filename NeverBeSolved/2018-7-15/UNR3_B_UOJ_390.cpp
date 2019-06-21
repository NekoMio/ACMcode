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
const int MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int f[2][1000][35];
int C[1000][1000];
int Get_Ans(int x) {
  for (int i = 1; i <= n; ++i) {
    
  }
}
int main() {
  int n = read(), m = 0;
  for (int i = 1; i <= n; ++i) a[i] = read(), m += a[i];
  for (int i = 0; i <= n; ++i) {
    C[i][0] = 0;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }
  int now = 0;
  f[0][0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int j = 0; j <= m; ++j)
      for (int k = 0; k < i; ++k)
        if (f[now ^ 1][j][k]) {
          f[now][j][k] = (f[now][j][k] + f[now ^ 1][j][k]) % MOD;
          for (int l = 0; l < a[i]; ++l)
            f[now][j + l][k + 1] =
                (f[now][j + l][k + 1] + 1ll * f[now ^ 1][j][k] * C[j + l][l] % MOD) % MOD;
        }
  }
  for (int i = 1; i <= n; ++i)
    printf ("%d\n", Get_Ans(i));
}
