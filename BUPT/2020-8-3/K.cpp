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
const int MAXN = 1e5 + 5;
long long a[MAXN];
int b[MAXN], Min[MAXN << 2], lazy[MAXN << 2], Pos[MAXN << 2];
int Max[MAXN << 2];
void PushUp(int rt) {
  Max[rt] =
      a[Max[rt << 1]] >= a[Max[rt << 1 | 1]] ? Max[rt << 1] : Max[rt << 1 | 1];
  Pos[rt] =
      b[Pos[rt << 1]] <= b[Pos[rt << 1 | 1]] ? Pos[rt << 1] : Pos[rt << 1 | 1];
  Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void PushDown(int rt) {
  if (lazy[rt]) {
    lazy[rt << 1] += lazy[rt];
    lazy[rt << 1 | 1] += lazy[rt];
    Min[rt << 1] -= lazy[rt];
    Min[rt << 1 | 1] -= lazy[rt];
    lazy[rt] = 0;
  }
}
void buildtree(int l, int r, int rt) {
  lazy[rt] = 0;
  if (l == r) {
    Max[rt] = l;
    Min[rt] = b[l];
    Pos[rt] = l;
    return;
  }
  int mid = l + r >> 1;
  buildtree(l, mid, rt << 1);
  buildtree(mid + 1, r, rt << 1 | 1);
  PushUp(rt);
}
void Update(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    Min[rt]--;
    lazy[rt]++;
    return;
  }
  PushDown(rt);
  int mid = l + r >> 1;
  if (L <= mid) Update(L, R, l, mid, rt << 1);
  if (R > mid) Update(L, R, mid + 1, r, rt << 1 | 1);
  PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    return Max[rt];
  }
  PushDown(rt);
  int mid = l + r >> 1;
  int pos = 0, tp;
  if (L <= mid) {
    pos = Query(L, R, l, mid, rt << 1);
  }
  if (R > mid) {
    tp = Query(L, R, mid + 1, r, rt << 1 | 1);
    if (pos == 0 || a[pos] < a[tp]) pos = tp;
  }
  PushUp(rt);
  return pos;
}
int QMin(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    return Min[rt];
  }
  PushDown(rt);
  int mid = l + r >> 1;
  int ans = 0x3f3f3f3f;
  if (L <= mid) {
    ans = QMin(L, R, l, mid, rt << 1);
  }
  if (R > mid) {
    ans = min(ans, QMin(L, R, mid + 1, r, rt << 1 | 1));
  }
  PushUp(rt);
  return ans;
}
int QPos(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    return Pos[rt];
  }
  PushDown(rt);
  int mid = l + r >> 1;
  int pos = 0, tp;
  if (L <= mid) {
    pos = QPos(L, R, l, mid, rt << 1);
  }
  if (R > mid) {
    tp = QPos(L, R, mid + 1, r, rt << 1 | 1);
    if (pos == 0 || b[pos] > b[tp]) pos = tp;
  }
  PushUp(rt);
  return pos;
}
void print(__int128 x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) print(x / 10);
  putchar(x % 10 + '0');
}
int main() {
  int T = read(), t = 0;
  int pos1, pos2, tm;
  while (T--) {
    t++;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    printf("Case #%d: %d ", t, b[1]);
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    buildtree(1, n, 1);
    __int128 ans = 0;
    pos2 = n;
    while (1) {
      pos1 = Query(1, pos2, 1, n, 1);
      ans = ans + a[pos1];
      Update(1, pos1, 1, n, 1);
      tm = QMin(1, pos1, 1, n, 1);
      if (tm == 0) {
        pos2 = QPos(1, pos1, 1, n, 1) - 1;
      }
      if (pos2 == 0) break;
    }
    print(ans);
    printf ("\n");
    // printf ("%lld\n", ans);
  }
}