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
const int N = 100000;
int a[MAXN], g[MAXN], f[MAXN], ans[MAXN];
struct data {
  int l, r, d, id;
  bool operator < (const data &c) const {
    return r < c.r;
  }
}v[MAXN];
void Calc(int n) {
  memset (g, 0, sizeof (g));
  memset (f, 0, sizeof (f));
  int cnt = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        g[j] = max(g[j], f[a[i] / j]);
        g[a[i] / j] = max(g[a[i] / j], f[j]);
      }
    }
    f[a[i]] = i;
    while (v[cnt].r == i) {
      if (g[v[cnt].d] >= v[cnt].l) ans[v[cnt].id] = 1;
      cnt++;
    }
  }
}
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  for (int i = 1; i <= m; ++i)
    v[i].l = read(), v[i].r = read(), v[i].d = read(), v[i].id = i;
  sort(v + 1, v + m + 1);
  Calc(n);
  reverse(a + 1, a + n + 1);
  for (int i = 1; i <= m; ++i)
    v[i].l = n - v[i].l + 1, v[i].r = n - v[i].r + 1, swap(v[i].l, v[i].r);
  sort(v + 1, v + m + 1);
  Calc(n);
  for (int i = 1; i <= m; ++i) {
    if (ans[i]) printf ("Yes\n");
    else printf ("No\n");
  }
}
