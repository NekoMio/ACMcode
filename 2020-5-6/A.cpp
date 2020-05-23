#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
  int n;
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &a[i]);
  }
  int ans = 0;
  sort(a + 1, a + n + 1);
  if (n & 1) {
    for (int i = n; i >= 1; i--) {
      ans += ((a[i] & 1) ? a[i] : a[i] - 1);
    }
  } else {
    for (int i = n; i >= 2; i--) {
      ans += ((a[i] & 1) ? a[i] : a[i] - 1);
    }
  }
  printf ("%d\n", ans);
}