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
const int MAXN = 5e5 + 5;
int Max[MAXN << 2];
void PushUp(int rt) {
  Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
}
void add(int x, int c, int l, int r, int rt) {
  if (l == r) {
    Max[rt] = c;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) add(x, c, l, mid, rt << 1);
  else add(x, c, mid + 1, r, rt << 1 | 1);
  PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    return Max[rt];
  }
  int mid = l + r >> 1, ans = 0;
  if (L <= mid) ans = max(ans, Query(L, R, l, mid, rt << 1));
  if (R > mid) ans = max(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
  return ans;
}
unordered_map<int, int> id;
int a[MAXN], pre[MAXN];
bool Judge(int x, int n, int k) {
  if (Query(1, x, 1, n, 1) > 0) return 0; 
  for (int i = x + 1; i <= n; i += k) {
    if (Query(i, min(n, i + k - 1), 1, n, 1) >= i) return 0;
  }
  return 1;
}
int main() {
  int T = read();
  while (T--) {
    id.clear();
    int n = read(), k = read();
    for (int i = 1; i <= n; i++) {
      a[i] = read();
      pre[i] = id[a[i]];
      id[a[i]] = i;
      add(i, pre[i], 1, n, 1);
    }
    bool flag = 0;
    for (int i = 1; i <= k && i <= n; i++) {
      if (Judge(i, n, k)) {
        flag = 1;
        break;
      }
    }
    if (flag) printf ("YES\n");
    else printf ("NO\n");
  }
}