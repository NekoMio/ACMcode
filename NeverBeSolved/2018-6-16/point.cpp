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
const int MOD = 1e9 + 9;
const int MAXN = 1e6;
int prime[MAXN + 1], mu[MAXN + 1], cnt, Sum[MAXN + 1];
bool isnprime[MAXN + 1];
void Get_mu() {
  mu[1] = 1;
  isnprime[1] = 1;
  for (int i = 2; i <= MAXN; ++i) {
    if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt; ++j) {
      if (i * prime[j] > MAXN) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= MAXN; ++i) Sum[i] = Sum[i - 1] + mu[i];
}
int a[55], b[55];
int Calc() {
  int n = read();
  for (int i = 1; i <= n; ++i)
    a[i] = read();
  sort(a + 1, a + n + 1);
  int ans = 0;
  int nxt = 0;
  for (int i = 1; i <= a[1]; i = nxt + 1) {
    nxt = a[1] / (a[1] / i);
    for (int j = 2; j <= n; ++j) nxt = min(nxt, a[j] / (a[j] / i));
    int tmp = 1;
    for (int j = 1; j <= n; ++j)
      tmp = 1ll * tmp * (a[j] / i) % MOD;
    ans = (ans + 1ll * (Sum[nxt] - Sum[i - 1] + MOD) % MOD * tmp) % MOD;
  }
  for (int i = 1; i <= n; ++i) a[i] >>= 1;
  for (int i = 1; i <= a[1]; i = nxt + 1) {
    nxt = a[1] / (a[1] / i);
    for (int j = 2; j <= n; ++j) nxt = min(nxt, a[j] / (a[j] / i));
    int tmp = 1;
    for (int j = 1; j <= n; ++j)
      tmp = 1ll * tmp * (a[j] / i) % MOD;
    ans = (ans + 1ll * (Sum[nxt] - Sum[i - 1] + MOD) % MOD * tmp) % MOD;
  }
  return ans;
}
int main() {
  int T = read();
  Get_mu();
  while (T--) {
    printf ("%d\n", Calc());
  }
}