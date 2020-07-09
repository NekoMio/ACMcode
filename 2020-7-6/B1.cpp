#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf ("%d", &n);
  double p1 = 1, p2 = 1;
  for (int i = 1; i < n; i++) {
    p1 = p1 * 362.0 / 365;
  }
  p1 *= (362 + 3.0 * n) / 365;
  p1 = 1 - p1;
  for (int i = 1; i < n; i++) {
    p2 *= 364.0 / 365;
  }
  p2 *= (364 + 1.0 * n) / 365;
  p2 = 1 - p2;
  printf ("%.12f\n", p1 * 52 + p2 * 209);
}