#include <bits/stdc++.h>
using namespace std;
bitset<501> a[20], tp;
char s[506];
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
      scanf ("%s", s);
      a[i].reset();
      for (int j = 0; j < n; j++) a[i][j] = (s[j] == '1');
    }
    int N = 1 << m, num, ans = 0x3f3f3f3f;
    for (int i = 0; i < N; i++) {
      tp.reset();
      num = 0;
      for (int j = 1; j <= m; j++) {
        if ((1 << (j - 1)) & i) {
          tp |= a[j];
          num ++;
        }
      }
      if (tp.count() == n) ans = min(ans, num);
    }
    if (ans == 0x3f3f3f3f) ans = -1;
    printf ("%d\n", ans);
  }
}