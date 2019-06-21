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
const int MAXN = 60005;
char s[MAXN];
int f[MAXN], g[MAXN];
int MOD = 998244353;
long long Hash[MAXN], bin[MAXN], base = 31;
int n;
unsigned int Get_Hash(int l, int r) {
  return (Hash[r] - Hash[l - 1] * bin[r - l + 1] % MOD + MOD) % MOD;
}
int Get_LCS(int x, int y, int L) {
  int l = 1, r = L, ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Get_Hash(x - mid + 1, x) == Get_Hash(y - mid + 1, y)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}
int Get_LCP(int x, int y, int L) {
  int l = 1, r = L, ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Get_Hash(x, x + mid - 1) == Get_Hash(y, y + mid - 1)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}
long long Calc(int n) {
  memset (f, 0, sizeof (f));
  memset (g, 0, sizeof (g));
  memset (Hash, 0, sizeof (Hash));
  for (int i = 1; i <= n; ++i) Hash[i] = (Hash[i - 1] * base + s[i]) % MOD;
  for (int l = 1; l * 2 <= n; ++l) {
    for (int i = l + l; i <= n; i += l) {
      if (s[i] != s[i - l]) continue;
      int h = i - Get_LCS(i, i - l, l) + 1;
      int t = i + Get_LCP(i, i - l, l) - 1;
      h = max(h + l - 1, i);
      t = min(t, i + l - 1);
      if (h <= t) {
        g[h - 2 * l + 1]++, g[t + 2 - 2 * l]--;
        f[h]++, f[t + 1]--;
      }
    }
  }
  for (int i = 1; i <= n; ++i) f[i] += f[i - 1], g[i] += g[i - 1];
  long long ans = 0;
  for(int i = 1; i < n; ++i) {
    ans = ans + 1ll * f[i] * g[i + 1];
  }
  return ans;
}
int main() {
  int T = read();
  bin[0] = 1;
  for (int i = 1; i <= 30000; ++i) bin[i] = bin[i - 1] * base % MOD;
  while (T--) {
    scanf ("%s", s + 1);
    n = strlen(s + 1);
    printf ("%lld\n", Calc(n));
  }
}
