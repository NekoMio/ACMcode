#include <bits/stdc++.h>
using namespace std;
int p[20];
int F[(1 << 12) + 1][13][701];
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
int main() {
  int n, x;
  scanf ("%d%d", &n, &x);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &p[i]);
  }
  int Mx = 0;
  for (int i = 1; i <= n; i++) Mx = max(Mx, p[i]);
  int N = (1 << n) - 1;
  for (int i = 1; i <= n; i++) {
    if (Mx != p[i]) F[1 << (i - 1)][i][(Mx - p[i] + 1) * n] = 1;
  }
  for (int S = 1; S <= N; S++) {
    for (int j = 1; j <= n; j++) {
      for (int r = 1; r <= x; r++) {
        if (F[S][j][r]) {
          for (int l = 1; l <= n; l++) {
            if (!(S & (1 << (l - 1))) && (r + max(p[j] - p[l] + 1, 0) * (n - Num(S))) <= x) {
              F[S | (1 << (l - 1))][l][r + max(p[j] - p[l] + 1, 0) * (n - Num(S))] += F[S][j][r];
            }
          }
        }
      }
    }
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= x; j++) {
      ans = ans + F[N][i][j];
    }
  }
  printf ("%lld\n", ans);
}