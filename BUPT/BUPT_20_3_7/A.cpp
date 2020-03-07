#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 200005
using namespace std;
int n;
long long Mx, sum, mx[N], size[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int l;
    scanf("%d", &l);
    size[i] = l;
    for (int j = 1; j <= l; j++) {
      long long x;
      scanf("%lld", &x);
      Mx = max(Mx, x);
      mx[i] = max(mx[i], x);
    }
  }
  for (int i = 1; i <= n; i++) {
    sum += 1ll * (Mx - mx[i]) * size[i];
  }
  printf("%lld\n", sum);
  return 0;
}
A