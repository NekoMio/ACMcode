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
const int MOD = 65537;
const int MAXN = 1e6 + 5;
struct Matrix {
  int a[505][505];
  int n, m;
  Matrix(int _n = 0, int _m = 0) {
    memset (a, 0, sizeof (a));
    n = _n, m = _m;
  }
  Matrix operator * (const Matrix &b) const {
    Matrix ans(n, b.m);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) if (a[i][j]) {
        for (int k = 1; k <= b.m; ++k) if (b.a[j][k]){
          ans.a[i][k] = (ans.a[i][k] + 1ll * a[i][j] * b.a[j][k]) % MOD;
        }
      }
    }
    return ans;
  }
  Matrix operator ^ (int b) {
    Matrix ans(n, m), a = *this;
    for (int i = 1; i <= n; ++i) ans.a[i][i] = 1;
    while (b) {
      if (b & 1) ans = ans * a;
      b >>= 1;
      a = a * a;
    }
    return ans;
  }
}A[30], B;
int f[MAXN], Sum[MAXN];
int main() {
  int n = read(), m = read();
  if (n <= 0) {
    f[0] = 1;
    Sum[0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
      if (i - m > 0) {
        f[i] = (Sum[i - 1] - Sum[i - m - 1] + MOD) % MOD;
      } else {
        f[i] = Sum[i - 1];
      }
      Sum[i] = (Sum[i - 1] + f[i]) % MOD;
    }
    printf ("%d\n", (f[n + 1] % MOD + MOD) % MOD);
  } else if (m <= 500) {
    A[0].n = A[0].m = m;
    for (int i = 1; i <= m; ++i) A[0].a[i][1] = 1;
    for (int i = 2; i <= m; ++i) A[0].a[i - 1][i] = 1;
    for (int i = 1; i <= 29; ++i) A[i] = A[i - 1] * A[i - 1];
    for (int i = 0; i <= 29; ++i) {
      for (int j = 1; j <= m; ++j) {
        for (int k = 1; k <= m; ++k) {
          printf ("A[%d].a[%d][%d]=%d,", i, j, k, A[i].a[j][k]);
        }
      }
    }
    B.n = 1, B.m = m;
    B.a[1][1] = 1;
    n++;
    for (int i = 0; i <= 29; ++i) {
      if (n & (1 << i)) B = B * A[i];
    }
    printf ("%d\n", B.a[1][1]);
  }
}
