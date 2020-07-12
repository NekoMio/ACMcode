#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int Val[]
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    long long l, r, k;
    scanf ("%lld%lld%lld", &l, &r, &k);
    long long ans = 0, tans = 0;
    for (long long i = l; i <= r; i++) {
      if (i == 1) {
        ans++;
        continue;
      }
      int t = 1;
      for (int j = 2; j <= tot; j++) {
        if (tmp[j] != tmp[j - 1]) {
          tans = tans * (t * k + 1) % MOD;
          t = 1;
        } else t++;
      }
      tans = tans * (t * k + 1) % MOD;
      ans = (ans + tans) % MOD;
    }
    printf ("%lld\n", ans);
  }
}