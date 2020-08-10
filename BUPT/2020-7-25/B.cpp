#include <bits/stdc++.h>
using namespace std;
long long w;
int t[50];
int main() {
  int n, u, v;
  scanf ("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf ("%d%d%lld", &u, &v, &w);
    int tmp = 1;
    while (w) {
      if (w & 1) t[tmp]++;
      w >>= 1;
      tmp++;
    }
  }
  long long ans = 0;
  for (int i = 1; i <= 40; i++) {
    ans = ans | ((t[i] >= 1) << (i - 1));
  }
  printf ("%lld\n", ans);
}