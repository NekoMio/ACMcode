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
struct Matrix {
  int a[65][65], n;
  Matrix (int _n = 0) {
    memset (a, 0, sizeof (a));
    n = _n;
  }
  Matrix operator * (const Matrix &b) const {
    Matrix ans(n);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
          ans.a[i][k] = (ans.a[i][k] + 1ll * a[i][j] * b.a[j][k] % MOD) % MOD;
        }
      }
    }
    return ans;
  }
}A, C;
int ans, n, m;
int Ans[100];
void Update() {
  memset (Ans, 0, sizeof (Ans));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      (Ans[(i - 1) & (j - 1)] += A.a[i][j]) %= MOD;
    }
  }
  for (int i = 0; i <= n - 1; ++i) printf ("%d ", Ans[i]);
  printf ("\n");
  for (int i = 0; i <= n - 1; ++i)
    ans = ans ^ Ans[i];
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      A.a[i][j] = read();
    }
  }
  A.n = n;
  Update();
  C = A;
  for (int i = 2; i <= m; ++i) {
    A = A * C;
    Update();
  }
  printf ("%d\n", ans);
  while (1);
}