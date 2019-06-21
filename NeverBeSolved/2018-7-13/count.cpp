#include <algorithm>
#include <cstring>
#include <cstdio>
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
const int MAXN = 2e5 + 5;
const int MOD = 998244353;
int a[MAXN];
int f[2][4005];
int vc[MAXN], cnt;
int fc[10000005];
int main() {
  // freopen ("count.in", "r", stdin);
  // freopen ("count.out", "w", stdout);
  int n = read(), k = read();
  for (int i = 1; i <= n; ++i)
    a[i] = read();
  for (int i = 1, nxt = 0; i <= k; i = nxt + 1) {
    nxt = k / (k / i);
    vc[++cnt] = (k / i);
    fc[k / i] = cnt;
  }
  int now = 0;
  f[now][1] = 1;
  for (int i = 1; i <= n; ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int j = 1; j <= cnt; ++j) {
      if (vc[j] >= a[i]) (f[now][fc[vc[j] / a[i]]] += f[now ^ 1][j]) %= MOD;
      (f[now][j] += f[now ^ 1][j]) %= MOD;
    }
  }
  int ans = 0;
  for (int i = 1; i <= cnt; ++i)
    ans = (ans + f[now][i]) % MOD;
  printf ("%d\n", ans);
}
