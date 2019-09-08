#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

inline void read(int &x) {
  x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}

inline int max(const int &a, const int &b) { return a > b ? a : b; }
inline void gmax(int &a, int b) {
  if (a < b) a = b;
}
void shuchu(int j) {
  if (j >= 10) shuchu(j / 10);
  putchar(j % 10 + '0');
}

const int MAXN = 5e5 + 5;
int a[MAXN], ans[MAXN], Hash[MAXN], Q[MAXN];
int Max[MAXN << 2];
void Update(int x, int val, int l, int r, int rt) {
  gmax(Max[rt], val);
  if (l == r) return;
  int mid = l + r >> 1;
  if (x <= mid) Update(x, val, l, mid, rt << 1);
  else Update(x, val, mid + 1, r, rt << 1 | 1);
}
int Query(int L, int R, int l, int r, int rt) {
  if (L > R) return -1;
  if (L <= l && R >= r) return Max[rt];
  int ans = -1, mid = l + r >> 1;
  if (L <= mid) ans = max(ans, Query(L, R, l, mid, rt << 1));
  if (R > mid) ans = max(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
  return ans;
}

int main() {
  // freopen("tmp/test.in", "r", stdin);
  int n, m;
  read(n), read(m);
  memset(Max, -1, sizeof(Max));
  for (int i = 1; i <= n; i++) read(a[i]), Hash[i] = a[i];
  sort(Hash + 1, Hash + n + 1);
  int cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
  for (int i = 1; i <= n; i++) {
    Q[i] = lower_bound(Hash + 1, Hash + cnt + 1, a[i] + m) - Hash;
    a[i] = lower_bound(Hash + 1, Hash + cnt + 1, a[i]) - Hash;
    // fprintf (stderr, "%d\n", Q[i]);
  }
  // fprintf (stderr, "%d\n", cnt);
  for (int i = n; i >= 1; i--) {
    ans[i] = Query(Q[i], cnt, 1, cnt, 1);
    if (ans[i] != -1) 
      ans[i] -= (i + 1);
    Update(a[i], i, 1, cnt, 1);
  }
  for (int i = 1; i < n; i++) {
    if (ans[i] < 0)
      putchar('-'), putchar('1');
    else
      shuchu(ans[i]);
    putchar(' ');
  }
  if (ans[n] < 0)
    putchar('-'), putchar('1');
  else
    shuchu(ans[n]);
  // while(1);
}