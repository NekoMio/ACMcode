#pragma GCC optimize("O3")
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
char s[200005];
const int MAXN = 205005;
int pos[MAXN], sa[MAXN], rk[MAXN], height[MAXN], Sum[MAXN];
int buc[MAXN], wa[MAXN], wb[MAXN], n;
int r[MAXN];
void getheight(int n) {
  int i, j, k = 0;
  for (i = 0; i < n; i++) rk[sa[i]] = i;
  for (i = 0; i < n; height[rk[i++]] = k)
    for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; k++)
      ;
  return;
}
bool cmp(int *c, int a, int b, int d) {
  return c[a] == c[b] && c[a + d] == c[b + d];
}
void da(int n, int m = 320) {
  int i, j, p, *x = wa, *y = wb, *t;
  for (i = 0; i < m; i++) buc[i] = 0;
  for (i = 0; i < n; i++) buc[x[i] = r[i]]++;
  for (i = 1; i < m; i++) buc[i] += buc[i - 1];
  for (i = n - 1; ~i; i--) sa[--buc[x[i]]] = i;
  for (j = 1, p = 1; p < n; j *= 2, m = p) {
    for (i = n - j, p = 0; i < n; i++) y[p++] = i;
    for (i = 0; i < n; i++)
      if (sa[i] >= j) y[p++] = sa[i] - j;
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[x[y[i]]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (i = n - 1; ~i; i--) sa[--buc[x[y[i]]]] = y[i];
    for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
      x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
  }
  getheight(n);
  return;
}
long long tot;
vector<pair<int, int> > ans;
long long S[MAXN << 2], tag[MAXN << 2];
void Pushdown(int rt, int l, int mid, int r) {
  if (tag[rt] != -1) {
    tag[rt << 1] = tag[rt];
    S[rt << 1] = tag[rt];
    tag[rt << 1 | 1] = tag[rt] + mid - l + 1;
    S[rt << 1 | 1] = tag[rt << 1 | 1];
    tag[rt] = -1;
  }
}
void Update(int L, int R, long long x, int l, int r, int rt) {
  if (L == l && R == r) {
    tag[rt] = x;
    S[rt] = x;
    return;
  }
  int mid = l + r >> 1;
  Pushdown(rt, l, mid, r);
  if (R <= mid)
    Update(L, R, x, l, mid, rt << 1);
  else if (L > mid)
    Update(L, R, x, mid + 1, r, rt << 1 | 1);
  else
    Update(L, mid, x, l, mid, rt << 1),
        Update(mid + 1, R, x + mid - L + 1, mid + 1, r, rt << 1 | 1);
}
long long Query(int x, int l, int r, int rt) {
  if (l == r) return S[rt];
  int mid = l + r >> 1;
  Pushdown(rt, l, mid, r);
  if (x <= mid)
    return Query(x, l, mid, rt << 1);
  else
    return Query(x, mid + 1, r, rt << 1 | 1);
}
int Calc(int i, int n) {
  int l = 1, r = n - i + 1;
  while (l <= r) {
    int mid = l + r >> 1;
    long long tp =
        (tot - Query(mid, 1, n, 1) + 1) - (Sum[i + mid - 1] - Sum[i - 1]);
    if (tp == 0) return i + mid - 1;
    if (tp > 0)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return n + 1;
}
int a[MAXN];
int main() {
  // freopen ("tes.in", "r", stdin);
  freopen ("platform.in", "r", stdin);
  freopen ("platform.out", "w", stderr);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  // reverse(s + 1, s + n + 1);
  for (int i = 1; i <= n; ++i) a[i] = read();
  for (int i = 1; i <= n; ++i)
    r[i - 1] = s[i];
  da(n + 1);
  for (int i = n; i >= 1; --i) sa[i]++;
  // for (int i = 1; i <= n; ++i) cerr << sa[i] << endl;
  long long tp = 0;
  memset(tag, -1, sizeof(tag));
  for (int i = 1; i <= n; ++i)
    Sum[i] = Sum[i - 1] + a[i], tot += n - sa[i] - height[i] + 1;
  for (int i = 1; i <= n; ++i) {
    // cerr << height[i] + 1 << " " << n - sa[i] + 1 << " " << tp + 1 << endl;
    Update(height[i] + 1, n - sa[i] + 1, tp + 1, 1, n, 1);
    int t = Calc(sa[i], n);
    if (t != n + 1) ans.push_back(pair<int, int>(sa[i], t));
    tp = tp + n - sa[i] - height[i] + 1;
  }
  printf("%d\n", (int)ans.size());
  sort(ans.begin(), ans.end());
  for (auto x : ans) printf("%d %d\n", x.first, x.second);
}
