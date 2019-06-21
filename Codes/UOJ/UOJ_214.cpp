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
char s[50];
const int MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int Num(unsigned int x) {
  unsigned int tmp = x
                   - ((x >> 1) & 033333333333)
                   - ((x >> 2) & 011111111111);
  tmp = (tmp + (tmp >> 3)) & 030707070707;
  return tmp % 63;
}
char sh[35][50];
int vis[65][65];
bool t[65][65];
int len[65], tmp[65], cnt, n, m;
bool Judge(int x) {
  for (int i = 1; i <= m; ++i) {
    if (!vis[x + i - 1][s[i] - 'a'])
      return 0;
  }
  return 1;
}
int K(int S) {
  memset (t, 0, sizeof (t));
  int k = 0;
  for (int i = 1; i <= cnt; ++i) {
    int z = tmp[i];
    if (S & (1 << (i - 1))) {
      for (int j = 1; j <= m; ++j) {
        k += t[z + j - 1][s[j] - 'a'] == 0;
        t[z + j - 1][s[j] - 'a'] = 1;
      }
    }
  }
  assert(k <= 35 * 35);
  return k;
}
int tt;
int ff[35 * 35];
int F(int x) {
  int ans = 0;
  if (ff[x] != -1) return ff[x];
  for (int i = 0; i < x; ++i) {
    ans = (ans + 1ll * tt * pow_mod(x - i, MOD - 2) % MOD) % MOD;
  }
  return ff[x] = ans;
}
int f[2][1030][1005], h[2058];
bool OK[35];
int Calc() {
  int N = (1 << m) - 1;
  memset (h, 0, sizeof (h));
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (i & (1 << (j - 1))) {
        h[i] |= (1 << (s[j] - 'a'));
      }
    }
  }
  N = (1 << (m - 1)) - 1;
  memset (f, 0, sizeof (f));
  int now = 0;
  f[now][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int j = 0; j <= N; ++j) {
      for (int k = 0; k <= i * m; ++k) {
        if (f[now ^ 1][j][k]) {
          (f[now][(j << 1) & N][k + Num(h[j << 1])] += f[now ^ 1][j][k]) %= MOD;
          if (i <= n - m && OK[i + 1]) {
            f[now][(j << 1 | 1) & N][k + Num(h[j << 1 | 1])] = (f[now][(j << 1 | 1) & N][k + Num(h[j << 1 | 1])] - f[now ^ 1][j][k] + MOD) % MOD;
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= tt; ++i) ans = (ans + 1ll * f[now][0][i] * (MOD - F(i)) % MOD) % MOD;
  return ans;
}
int main() {
  int T = read();
  while (T--) {
    n = read(), m = read();
    memset (vis, 0, sizeof (vis));
    tt = 0;
    memset (ff, -1, sizeof (ff));
    for (int i = 1; i <= n; ++i) {
      scanf ("%s", sh[i] + 1);
      tt += (len[i] = strlen(sh[i] + 1));
      for (int j = 1; j <= len[i]; ++j)
        vis[i][sh[i][j] - 'a'] = 1;
    }
    scanf ("%s", s + 1);
    cnt = 0;
    for (int i = 1; i <= n; ++i)
      if (Judge(i)) {
        tmp[++cnt] = i;
        OK[i] = 1;
      } else OK[i] = 0;
    if (cnt == 0) {
      printf ("-1\n");
      continue;
    }
    if (m >= 12) {
      int N = (1 << cnt) - 1;
      int ans = 0;
      for (int i = 0; i <= N; ++i) {
        if (Num(i) & 1) ans = (ans + F(K(i))) % MOD;
        else ans = (ans - F(K(i)) + MOD) % MOD;
      }
      printf ("%d\n", ans);
    } else {
      // printf ("0\n");
      printf ("%d\n", Calc());
    }
  }
}
