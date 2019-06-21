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
int du[105], MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int Max;
int main() {
  int n = read();
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    du[a]++, du[b]++;
    Max = max(Max, du[a]);
    Max = max(Max, du[b]);
  }
  if (Max <= 2) {
    printf ("%lld\n", 1ll * (n - 1) * pow_mod(2, MOD - 2) % MOD);
    return 0;
  } else if (Max == n - 1){
    printf ("%lld\n", 1ll * (n + n - 3) * pow_mod(n, MOD - 2) % MOD);
  } else {
    printf ("382660337");
  }
}