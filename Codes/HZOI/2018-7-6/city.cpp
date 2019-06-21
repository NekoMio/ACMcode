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
const int MOD = 22222223;
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int f[105][105], n, m;
int C[105][105];
int DP(int h1, int t1, int h2, int t2, int val) {
  memset (f, 0, sizeof (f));
  int num = t2 - h2 + 1;
  f[h1 - 1][0] = 1;
  for (int i = h1; i <= t1; ++i) {
    for (int j = 0; j <= num; ++j) {
      for (int k = 0; k <= num; ++k) if (j + k <= num) {
        if (k != 0)
          f[i][j + k] = (f[i][j + k] + 1ll * f[i - 1][j] * pow_mod(val + 1, m - t2 + j) % MOD * C[num - j][k] % MOD * pow_mod(val, num - j - k) % MOD) % MOD;
        else
          f[i][j] = (f[i][j] + 1ll * f[i - 1][j] * pow_mod(val, num - j) % MOD * ((pow_mod(val + 1, m - t2 + j) - pow_mod(val, m - t2 + j) + MOD) % MOD) % MOD) % MOD;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= num; ++i) {
    ans = (ans + 1ll * f[t1][i] * pow_mod(val + 1, i * (n - t1)) % MOD * pow_mod((pow_mod(val + 1, n - t1) - pow_mod(val, n - t1) + MOD) % MOD, num - i) % MOD) % MOD;
  }
  return ans;
}
int A[105], B[105];
int main() {
  freopen ("city.in", "r", stdin);
  freopen ("city.out", "w", stdout);
  n = read(), m = read();
  for (int i = 1; i <= n; ++i) A[i] = read();
  for (int i = 1; i <= m; ++i) B[i] = read();
  for (int i = 0; i <= m; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }
  sort(A + 1, A + n + 1);
  sort(B + 1, B + m + 1);
  if (A[n] != B[m]) return printf ("No solution!"), 0;
  int p1 = 1, p2 = 1, ans = 1;
  for (; p1 <= n && p2 <= m;) {
    if (A[p1] != B[p2]) {
      if (A[p1] < B[p2]) {
        ans = 1ll * ans * ((pow_mod(A[p1] + 1, m - p2 + 1) - pow_mod(A[p1], m - p2 + 1) + MOD) % MOD) % MOD;
        p1++;
      } else {
        ans = 1ll * ans * ((pow_mod(B[p2] + 1, n - p1 + 1) - pow_mod(B[p2], n - p1 + 1) + MOD) % MOD) % MOD;
        p2++;
      }
      // continue;
    } else {
      int i = p1, j = p2;
      while (p1 < n && A[p1 + 1] == A[i]) p1++;
      while (p2 < m && B[p2 + 1] == B[j]) p2++;
      ans = 1ll * ans * DP(i, p1, j, p2, A[p1]) % MOD;
      p1++, p2++;
    }
  }
  printf ("%d\n", ans);
}
