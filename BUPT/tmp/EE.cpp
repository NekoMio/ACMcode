#include <bits/stdc++.h>
using namespace std;
#define int long long
int MOD, B, D;
struct data {
  long long A, C;
  data operator * (data &c) {
    int a = 1ll * A * c.A % MOD;
    int b1 = 1ll * c.C * A % MOD;
    int c1 = 1ll * C * c.A % MOD;
    int d1 = 1ll * C * c.C % MOD;
    return data{(a + d1 * D) % MOD, (b1 + c1) % MOD};
  }
  data operator - (data c) {
    return data{((A - c.A) % MOD + MOD) % MOD, ((C - c.C) % MOD + MOD) % MOD};
  }
};
data pow_mod(data a, long long b) {
  data ans;
  ans.A = 1, ans.C = 0;
  while (b) {
    if (b & 1) ans = ans * a;
    b >>= 1;
    a = a * a;
  }
  return ans;
}
void div(int b, int &c, int &d){
  c = 1, d = 1;
  int num = 0, v = 2;
  while (b > 1) {
    if (v * v > b) break;
    num = 0;
    while (b % v == 0) {
      num++;
      b /= v;
    }
    while (num >= 2) {
      c *= v;
      num -= 2;
    }
    if (num == 1) d *= v;
    v++;
  }
  if (b != 1) d *= b;
}
data ans;
signed main() {
  int T;
  scanf ("%lld", &T);
  int a;
  long long n;
  while (T--) {
    scanf ("%lld%lld%lld%lld", &a, &B, &n, &MOD);
    int c;
    MOD *= 2;
    div(B, c, D);
    // long long Inv2 = pow_mod(2, MOD - 2);
    ans = pow_mod(data{a % MOD, c % MOD}, n) - pow_mod(data{a % MOD, MOD - c % MOD}, n);
    ans.A /= 2;
    ans.C /= 2;
    MOD /= 2;
    if (D == 1) {
      printf ("%d %lld %d\n", 1, (ans.A + ans.C) % MOD, 1);
    } else if (ans.A == 0) {
      printf ("%d %lld %lld\n", 1, ans.C, D);
    } else {
      printf ("%d %lld %d %lld %lld\n", 2, ans.A, 1, ans.C, D);
    }
  }
}