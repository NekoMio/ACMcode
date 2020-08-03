#include <bits/stdc++.h>
using namespace std;
int a[104][105];
int main() {
  int n, k;
  scanf ("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      if (i == 1) printf ("1 ");
      else if (i < j) printf ("0 ");
      else printf ("1 ");
    }
    printf ("\n");
  }
}