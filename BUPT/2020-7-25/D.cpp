#include <bits/stdc++.h>
using namespace std;
int a[605], b[605], f[605];
int main() {
  int n;
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &a[i]);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1, k = i; j <= n; j++, k++) {
      b[j] = a[k];
      if (k == n) k = 0;
    }
    for (int j = 1; j <= n; j++) {
      f[j] = 1;
      for (int k = 1; k < j; k++) {
        if (b[k] < b[j]) f[j] = max(f[j], f[k] + 1);
      }
      ans = max(ans, f[j]);
    }
  }
  printf ("%d\n", n - ans);
}