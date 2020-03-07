#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN];
int main() {
  int n, k;
  scanf ("%d%d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf ("%d", a + i);
  int Max = 0, Sum = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] != a[i - 1]) Sum++;
    else {
      Max = max(Sum, Max);
      Sum = 1;
    }
  }
  Max = max(Sum, Max);
  printf ("%d\n", Max);
}