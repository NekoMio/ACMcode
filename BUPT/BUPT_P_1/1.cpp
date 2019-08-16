#include <algorithm>
#include <cstdio>
using namespace std;

long long a, b, c, d, e, f, g, i, m, n, r, s, t;
long long xa[500000] = {0}, xb[500000] = {0}, xc[500000] = {0};
long long w[500000];

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld%lld", &b, &c, &d);
    for (i = 1; i <= b; i++) {
      scanf("%lld", &xa[i]);
    }
    r = 0;
    for (i = 1; i <= d; i++) {
      scanf("%lld%lld", &e, &f);
      e = xa[e];
      if (f <= e)
        s = e - f;
      else {
        s = (f - e) / c;
        s = c * (s + 1) - (f - e);
        s %= c;
      }
      r += s;
      w[i] = s;
      // printf("1---%lld %lld %lld\n",i,r,s);
    }
    sort(w + 1, w + d + 1);
    t = r;
    f = 0;
    for (i = 1; i <= d; i++) {
      e = w[i];
      g = 1;
      while ((i <= d) && (w[i + 1] == e)) i++, g++;
      r -= d * (e - f);
      if (t > r) t = r;
      // printf("2---%lld %lld %lld %lld %lld\n",i,f,e,g,r);
      r += g * c;
      f = e;
    }
    printf("%lld\n", t);
  }
}