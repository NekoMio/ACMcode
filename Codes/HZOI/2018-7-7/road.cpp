#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
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
int T;
int C[10][10];
struct Matrix {
  int a[71][71][7];
  int n;
  Matrix(int _n = 0) {
    memset (a, 0, sizeof (a));
    n = _n;
  }
}A[20], F[20], tt;
inline void Mul(const Matrix &a, const Matrix &b, Matrix &ans) {
  ans.n = a.n;
  int i, j, k;
  register int l, m;
  for (i = 1; i <= a.n; ++i)
    for (j = 1; j <= a.n; ++j)
      for (k = 1; k <= a.n; ++k)
        for (l = 0; l <= T; ++l) if (b.a[j][k][l])
          for (m = 0; l + m <= T; ++m) if (a.a[i][j][m])
            ans.a[i][k][l + m] = (ans.a[i][k][l + m] + 1ull * a.a[i][j][m] * b.a[j][k][l] % MOD * C[l + m][m]) % MOD;
}
int main() {
  // freopen ("road.in", "r", stdin);
  // freopen ("road.out", "w", stdout);
  A[0].n = read();
  int k = read(), q = read();
  T = read();
  for (int i = 0; i <= T; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
  }
  for (int i = 1; i <= A[0].n; ++i) {
    for (int j = 1; j <= A[0].n; ++j) {
      A[0].a[i][j][0] = read();
      for (int k = 1; k <= T; ++k) A[0].a[i][j][k] = A[0].a[i][j][0];
    }
  }
  for (int i = 1; i <= 19; ++i) Mul(A[i - 1], A[i - 1], A[i]);
  F[0].n = A[0].n;
  for (int i = 1; i <= F[0].n; ++i) F[0].a[i][i][0] = 1;
  for (int t = 1; t <= 19; ++t) {
    Mul(F[t - 1], A[t - 1], F[t]);
    for (int i = 1; i <= F[t].n; ++i)
      for (int j = 1; j <= F[t].n; ++j)
        for (int k = 0; k <= T; ++k)
          F[t].a[i][j][k] = (F[t].a[i][j][k] + F[t - 1].a[i][j][k]) % MOD;
  }
  Matrix Ans(A[0].n), tmp(A[0].n);
  for (int i = 1; i <= tmp.n; ++i) tmp.a[i][i][0] = 1;
  for (int i = 0; i <= 19; ++i) {
    if (k & (1 << i)) {
      memset (tt.a, 0, sizeof(tt.a));
      Mul(F[i], tmp, tt);
      for (int z = 1; z <= tt.n; ++z)
        for (int j = 1; j <= tt.n; ++j)
          for (int k = 0; k <= T; ++k)
            Ans.a[z][j][k] = (Ans.a[z][j][k] + tt.a[z][j][k]) % MOD;
      memset (tt.a, 0, sizeof(tt.a));
      Mul(tmp, A[i], tt);
      tmp = tt;
    }
  }
  for (int i = 1; i <= q; ++i) {
    int x = read(), y = read();
    printf ("%d\n", Ans.a[x][y][T]);
  }
}
