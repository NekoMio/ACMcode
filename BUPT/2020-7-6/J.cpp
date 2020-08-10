#include <bits/stdc++.h>
using namespace std;
int a[10];
int main() {
  int n;
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &a[i]);
  }
  int N = (1 << n) - 1;
  int ans = 0, tmp;
  for (int i = 1; i <= N; i++) {
    tmp = 0;
    for (int j = 1; j <= n; j++) {
      if (i & (1 << (j - 1))) {
        tmp ^= a[j];
      }
    }
    ans = max(ans, tmp);
  }
  printf ("%d\n", ans);
}