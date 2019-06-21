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
const int MOD = 1e9 + 7;
int c[10][10];
int C(int n, int m) {
  if (n < m) return 0;
  return c[n][m];
}
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
int ans = 0;
int mp[5][5], id[5][5];
int n, m, h, w;
unordered_map<int, int> calc[5];
int Calc(int g, int b) {
  if (calc[g].count(b)) return calc[g][b];
  int ans = 0;
  for (int j = 0; j <= g; ++j)
    ans = (ans + pow_mod(C(g, j), b)) % MOD;
  calc[g][b] = ans;
  return ans;
}
void Calc(int S) {
  memset (mp, 0, sizeof (mp));
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      if (S & (1 << (id[i][j] - 1)))
        mp[i][j] = 1;
  int Sum1 = 1;
  for (int i = 1; i <= w; ++i) {
    int g = 0, tmp = 0;
    for (int j = 1; j <= h; ++j) if (mp[j][i]) g++;
    for (int j = 0; j <= g; ++j) {
      if (j & 1) tmp = (tmp - 1ll * C(g, j) * (1 << j) % MOD * Calc(g - j, (m - i + 1) / w + (((m - i + 1) % w) != 0)) % MOD + MOD) % MOD;
      else tmp = (tmp + 1ll * C(g, j) * (1 << j) % MOD * Calc(g - j, (m - i + 1) / w + (((m - i + 1) % w) != 0)) % MOD) % MOD;
    }
    Sum1 = 1ll * Sum1 * tmp % MOD;
  }
  int Sum2 = 1;
  for (int i = 1; i <= h; ++i) {
    int g = 0;
    for (int j = 1; j <= w; ++j) if (!mp[i][j]) g++;
    Sum2 = 1ll * Sum2 * Calc(g, (n - i + 1) / h + (((n - i + 1) % h) != 0)) % MOD;
  }
  ans = (ans + 1ll * Sum1 * Sum2 % MOD) % MOD;
}
int main() {
  n = read(), m = read(), h = read(), w = read();
  int T = (1 << (h * w)) - 1, Id = 0;
  for (int i = 0; i <= 5; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      id[i][j] = ++Id;
  for (int i = 0; i <= T; ++i) {
    Calc(i);
  }
  printf ("%d\n", ans);
}