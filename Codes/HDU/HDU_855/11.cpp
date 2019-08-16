#include <algorithm>
#include <cstdio>
using namespace std;

struct xl {
  long long p, q;
};

bool sx(xl j, xl k) { return j.p < k.p; }

long long a, b, c, d, e, f, i, m, n, r, s, t;
xl w[2000000];

inline void Get(long long &j) {
  j = 0;
  char ch;
  do {
    ch = getchar();
  } while (ch < '0' || ch > '9');
  do {
    j = j * 10 + ch - '0';
    ch = getchar();
  } while (ch >= '0' && ch <= '9');
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  Get(a);  //
  for (i = 1; i <= a; i++) {
    Get(b);  //
    for (m = 1; m <= b; m++) {
      Get(w[m].p);  //
      Get(w[m].q);  //
    }
    sort(w + 1, w + b + 1, sx);
    c = 0;
    for (m = b; m > 1; m--) {
      // printf("%lld %lld\n",w[m].p,w[m-1].p);
      if (w[m].p <= w[m - 1].q)
        d = w[m].p;
      else
        d = w[m - 1].q;
      c += d;
      w[m].p -= d;
      w[m - 1].q -= d;
      if (w[m - 1].p <= w[m].q)
        d = w[m - 1].p;
      else
        d = w[m].q;
      c += d;
      w[m - 1].p -= d;
      w[m].q -= d;
      w[m - 1].p += w[m].p;
      w[m - 1].q += w[m].q;
    }
    printf("%lld\n", c);
  }
}