#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define mmin(a, b) (a < b ? a : b)
#define mmax(a, b) (a > b ? a : b)
#define ll long long
struct node {
  int le, ri, h;
} q[510];
int T, n, m, A, cnt1, cnt2, w[1010], jie[1010], t[1010], head, zh[1010],
    to[1010];
const int mod = 998244353;
ll ans, f[1010][1010];
void Main();
ll ksm(int, int);
ll dp(int);
int main() {
  scanf("%d", &T);
  while (T--) Main();
  return 0;
}
void Main() {
  cnt1 = 0;
  cnt2 = 0;
  scanf("%d%d%d", &n, &m, &A);
  for (int i = 1; i <= m; i++) scanf("%d%d%d", &q[i].le, &q[i].ri, &q[i].h);
  for (int i = 1; i <= m; i++) {
    jie[++cnt1] = q[i].le;
    jie[++cnt1] = q[i].ri + 1;
    w[++cnt2] = q[i].h;
  }
  jie[++cnt1] = 1;
  jie[++cnt1] = n + 1;
  sort(jie + 1, jie + cnt1 + 1);
  cnt1 = unique(jie + 1, jie + cnt1 + 1) - jie - 1;
  sort(w + 1, w + cnt2 + 1);
  cnt2 = unique(w + 1, w + cnt2 + 1) - w - 1;
  for (int i = 1; i <= cnt1; i++) zh[i] = A + 1;
  for (int i = 1; i <= m; i++) {
    q[i].le = lower_bound(jie + 1, jie + cnt1 + 1, q[i].le) - jie;
    q[i].ri = lower_bound(jie + 1, jie + cnt1 + 1, q[i].ri + 1) - jie;
    for (int j = q[i].le; j < q[i].ri; j++) zh[j] = mmin(zh[j], q[i].h);
  }
  ans = 1;
  for (int i = 1; i <= cnt2; i++) {
    ans = ans * dp(i) % mod;
  }
  for (int i = 1; i < cnt1; i++)
    if (zh[i] == A + 1) ans = ans * ksm(A, jie[i + 1] - jie[i]) % mod;
  printf("%lld\n", ans);
}
ll ksm(int x, int y) {
  ll z = x, sum = 1;
  while (y) {
    if (y & 1) sum = sum * z % mod;
    y >>= 1;
    z = z * z % mod;
  }
  return sum;
}
ll dp(int x) {
  ll sum = 0;
  head = 0;
  for (int i = 1; i < cnt1; i++)
    if (zh[i] == w[x]) {
      t[++head] = i;
      memset(f[head], 0, sizeof(f[head]));
      to[head] = 0;
    }
  if (!head) return 0;
  for (int i = 1, le, ri; i <= m; i++)
    if (q[i].h == w[x]) {
      le = lower_bound(t + 1, t + head + 1, q[i].le) - t;
      ri = lower_bound(t + 1, t + head + 1, q[i].ri) - t;
      ri--;
      if (le > ri) return 0;
      to[ri] = mmax(to[ri], le);
    }
  f[0][0] = 1;
  ll v1, v2;
  for (int i = 1; i <= head; i++) {
    v1 = ksm(w[x], jie[t[i] + 1] - jie[t[i]]),
    v2 = ksm(w[x] - 1, jie[t[i] + 1] - jie[t[i]]);
    for (int j = i - 1; j >= 0; j--) {
      if (j >= to[i]) (f[i][j] += f[i - 1][j] * v2) %= mod;
      (f[i][i] += f[i - 1][j] * (v1 - v2 + mod)) %= mod;
    }
  }
  for (int i = 0; i <= head; i++) (sum += f[head][i]) %= mod;
  return sum;
}
