#include <bits/stdc++.h>
using namespace std;
int main() {
  int K, P, X;
  scanf ("%d%d%d", &K, &P, &X);
  int M = sqrt(1. * K * P / X);
  double ans = (K * P * 1. / M) + M * X;
  M++;
  ans = min(ans, (K * P * 1. / M) + M * X);
  printf ("%.3f\n", ans);
}