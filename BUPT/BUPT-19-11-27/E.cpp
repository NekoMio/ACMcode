#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN], n, k;
int Calc(int x) {
  int ans = 1, Sum = 0;
  for (int i = 2; i <= n; i++) {
    Sum += a[i] - a[i - 1];
    if (Sum >= x) {
      Sum = 0;
      ans++;
    }
  }
  return ans;
}
int main() {
  while (scanf ("%d%d", &n, &k)) {
    if (n == 0 && k == 0) break;
    for (int i = 1; i <= n; i++)
      scanf ("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int l = 0, r = 1e6 + 1;
    int ans = 0;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Calc(mid) >= k) l = mid + 1, ans = mid;
      else r = mid - 1;
    }
    printf ("%d\n", ans);
  }
}