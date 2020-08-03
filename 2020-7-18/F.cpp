#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 10005;
LL p[maxn];
LL c[maxn];
LL m;
void divide(LL n) {
  m = 0;
  for (LL i = 2; i <= (LL)sqrt(n); i++) {
    if (n % i == 0) {
      p[++m] = i, c[m] = 0;
      while (n % i == 0) n /= i, c[m]++;
    }
  }
  if (n > 1) p[++m] = n, c[m] = 1;
}
LL a, b, cc, d, e, f;
bool solve() {
  e = 1;
  for (e = 1; e <= f; e++) {
    if ((a + e * d) % f == 0) {
      cc = (a + e * d) / f;
      return true;
    }
  }
  return false;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%lld%lld", &a, &b);
    if (b == 1) {
      printf("-1 -1 -1 -1\n");
      continue;
    }
    divide(b);
    if (m == 1 && c[1] == 1) {
      printf("-1 -1 -1 -1\n");
      continue;
    }
    LL left, right;
    int flag = 0;
    for (left = 1; left <= m; left++) {
      for (right = left; right <= m; right++) {
        d = 1;
        for (LL i = left; i <= right; i++) d *= (LL)pow(p[i], c[i]);
        f = b / d;
        // if(d>=tempb||f>=tempb) continue;
        // cout<<d<<" "<<f<<endl;
        if (solve()) {
          printf("%lld %lld %lld %lld\n", cc, d, e, f);
          flag = 1;
        }
        if (flag) break;
      }
      if (flag) break;
    }
    if (!flag) printf("-1 -1 -1 -1\n");
  }
}
