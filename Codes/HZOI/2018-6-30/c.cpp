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
const int MAXN = 200005;
struct data {
  int l, r;
  bool operator < (const data &c) const {
    return l < c.l;
  }
}d[MAXN];
int Hash[MAXN], tot;
vector<int> vc[MAXN];
int f[MAXN];
int nxt[MAXN][21], n, m;
int Minid[MAXN << 2];
void Pushup(int rt) {
  if (d[Minid[rt << 1]].r < d[Minid[rt << 1 | 1]].r) Minid[rt] = Minid[rt << 1];
  else Minid[rt] = Minid[rt << 1 | 1];
}
void Update(int x, int c, int l = 0, int r = 2 * m, int rt = 1) {
  if (l == r) {
    if (d[Minid[rt]].r > d[c].r) Minid[rt] = c;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) Update(x, c, l, mid, rt << 1);
  else Update(x, c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
int Query(int L, int R = 2 * m, int l = 0, int r = 2 * m, int rt = 1) {
  if (L <= l && R >= r) {
    return Minid[rt];
  }
  int mid = l + r >> 1;
  int ans = 0;
  if (L <= mid) {
    int t = Query(L, R, l, mid, rt << 1);
    if (d[ans].r > d[t].r) ans = t;
  }
  if (R > mid) {
    int t = Query(L, R, mid + 1, r, rt << 1 | 1);
    if (d[ans].r > d[t].r) ans = t;
  }
  return ans;
}
int Calc(int x) {
  int T = d[x].l + m, ans = 0;
  for (int i = 20; i >= 0; --i) {
    if (d[nxt[x][i]].r <= T) {
      ans += (1 << i);
      x = nxt[x][i];
    }
  }
  return ans;
}
int main() {
  // freopen ("c.in", "r", stdin);
  // freopen ("c.out", "w", stdout);
  m = read(), n = read();
  for (int i = 1; i <= n; ++i) {
    d[i].l = read(), d[i].r = read();
    Hash[tot++] = d[i].l, Hash[tot++] = d[i].r;
  }
  Hash[tot++] = m - 1;
  sort(Hash, Hash + tot);
  int cnt = unique(Hash, Hash + tot) - Hash - 1;
  m = lower_bound(Hash, Hash + cnt + 1, m - 1) - Hash;
  m++;
  for (int i = 1; i <= n; ++i) {
    d[i].l = lower_bound(Hash, Hash + cnt + 1, d[i].l) - Hash;
    d[i].r = lower_bound(Hash, Hash + cnt + 1, d[i].r) - Hash;
    if (d[i].l > d[i].r) d[i].r += m;
  }
  sort(d + 1, d + n + 1);
  d[0].r = 0x3f3f3f3f;
  for (int i = n; i >= 1; --i) {
    nxt[i][0] = Query(d[i].r);
    Update(d[i].l, i);
  }
  for (int i = 1; i <= 20; ++i)
    for (int j = 1; j <= n; ++j)
      nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = max(ans, Calc(i) + 1);
  printf ("%d\n", ans);
}
