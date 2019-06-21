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
const int MAXN = 1e7;
const int MOD = 1e9 + 7;
int F[MAXN + 2], Sum[MAXN + 2];
int Calc(int n) {
  int ans = ((2ll * F[n - 1] + F[n - 2] - Sum[n - 4] - 1) % MOD + MOD) % MOD;
  return (F[n] - ans + MOD) % MOD;
}
int main() {
  // freopen ("game.in", "r", stdin);
  // freopen ("game.out", "w", stdout);
  int T = read();
  F[0] = 1;
  for (int i = 1; i <= MAXN; ++i) F[i] = 1ll * F[i - 1] * i % MOD;
  Sum[0] = 1;
  for (int i = 1; i <= MAXN; ++i) Sum[i] = (Sum[i - 1] + F[i]) % MOD;
  for (int i = 1; i <= MAXN; ++i) Sum[i] = (Sum[i] + Sum[i - 1]) % MOD;
  while (T--) {
    printf ("%d\n", Calc(read()));
  }
}
