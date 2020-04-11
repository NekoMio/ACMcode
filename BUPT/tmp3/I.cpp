#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
long long A[MAXN], B[MAXN], N;
long long Inv;
int rev[MAXN];
long long pow_mod(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
void FFt(long long *a, int op) {
  long long w, wn, t;
  for (int i = 0; i < N; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 2; k <= N; k <<= 1) {
    wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
    for (int j = 0; j < N; j += k) {
      w = 1;
      for (int i = 0; i < (k >> 1); i++, w = w * wn % MOD) {
        t = a[i + j + (k >> 1)] * w % MOD;
        a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
        a[i + j] = (a[i + j] + t) % MOD;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < N; i++) a[i] = a[i] * Inv % MOD;
}
void FFt(const int *a, const int *b, int *res, int n) {
  N = 1;
  while (N < n) N <<= 1;
  Inv = pow_mod(N, MOD - 2);
  for (int i = 0; i < N; i++)
    if (i & 1)
      rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else
      rev[i] = (rev[i >> 1] >> 1);
  for (int i = 0; i < N; i++) A[i] = a[i], B[i] = b[i];
  FFt(A, 1), FFt(B, 1);
  for (int i = 0; i < N; i++) A[i] = A[i] * B[i] % MOD;
  FFt(A, -1);
  for (int i = 0; i < N; i++) res[i] = A[i];
}
int F[MAXN];
int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * F[n] * pow_mod(1ll * F[m] * F[n - m] % MOD, MOD - 2);
}
int a[MAXN];
int main() {
  int T;
  F[0] = 1;
  for (int i = 1; i <= MAXN - 1; i++) F[i] = 1ll * F[i - 1] * i % MOD;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a[i]);
    }
    int num[4] = {0}, c;
    for (int i = 1; i <= m; i++) {
      scanf("%d", &c);
      num[c]++;
    }
  }
}