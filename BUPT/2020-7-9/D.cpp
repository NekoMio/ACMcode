#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int pos[60005], pre[60005];
#define lch l, mid, rt << 1
#define rch mid + 1, r, rt << 1 | 1
double Min[60005 << 2];
int Add[60005 << 2];
void PushUp(int rt) {
  Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
void rebuild(double Mid, int l, int r, int rt) {
  Add[rt] = 0;
  if (l == r) {
    Min[rt] = Mid * l;
    return;
  }
  int mid = l + r >> 1;
  rebuild(Mid, lch);
  rebuild(Mid, rch);
  PushUp(rt);
}
void PushDown(int rt) {
  if (Add[rt]) {
    Add[rt << 1] += Add[rt];
    Min[rt << 1] += Add[rt];
    Add[rt << 1 | 1] += Add[rt];
    Min[rt << 1 | 1] += Add[rt];
    Add[rt] = 0;
  }
}
void Update(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    Add[rt] += 1;
    Min[rt] += 1;
    return;
  }
  int mid = l + r >> 1;
  PushDown(rt);
  if (L <= mid) Update(L, R, lch);
  if (R > mid) Update(L, R, rch);
  PushUp(rt);
}
double Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) {
    return Min[rt];
  }
  int mid = l + r >> 1;
  double ans = 0x3f3f3f3f;
  if (L <= mid) ans = min(ans, Query(L, R, lch));
  if (R > mid) ans = min(ans, Query(L, R, rch));
  return ans;
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, a;
    memset(pre, 0, sizeof(pre));
    memset(pos, 0, sizeof(pos));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a);
      pre[i] = pos[a];
      pos[a] = i;
    }
    double L = 0, R = 1;
    while (R - L >= 1e-4) {
      double mid = (L + R) / 2, tmp = 0;
      rebuild(mid, 1, n, 1);
      bool flag = 0;
      for (int i = 1; i <= n; i++) {
        Update(pre[i] + 1, i, 1, n, 1);
        tmp = Query(1, i, 1, n, 1);
        if (tmp <= (i + 1) * mid) {
          flag = 1;
          break;
        }
      }
      if (flag)
        R = mid;
      else
        L = mid;
    }
    printf ("%.4f\n", (L + R) / 2);
  }
}