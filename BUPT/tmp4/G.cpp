#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int bin[5005];
int BinX[5005], BinY[5005];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int main() {
  int N, R, C, K;
  scanf ("%d%d%d%d", &N, &R, &C, &K);
  for (int i = 1; i <= 5000; i++) bin[i] = pow_mod(i, N);
  int ans = 0;
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= R - i + 1; j++) {
      BinX[i] = (BinX[i] + 1ll * (bin[j] - bin[j - 1] + MOD) * (bin[R - i + 2 - j] - bin[R - i + 1 - j] + MOD) % MOD) % MOD;
    }
  }
  for (int i = 1; i <= C; i++) {
    for (int j = 1; j <= C - i + 1; j++) {
      BinY[i] = (BinY[i] + 1ll * (bin[j] - bin[j - 1] + MOD) * (bin[C - i - j + 2] - bin[C - i + 1 - j] + MOD) % MOD) % MOD;
    }
  }
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      if (i * j >= K) {
        ans = (ans + (1ll * BinX[i] * BinY[j]) % MOD) % MOD;
        // printf ("%d %d %lld\n", i, j, (1ll * BinX[i] * BinY[j]) % MOD);
      }
    }
  }
  printf ("%d\n", ans);
}