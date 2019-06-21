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
const int MAXN = 2e5 + 5;
struct data {
  int s, v;
  bool operator<(const data &a) const { return s < a.s; }
} a[MAXN];
long long Get_Ans(long long Sum, long long len, int ds, int dv) {
  if (dv == 2) Sum = Sum * Sum;
  if (ds == 2) len = len * len;
  return Sum - len;
}
int Max[MAXN][21], Log[MAXN];
int Query_Max(int l, int r) {
  if (l == r) return Max[l][0];
  int k = Log[r - l + 1];
  return max(Max[l][k], Max[r - (1 << k) + 1][k]);
}
int Query(int x, int val) {
  if (Query_Max(1, x) <= val) return 0;
  int l = 1, r = x, ans = 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Query_Max(mid, x) <= val)
      r = mid - 1;
    else
      ans = mid, l = mid + 1;
  }
  return ans;
}
long long Calc(int x, int m, int ds, int dv) {
  priority_queue<long long, vector<long long>, greater<long long> > Q;
  long long Ans = 0, Sum = 0;
  for (int i = x; i >= 1; --i) {
    if (Q.size() < m) {
      Sum += a[i].v;
      Q.push(a[i].v);
    } else {
      i = Query(i, Q.top());
      // cerr << i << endl;
      Sum -= Q.top();
      Q.pop();
      Sum += a[i].v;
      Q.push(a[i].v);
      if (!i) break;
    }
    Ans = max(Ans, Get_Ans(Sum, a[x].s - a[i].s, ds, dv));
    if (Q.top() > a[x].v) break;
  }
  return Ans;
}
int main() {
  int n = read(), m = read(), ds = read(), dv = read();
  for (int i = 1; i <= n; ++i) a[i].s = read(), a[i].v = read();
  long long ans = 0;
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) Max[i][0] = a[i].v;
  for (int i = 1; i <= 20; ++i)
    for (int j = 1; j + (1 << i) - 1 <= n; ++j)
      Max[j][i] = max(Max[j][i - 1], Max[j + (1 << (i - 1))][i - 1]);
  Log[0] = -1;
  for (int i = 1; i <= n; ++i) Log[i] = Log[i >> 1] + 1;
  for (int i = 1; i <= n; ++i) ans = max(ans, Calc(i, m, ds, dv));
  printf("%lld\n", ans);
}
