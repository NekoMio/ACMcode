#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 10000005
#define int long long
using namespace std;
int T, m, n, k, p, q, r, MOD;
int a[N], q1[N], en, he;
signed main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &m, &k, &p, &q, &r, &MOD);
    for (int i = 1; i <= k; i++) scanf("%lld", &a[i]);
    for (int i = k + 1; i <= n; i++)
      a[i] = (1ll * p * a[i - 1] % MOD + 1ll * q * i % MOD + r) % MOD;
    he = 1, en = 1;
    long long A = 0, B = 0;
    q1[1] = n;
    for (int i = n - 1; i > n - m + 1; i--) {
      while (a[q1[en]] <= a[i] && en >= he) en--;
      en++;
      q1[en] = i;
    }
    for (int i = n - m + 1; i > 0; i--) {
      while (a[q1[en]] <= a[i] && en >= he) en--;
      en++;
      q1[en] = i;
      while (q1[he] >= i + m) he++;
      A += i ^ a[q1[he]];
      B += i ^ (en - he + 1);
    }
    printf("%lld %lld\n", A, B);
  }
  return 0;
}