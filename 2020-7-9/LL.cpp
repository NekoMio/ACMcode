#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int a[2005], b[2005];
int F[2005][2005][2];
int Sum[2005][2];
#define lowbit(_) ((_) & (-(_)))
void Add(int x, int b, int o) {
    for (int j = b; j <= 2000; j += lowbit(j)) {
      Sum[j][o] = (Sum[j][o] + x) % MOD;
    }
}
int Query(int b, int o) {
  int ans = 0;
  for (int j = b; j > 0; j -= lowbit(j)) {
    ans = (ans + Sum[j][o]) % MOD;
  }
  return ans;
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, m;
    scanf ("%d%d", &n, &m);
    memset(F, 0, sizeof(F));
    memset(Sum, 0, sizeof(Sum));
    for (int i = 1; i <= n; i++)
      scanf ("%d", &a[i]);
    for (int i = 1; i <= m; i++)
      scanf ("%d", &b[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (F[i - 1][j][0]) Add(F[i - 1][j][0], b[j], 0);
        if (F[i - 1][j][1]) Add(F[i - 1][j][1], b[j], 1);
        if (a[i] == b[j]) {
          F[i][j][0] = 1;
          F[i][j][0] = (F[i][j][0] + ((Query(2000, 1) - Query(a[i], 1)) % MOD + MOD) % MOD) % MOD;
          F[i][j][1] = (F[i][j][1] + Query(a[i] - 1, 0)) % MOD;
          ans = ((ans + F[i][j][0]) % MOD + F[i][j][1]) % MOD;
        }
      }
      memset (Sum, 0, sizeof(Sum));
      for (int j = 1; j <= m; j++) {
        F[i][j][0] = (F[i][j][0] + F[i - 1][j][0]) % MOD;
        F[i][j][1] = (F[i][j][1] + F[i - 1][j][1]) % MOD;
      }
    }
    printf("%d\n", ans);
  }
}