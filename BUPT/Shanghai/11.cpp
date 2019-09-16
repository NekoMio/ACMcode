#include <bits/stdc++.h>
using namespace std;
#define int long long
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
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
struct Matrix {
  long long a[75][75], n;
  Matrix() {
    memset(a, 0, sizeof(a));
    n = 0;
  }
  void clear() {
    memset(a, 0, sizeof(a));
    n = 0;
  }
  long long *operator[](int x) { return a[x]; }
  const long long *operator[](const int x) const { return a[x]; }
  Matrix operator*(const Matrix b) {
    Matrix ans;
    ans.n = n;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++)
          ans[i][j] = (ans[i][j] + 1ll * a[i][k] * b[k][j] % MOD) % MOD;
    return ans;
  }
  Matrix operator^(long long b) {
    Matrix ans, a = *this;
    ans.n = n;
    for (int i = 1; i <= n; i++) ans[i][i] = 1;
    while (b) {
      if (b & 1) ans = ans * a;
      b >>= 1;
      a = a * a;
    }
    return ans;
  }
} trans;
long long a[100][100];
void gauss(int n) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n + 1; j++) a[i][j] = (MOD + a[i][j]) % MOD;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++)
      while (a[j][i]) {
        int t = a[i][i] / a[j][i];
        for (int k = i; k <= n + 1; k++) {
          a[i][k] = (a[i][k] - a[j][k] * t % MOD + MOD) % MOD;
          swap(a[i][k], a[j][k]);
        }
      }
  }
  for (int i = n; i >= 1; i--) {
    a[i][n + 1] = a[i][n + 1] * pow_mod(a[i][i], MOD - 2) % MOD;
    for (int j = i - 1; j >= 1; j--) {
      a[j][n + 1] = (a[j][n + 1] - a[j][i] * a[i][n + 1] % MOD + MOD) % MOD;
    }
  }
}
long long A[150];
signed main() {
  int T = read();
  while (T--) {
    memset(a, 0, sizeof(a));
    trans.clear();
    int k = read(), n = read();
    for (int i = 1; i <= k * 2; i++) A[i] = read();
    if (n <= 2 * k) {
      long long ans = 0;
      for (int i = 1; i <= n; i++)
        ans = (ans + A[i]) % MOD;
      printf ("%lld\n", ans);
    } else {
      for (int i = k + 1; i <= 2 * k; i++) {
        for (int j = i - k; j < i; j++) a[i - k][j - (i - k) + 1] = A[j];
        a[i - k][k + 1] = A[i];
      }
      gauss(k);
      trans.n = k + 1;
      for (int i = 1; i <= k - 1; i++)
        trans[i][i + 1] = 1;
      for (int i = 1; i <= k; i++)
        trans[k][i] = trans[k + 1][i] = a[i][k + 1];
      trans[k + 1][k + 1] = 1;
      trans = trans ^ (n - 2 * k);
      long long Sum = 0;
      for (int i = 1; i <= 2 * k; i++) Sum = (Sum + A[i]) % MOD;
      long long ans = 0;
      for (int i = 1; i <= k; i++)
        ans = (ans + 1ll * A[i + k] * trans[k + 1][i] % MOD) % MOD;
      ans = (ans + Sum * trans[k + 1][k + 1] % MOD) % MOD;
      printf ("%lld\n", ans);
    }
  }
  // while (1);
}