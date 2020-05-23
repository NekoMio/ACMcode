#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7, Inv2 = 500000004;
long long bin[25], D[25];
int Calc(long long a, int L) {
  if (a <= 7) return 0;
  int T = a / bin[L];
  // long long d = (bin[L] * 2 - a % bin[L] - 1) % MOD;
  long long ans = (bin[L] * 2 - a % bin[L] - 1) % MOD * ((a % bin[L]) % MOD) % MOD * Inv2 % MOD * (a / bin[L]) % MOD;
  ans = (ans + 1ll * Calc(a % bin[L], L - 1) * (a / bin[L] + 1) % MOD) % MOD;
  ans = (ans + 1ll * D[L] * (1 + T) * T % MOD * Inv2 % MOD + bin[L] % MOD * ((bin[L] - 1) % MOD) % MOD * Inv2 % MOD * T * (T - 1) % MOD * Inv2 % MOD) % MOD;
  return ans;
}
int main() {
  int N;
  scanf ("%d", &N);
  long long a = 0;
  bin[0] = 1;
  for (int i = 1; i <= 22; i++) bin[i] = bin[i - 1] * 7;
//   for (int i = 1; i <= 22; i++) printf ("%lld\n", bin[i]);
  for (int i = 1; i <= 22; i++) D[i] = Calc(bin[i] - 1, i - 1);
  for (int i = 1; i <= N; i++) {
    scanf ("%lld", &a);
    int L;
    for (L = 22; L >= 1; L--) {
      if (a >= bin[L])
        break;
    }
    printf ("Case %d: %d\n", i, Calc(a + 1, L));
  }
}