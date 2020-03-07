#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
const int MOD = 1e9 + 7;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
char a[MAXN], b[MAXN];
long long F[MAXN];
int Sumlen;
int C(int n, int m) {
  if (n < m) return 0;
  if (n < 0 || m < 0) return 0;
  return F[n] * pow_mod(F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int Calc1(int len, int c00, int c01, int c10, int c11) {
  return 1ll * C(c11 + c01, c01) * C(c00 + c10 - 1, c10 - 1) % MOD;
}
int Calc0(int len, int c00, int c01, int c10, int c11) {
  return 1ll * C(c00 + c10, c10) * C(c11 + c01 - 1, c01 - 1) % MOD;
}
int Calc(char *s, int c00, int c01, int c10, int c11, int tp) {
  if (c10 != c01 && c10 != c01 + 1) return 0;
  if (strlen(s + 1) < Sumlen) return 0;
  if (strlen(s + 1) > Sumlen) return Calc1(Sumlen, c00, c01, c10, c11);
  long long ans = 0;
  for (int i = 2; i < Sumlen; i++) {
    if (s[i] == '0') {
      if (s[i - 1] == '0') c00--;
      if (s[i - 1] == '1') c10--;
    } else {
      (ans += Calc0(Sumlen - i, c00 - 1 - (s[i - 1] == '0'), c01, c10 - (s[i - 1] == '1'), c11)) %= MOD;
      (ans += Calc1(Sumlen - i, c00 - (s[i - 1] == '0'), c01, c10 - 1 - (s[i - 1] == '1'), c11)) %= MOD;
      if (s[i - 1] == '0') c01--;
      if (s[i - 1] == '1') c11--;
    }
  }
  if (s[Sumlen - 1] == '0') {
    if (c00 - 1 == 0 && c11 == 0 && c01 == 0 && c10 == 0) ans++;
    if (s[Sumlen] == '1') {
      if (c00 == 0 && c11 == 0 && c01 - 1 == 0 && c10 == 0) ans++;
      c01--;
    } else {
      c00--;
    }
  } else {
    if (c00 == 0 && c11 == 0 && c01 == 0 && c10 - 1 == 0) ans++;
    if (s[Sumlen] == '1') {
      if (c00 == 0 && c11 - 1 == 0 && c01 == 0 && c10 == 0) ans++;
      c11--;
    } else {
      c10--;
    }
  }
  return (ans - tp * (c00 == 0 && c11 == 0 && c01 == 0 && c10 == 0)) % MOD;
}
int main() {
  scanf ("%s%s", a + 1, b + 1);
  int c00, c01, c10, c11;
  scanf ("%d%d%d%d", &c00, &c01, &c10, &c11);
  F[0] = 1;
  Sumlen = c00 + c01 + c10 + c11 + 1;
  for (int i = 1; i <= MAXN - 1; i++) F[i] = F[i - 1] * i % MOD;
  printf ("%d\n", ((Calc(b, c00, c01, c10, c11, 0) - Calc(a, c00, c01, c10, c11, 1)) % MOD + MOD) % MOD);
}