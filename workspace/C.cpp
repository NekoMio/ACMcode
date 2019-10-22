#include <bits/stdc++.h>
using namespace std;
int a[305][305];
int main() {
  int n;
  scanf ("%d", &n);
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) {
      for (int j = 1; j <= n; j++) {
        a[j][i] = ++cnt;
      }
    } else {
      for (int j = n; j >= 1; j--) {
        a[j][i] = ++cnt;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      printf ("%d ", a[i][j]);
    }
    printf ("\n");
  }
  // while (1);
}