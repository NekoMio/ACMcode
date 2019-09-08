#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

long long a, b, c, d, e, f, g, i, m, n, ha, hb, hc, r, s, t;
long long xa[5][5] = {0}, xb[5][5] = {0}, xc[5][5] = {0};
long long y = 998244353;
unordered_map<long long, long long> st;

void js(long long j) {
  if (j == 1) {
    for (r = 1; r <= 2; r++) {
      for (s = 1; s <= 2; s++) {
        xb[r][s] = xa[r][s];
      }
    }
  } else {
    js(j / 2);
    for (r = 1; r <= 2; r++) {
      for (s = 1; s <= 2; s++) {
        xc[r][s] = 0;
        for (t = 1; t <= 2; t++) {
          xc[r][s] += xb[r][t] * xb[t][s];
          xc[r][s] %= y;
        }
      }
    }
    for (r = 1; r <= 2; r++) {
      for (s = 1; s <= 2; s++) {
        xb[r][s] = xc[r][s];
      }
    }
    if (j & 1) {
      for (r = 1; r <= 2; r++) {
        for (s = 1; s <= 2; s++) {
          xc[r][s] = 0;
          for (t = 1; t <= 2; t++) {
            xc[r][s] += xb[r][t] * xa[t][s];
            xc[r][s] %= y;
          }
        }
      }
      for (r = 1; r <= 2; r++) {
        for (s = 1; s <= 2; s++) {
          xb[r][s] = xc[r][s];
        }
      }
    }
  }
}

int main() {
  scanf("%lld%lld", &a, &b);
  long long bb = b;
  xa[1][1] = 0;
  xa[1][2] = 2;
  xa[2][1] = 1;
  xa[2][2] = 3;
  d = 0;
  for (i = 1; i <= a; i++) {
    // if (b == bb) fprintf (stderr, "%lld\n", i);
    if (st.count(b)) {
      c = st[b];
    } else {
      if (b <= 1) {
        if (b == 0)
          c = 0;
        else
          c = 1;
      } else {
        js(b - 1);
        c = xb[2][2];
      }
      st[b] = c;
    }
    d ^= c;
    b ^= c * c;
  }
  printf("%lld", d);
}