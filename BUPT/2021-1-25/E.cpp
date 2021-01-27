#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  scanf ("%d%d", &a, &b);
  long long L = a + b - 1;
  long long ans = L * (L - 1) / 2;
  if (L & 1) ans += b;
  else ans += a;
  printf ("%lld\n", ans);
}