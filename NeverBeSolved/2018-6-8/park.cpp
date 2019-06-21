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
const int MAXN = 100005;
struct edge {
  int END, next, c;
}v[MAXN << 1];
int first[MAXN], p;
long long d[MAXN], w[MAXN], Hash[MAXN];
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].c = c;
  v[p].next = first[a];
  first[a] = p++;
}
int cnt;
long long tmp[MAXN];
const long long INF = 0x3f3f3f3f3f3f3f3f;
long long f[5005][5005];
void DP(int rt, int fa) {
  for (int i = 1; i <= cnt; ++i)
    f[rt][i] = w[rt] * abs(Hash[i] - Hash[d[rt]]);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DP(v[i].END, rt);
    if (v[i].c == 0) {
      tmp[0] = INF;
      for (int j = 1; j <= cnt; ++j) {
        tmp[j] = min(tmp[j - 1], f[v[i].END][j]);
      }
      for (int j = 1; j <= cnt; ++j) {
        f[rt][j] += tmp[j];
      }
    } else {
      tmp[cnt + 1] = INF;
      for (int j = cnt; j >= 1; --j) {
        tmp[j] = min(tmp[j + 1], f[v[i].END][j]);
      }
      for (int j = 1; j <= cnt; ++j) {
        f[rt][j] += tmp[j];
      }
    }
  }
}
int main() {
  // freopen("park.in", "r", stdin);
  // freopen("park.out", "w", stdout);
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) d[i] = read(), Hash[i] = d[i];
  for (int i = 1; i <= n; ++i) w[i] = read();
  sort(Hash + 1, Hash + n + 1);
  cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
  for (int i = 1; i <= n; ++i)
    d[i] = lower_bound(Hash + 1, Hash + cnt + 1, d[i]) - Hash;
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read();
    add(a, b, 1);
    add(b, a, 0);
  }
  DP(1, 0);
  long long ans = INF;
  for (int i = 1; i <= cnt; ++i) ans = min(ans, f[1][i]);
  printf ("%lld\n", ans);
}