#include <bits/stdc++.h>
using namespace std;
int f[200005], Pow[200005], Inv[200005], n;
const int MOD = 1000000007;
const int Inv2 = (MOD + 1) / 2;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int C(int x, int y) {
  if (x < y) return 0;
  return 1ll * f[x] * Inv[y] % MOD * Inv[x - y] % MOD;
}
int Calc(int num1, int num2) {
  int val1 = n - num1 - 1, val2 = n - num2 - 1;
  int ans = C(val1 + val2, val1);
  return 1ll * ans * Pow[2 * n - 1 - val1 - val2] % MOD;
}
int main() {
  freopen ("beijing.in", "r", stdin);
  freopen ("beijing.out", "w", stdout);
  scanf ("%d", &n);
  Pow[0] = 1;
  for (int i = 1; i <= 2 * n; ++i) Pow[i] = Pow[i - 1] * 2 % MOD;
  f[0] = 1;
  for (int i = 1; i <= 2 * n; ++i) f[i] = 1ll * f[i - 1] * i % MOD;
  Inv[2 * n] = pow_mod(f[2 * n], MOD - 2);
  for (int i = 2 * n - 1; i >= 0; --i) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
  int num1 = 0, num2 = 0, x;
  for (int i = 1; ; ++i) {
    printf ("%d\n", Calc(num1, num2));
    scanf ("%d", &x);
    if (x == 1) num1++;
    else num2++;
    if (num1 == n || num2 == n) break;
  }
}

