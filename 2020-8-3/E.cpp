#include <bits/stdc++.h>
using namespace std;
int a[100005], sum[100005];
int main() {
  int n = 10;
  for (int i = 1; i <= n / 3; i++) {
    if (i + i + i + 3 <= n) {
      memset (a, 0, sizeof (a));
      a[i + i + i + 3] = 1;
      for (int j = i + i + i + 3; j + i <= n; j++) {
        a[j + i] += a[j];
        a[j + i + 1] += a[j];
        a[j + i + 2] += a[j];
      }
      for (int j = 1; j <= n; j++) {
        sum[j] += a[j];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    printf ("%d\n", sum[i]);
  }
}