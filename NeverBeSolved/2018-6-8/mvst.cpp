#pragma GCC optimize("O0")
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
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e5 + 5;
struct data {
  int a, b, v;
  double val;
}v[MAXN << 1];
bool cmp(const data &a, const data &b) {
  return a.v < b.v;
}
int n, m;
int val[MAXN];
int fa[MAXN];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
long long Calc(double x) {
  int Num = 0;
  int h = 0;
  for (int i = 1; i <= m; ++i) v[i].val = (v[i].v - x) * (v[i].v - x);
  sort(v + 1, v + m + 1, [](const data &y, const data &z) {
    return y.val < z.val;
  });
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    if (find(v[i].a) != find(v[i].b)) {
      Num++;
      fa[find(v[i].a)] = find(v[i].b);
      val[++h] = v[i].v;
      if (Num == n - 1) break;
    }
  }
  if (Num != n - 1) return -1;
  long long Sum = 0;
  long long ret = 0;
  for (int i = 1; i < n; ++i) {
    ret = ret + 1ll * val[i] * val[i];
    Sum = Sum + val[i];
  }
  ret = (n - 1) * ret - Sum * Sum;
  return ret;
}
vector<double> vc;
int main() {
  // freopen("mvst1.in", "r", stdin);
  // freopen("mvst.out", "w", stdout);
  n = read(), m = read();
  int T = read();
  for (int i = 1; i <= m; ++i)
    v[i].a = read(), v[i].b = read(), v[i].v = read();
  sort(v + 1, v + m + 1, cmp);
  if (T == 1) {
    long long ans = INF;
    for (int i = 1; i <= m; ++i) {
      for (int j = i + 1; j <= m; ++j) {
        vc.push_back((v[i].v + v[j].v) / 2.0);
      }
    }
    vc.push_back(-INF), vc.push_back(INF);
    sort(vc.begin(), vc.end());
    int cnt = vc.size() - 1;
    for (int i = 1; i < cnt; ++i) {
      double mid = (vc[i - 1] + vc[i]) / 2;
      // printf ("%.3f\n", mid);
      long long tp = Calc(mid);
      if (tp != -1) ans = min(ans, tp);
    }
    if (ans == INF) ans = -1;
    printf ("%lld\n", ans);
  }
}