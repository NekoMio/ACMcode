#pragma GCC optimize("O2")
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
int n, m, k;
const int MAXN = 2e5 + 5;
int mp[1005][1005];
vector<int> X[MAXN], Y[MAXN];
int vis[MAXN], h[MAXN], b[MAXN], d[MAXN], c[MAXN], e[MAXN], use[MAXN];
int f[2][2][1025];
int main() {
  n = read(), m = read(), k = read();
  if ((n + m) & 1) return printf ("0\n"), 0;
  for (int i = 1; i <= k; ++i) {
    int z = read(), y = read(), oo = read();
    X[y].push_back(z);
    Y[y].push_back(oo);
  }
  int S = 0x3f3f3f3f, id = 0;
  for (int i = 1; i <= m; ++i) {
    if (X[i].size() < S) {
      id = i;
      S = X[i].size();
    }
  }
  // fprintf (stderr, "%d\n", S);
  int N = (1 << S) - 1, t = -1, tmp = 0;
  memset(vis, -1, sizeof(vis));
  memset(mp, -1, sizeof(mp));
  for (int j = 0; j < S; ++j) vis[X[id][j]] = ++t;
  int ans1 = 1, M = 0;
  for (int i = 1; i <= m; ++i) {
    if (i != id) {
      int l = 0, u = 0;
      for (int j = 0; j < X[i].size(); ++j) {
        if (vis[X[i][j]] == -1) {
          l++;
          u ^= Y[i][j];
        }
      }
      if (l == n - S) {
        b[++M] = u;
        for (int j = 0; j < X[i].size(); ++j) {
          if (vis[X[i][j]] != -1)
            mp[vis[X[i][j]]][M] = Y[i][j];
        }
      } else {
        // printf ("%d %d\n", ans1, l);
        ans1 = 1ll * ans1 * pow_mod(2, n - S - l - 1) % MOD;
        for (int j = 0; j < S; ++j) d[j]++;
        for (int j = 0; j < X[i].size(); ++j) {
          if (vis[X[i][j]] != -1) {
            d[vis[X[i][j]]]--;
            e[vis[X[i][j]]] ^= Y[i][j];
          }
        }
      }
    }
  }
  // printf ("%d\n", ans1);
  for (int i = 0; i < S; ++i) {
    tmp ^= (Y[id][i] ^ e[i]) << i;
  }
  use[1] = tmp;
  int cnt = 1, Start = 1;
  for (int i = 0; i < S; ++i) {
    if (d[i]) {
      for (int j = 1; j <= cnt; ++j) use[j + cnt] = use[j] ^ (1 << i);
      cnt <<= 1;
      Start = 1ll * Start * pow_mod(2, d[i] - 1) % MOD;
    }
  }
  // printf ("%d\n", Start);
  for (int i = 1; i <= cnt; ++i) {
    f[0][1][use[i]] = Start;
  }
  int now = 0;
  for (int j = 1; j <= M; ++j) {
    // if (j == id) continue;
    now ^= 1;
    memset(f[now], 0, sizeof(f[now]));
    for (int i = 0; i <= N; ++i) {
      f[now][b[j]][i] = f[now ^ 1][1][i];
    }
    for (int i = 0; i < S; ++i) {
      now ^= 1;
      memset(f[now], 0, sizeof(f[now]));
      for (int k = 0; k <= 1; ++k) {
        for (int l = 0; l <= N; ++l) {
          if (mp[i][j] != -1) {
            if (mp[i][j] == 1)
              (f[now][k ^ 1][l ^ (1 << i)] +=
               f[now ^ 1][k][l]) %= MOD;
            else
              (f[now][k][l] += f[now ^ 1][k][l]) %= MOD;
          } else {
            (f[now][k][l] += f[now ^ 1][k][l]) %= MOD;
            (f[now][k ^ 1][l ^ (1 << i)] +=
             f[now ^ 1][k][l]) %= MOD;
          }
        }
      }
    }
  }
  printf("%lld\n", 1ll * f[now][1][N] * ans1 % MOD);
}
