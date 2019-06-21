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
const int MAXN = 1000000;
int Hash[MAXN + 5];
struct data {
  int l, r;
  bool operator < (const data &a) const {
    return  Hash[r] - Hash[l] + 1 < Hash[a.r] - Hash[a.l] + 1;
  }
}a[MAXN + 5];
int Max[MAXN + 5 << 2], Add[MAXN + 5 << 2];
void Pushup(int rt) {
  Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
}
void Pushdown(int rt) {
  if (Add[rt]) {
    Max[rt << 1] += Add[rt];
    Max[rt << 1 | 1] += Add[rt];
    Add[rt << 1] += Add[rt];
    Add[rt << 1 | 1] += Add[rt];
    Add[rt] = 0;
  }
}
void Update(int L, int R, int c, int l, int r, int rt) {
  if (L <= l && R >= r) {
    Max[rt] += c;
    Add[rt] += c;
    return;
  }
  int mid = l + r >> 1;
  Pushdown(rt);
  if (L <= mid) Update(L, R, c, l, mid, rt << 1);
  if (R > mid) Update(L, R, c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
int main() {
  int n = read(), m = read(), tot = 0;
  for (int i = 1; i <= n; ++i)
    a[i].l = read(), a[i].r = read(), Hash[++tot] = a[i].l, Hash[++tot] = a[i].r;
  sort(Hash + 1, Hash + tot + 1);
  int cnt = unique(Hash + 1, Hash + tot + 1) - Hash - 1;
  for (int i = 1; i <= n; ++i) {
    a[i].l = lower_bound(Hash + 1, Hash + cnt + 1, a[i].l) - Hash;
    a[i].r = lower_bound(Hash + 1, Hash + cnt + 1, a[i].r) - Hash;
  }
  sort(a + 1, a + n + 1);
  int l = 1;
  int Ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i) {
    Update(a[i].l, a[i].r, 1, 0, MAXN, 1);
    bool flag = 0;
    while (Max[1] >= m) {
      Update(a[l].l, a[l].r, -1, 0, MAXN, 1);
      l++;
      flag = 1;
    }
    if (flag) l--, Update(a[l].l, a[l].r, 1, 0, MAXN, 1);
    if (Max[1] == m) Ans = min(Ans, (Hash[a[i].r] - Hash[a[i].l]) - (Hash[a[l].r] - Hash[a[l].l]));
  }
  printf ("%d\n", Ans == 0x3f3f3f3f ? -1 : Ans);
}
