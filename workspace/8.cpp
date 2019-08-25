#include <algorithm>
#include <cstdio>
using namespace std;
long long a, b, c, d, e, f, g, i, m, n;
long long x[200000] = {0};
long long w[200000] = {0};

bool sx(long long j, long long k) { return j > k; }

int main() {
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    scanf("%lld%lld", &b, &c);
    for (i = 1; i <= b; i++) {
      scanf("%lld", &x[i]);
    }
    sort(x + 1, x + b + 1);
    d = 0;
    e = 0;
    g = 0;
    m = 0;
    for (i = b; i >= 1; i--) {
      m++;
      if (e < m) {
        e++;
        // printf("  %d %d %d %d\n",e,g,w[1],c);
        if ((g > 0) && (w[1] < c)) {
          d += w[1];
          // printf("%d %d\n",d,w[1]);
          pop_heap(w + 1, w + g + 1, sx);
          g--;
        } else
          d += c;
      }
      d += x[i];
      f = x[i];
      // printf("%d %d %d\n",i,x[i],d);
      e += f / c;
      f -= f / c * c;
      if (f > 0) {
        g++;
        w[g] = c - f;
        push_heap(w + 1, w + g + 1, sx);
      }
      // printf("%lld %lld %lld %lld %lld\n",i,d,g,w[1],e);
    }
    printf("%lld\n", d);
  }
  return 0;
}
