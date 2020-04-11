#include <bits/stdc++.h>
using namespace std;
long long exgcd(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long ret = exgcd(b, a % b, x, y);
  long long tmp = x;
  x = y;
  y = tmp - a / b * y;
  return ret;
}
long long mul(long long a, long long b, long long z) {
  return (a * b - (long long)(((long double)a * b + 0.5) / (long double)z) * z + z) % z;
}
long long pow_mod(long long a, long long b, long long MOD) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = mul(a, ans, MOD);
    b >>= 1;
    a = mul(a, a, MOD);
  }
  return ans;
}
int main() {
  int T, cnt = 0;
  scanf("%d", &T);
  long long n, c, x, y;
  while (T--) {
    printf("Case %d: ", ++cnt);
    scanf("%lld%lld", &n, &c);
    int p1 = sqrt(n), p2;
    while (1) {
      if (n % p1 == 0) {
        p2 = n / p1;
        break;
      }
      p1++;
    }
    exgcd((1ll << 30) + 3, 1ll * (p1 - 1) * (p2 - 1), x, y);
    printf ("%lld\n", pow_mod(c, (x + 1ll * (p1 - 1) * (p2 - 1)) % (1ll * (p1 - 1) * (p2 - 1)), n));
  }
}