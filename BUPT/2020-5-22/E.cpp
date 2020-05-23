#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, X;
  double v;
  scanf ("%d%d%lf", &n, &X, &v);
  double A, B;
  int l, r;
  double tv;
  for (int i = 1; i <= n; i++) {
    scanf ("%d%d%lf", &l, &r, &tv);
    B += (r - l) * tv / v;
  }
  double T = B / X;
  if (T > 1 || T < -1) {
    printf ("Too hard\n");
  } else {
    T = sqrt(1 - T * T);
    printf ("%.3f\n", X / (v * T));
  }
}