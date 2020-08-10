#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 40;
int p1[maxn];
int c1[maxn];
int m1;
void divide(int n) {
  m1 = 0;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      p1[++m1] = i, c1[m1] = 0;
      while (n % i == 0) n /= i, c1[m1]++;
    }
  }
  if (n > 1) p1[++m1] = n, c1[m1] = 1;
}
int p2[maxn];
int c2[maxn];
int m2;
void divide2(int n) {
  m2 = 0;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      p2[++m2] = i, c2[m2] = 0;
      while (n % i == 0) n /= i, c2[m2]++;
    }
  }
  if (n > 1) p2[++m2] = n, c2[m2] = 1;
}
LL fpow(LL a, __int128 n, LL p) {
  LL ans = 1;
  while (n) {
    if (n & 1) ans = ans * a % p;
    a = a * a % p;
    n >>= 1;
  }
  return ans;
}
const LL MOD = 998244353;
int a, b, c, d, x, y;
int pp[100];
int cc1[100];
int cc2[100];
const int N = 3e6 + 10;
LL pos[N];
LL ans = 1;
LL Sum[N];
int main() {
  scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &x, &y);
  divide(x), divide2(y);
  int L = 1, R = 1, sz = 0;
  while (L <= m1 && R <= m2) {
    if (p1[L] == p2[R]) {
      pp[sz] = (p1[L]);
      cc1[sz] = (c1[L]);
      cc2[sz++] = (c2[R]);
      if (L != m1) L++;
      else break;
      if (R != m2) R++;
      else break;
      continue;
    }
    if (p1[L] < p2[R]) {
      if (L != m1) L++;
      else break;
      continue;
    }
    if (p1[L] > p2[R]) {
      if (R != m2) R++;
      else break;
      continue;
    }
  }
  for (int k = 0; k < sz; k++) {
    for (int j = c; j <= d; j++) {
      Sum[j] = Sum[j - 1] + (LL)j * cc2[k];
    }
    __int128 num = 0;
    for (int i = a, j = c; i <= b; i++) {
      while ((LL)j * cc2[k] <= (LL)i * cc1[k] && j <= d) j++;
      num += ((LL)i * cc1[k]) * (d - j + 1) + Sum[j - 1];
    }
    ans = (ans * fpow(pp[k], num, MOD)) % MOD;
  }
  printf("%lld\n", ans);
}
