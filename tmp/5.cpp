#include <bits/stdc++.h>
using namespace std;
int n;
inline int Query(int x) {
  if (x > n) return 0;
  printf ("1 %d\n", x);
  fflush(stdout);
  static int ans;
  scanf ("%d", &ans);
  return ans;
}
inline void Ans(int x) {
  printf ("2 %d\n", x);
  fflush(stdout);
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    scanf ("%d", &n);
    int fi = Query(1);
    int l = 1, r = n + 1, len = 0;
    while (l < r) {
      int mid = l + r >> 1;
      int t = Query(mid);
      if (t == fi) len = mid, l = mid + 1;
      else r = mid;
    }
    if (Query(len + 1) == Query(2 * len + 1)) {
      Ans(fi);
      continue;
    } else {
      int Num = n / len + 1;
      int l = 1, r = Num + 1, ans = 0;
      while (l < r) {
        int mid = l + r >> 1;
        int t1 = Query(mid * len), t2 = Query(mid * len + 1);
        if (t1 != t2)
          ans = t2, l = mid + 1;
        else r = mid;
      }
      Ans(ans);
    }
  }
}