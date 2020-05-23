#include <bits/stdc++.h>
using namespace std;
int a[104];
int main() {
  int n;
  scanf ("%d", &n);
  unsigned long long ans = 0;
  int t = 0;
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &a[++t]);
    if (a[t] < 128) {
      ans = a[t];
      for (int i = t - 1; i >= 1; i--) {
        ans = ans * 128 + a[i] - 128;
      }
      if (ans & 1) {
        printf ("-%llu\n", ans / 2 + 1);
      } else {
        printf ("%llu\n", ans / 2);
      }
      t = 0;
    }
  }
}