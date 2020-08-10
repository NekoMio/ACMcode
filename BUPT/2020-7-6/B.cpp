#include <bits/stdc++.h>
using namespace std;
int main() {
  double p = 52 * 3.0 / 365;
  int n;
  scanf ("%d", &n);
  n = n * (n - 1) / 2;
  printf ("%.12f\n", n * ((3. / 365) * p + (1. / 365) * (1 - p)));
}