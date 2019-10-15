#include <bits/stdc++.h>
using namespace std;
int main() {
  int T, cnt = 0;
  scanf("%d", &T);
  while (T--) {
    cnt++;
    int n, k, mod;
    long long f = 1;
    scanf("%d%d%d", &n, &k, &mod);
    if (k < n) {
      for (int i = 1; i <= k; i++) f = f * i % mod;
      long long Ans = f * k * (n - k) % mod;
      Ans = (Ans +
             ((n - k) * (n - k - 1) / 2 + (n - k - 1) * (n - k - 2) / 2 + 1) *
                 f) %
            mod;
      Ans = (Ans + f * (n - k - 1)) % mod;
      printf("Case #%d: %lld\n", cnt, Ans);
    } else {
      for (int i = 1; i <= n; i++) f = f * i % mod;
      printf("Case #%d: %lld\n", cnt, f);
    }
  }
  // while (1);
}