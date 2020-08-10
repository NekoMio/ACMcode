#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
long long tmp[100];
int tot;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
long long mul(long long a, long long b, long long z) {
  return (a * b - (long long)(((long double)a * b + 0.5) / (long double)z) * z + z) % z;
}
long long pow_mod(long long a, long long b, long long p) {
  a %= p;
  long long ans = 1;
  while (b) {
    if (b & 1) ans = mul(ans, a, p);
    b >>= 1;
    a = mul(a, a, p);
  }
  return ans;
}
bool Miller_Rabin(long long x) {
  if (x == 1) return 0;
  for (int i = 0; i <= 9; ++i) {
    if (x == prime[i]) return 1;
    if (x % prime[i] == 0) return 0;
  }
  long long y = x - 1;
  int k = 0;
  for (; !(y & 1); y >>= 1) k++;
  for (int i = 0; i < 10; ++i) {
    long long z = rand() % (x - 1) + 1;
    long long c = pow_mod(z, y, x), d;
    for (int j = 0; j < k; ++j, c = d)
      if ((d = mul(c, c, x)) == 1 && c != 1 && c != x - 1)
        return 0;
    if (d != 1) return 0;
  }
  return 1;
}
long long Pollard_Rho(long long x, int y) {
  long long i = 1, k = 2, c = rand() % (x - 1) + 1;
  long long d = c;
  while (1) {
    i++;
    c = (mul(c, c, x) + y) % x;
    long long g = __gcd((d - c + x) % x, x);
    if (g != 1 && g != x) return g;
    if (c == d) return x;
    if (i == k) d = c, k <<= 1;
  }
}
void Divide(long long x, int c) {
  if (x == 1) return;
  if (Miller_Rabin(x)) return tmp[++tot] = x, void();
  long long z = x, tp = c;
  while (z >= x) z = Pollard_Rho(z, c--);
  Divide(z, tp), Divide(x / z, tp);
}
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
      tot = 0;
      tans = 1;
      Divide(i, 300000);
      sort(tmp + 1, tmp + tot + 1);
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