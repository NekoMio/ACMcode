#pragma GCC optimize("O2")
#include <cstdio>

int a, b, c, d, g, h, i, m, n;
int y = 1000000007;
bool z[2000000];
int xa[200000], f, e, xc[1600000], xb[1600000];

int zh(int j, int k) {
  return 1ll * xb[j] * xc[j - k] % y * xc[k] % y;
}

long long km(long long j, long long k) {
  long long ans = 1;
  while (j) {
    if (j & 1) ans = ans * k % y;
    j >>= 1;
    k = k * k % y;
  }
  return ans;
}

int main() {
  int t = 0;
  register int r, s;
  for (r = 2; r <= 1500000; r++) {
    if (z[r] == 0) {
      t++;
      xa[t] = r;
    }
    for (s = 1; (s <= t) && (r * xa[s] <= 1500000); s++) {
      z[r * xa[s]] = 1;
      if (r % xa[s] == 0) s = t + 10;
    }
  }
  xb[0] = 1;
  xb[1] = 1;
  xc[0] = 1;
  xc[1] = 1;
  for (i = 2; i <= 1500000; i++) {
    xb[i] = 1ll * xb[i - 1] * i % y;
    xc[i] = 1ll * (y - y / i) * xc[y % i] % y;
  }
  for (i = 2; i <= 1500000; i++) {
    xc[i] = 1ll * xc[i - 1] * xc[i] % y;
  }
  scanf("%d", &a);
  for (r = 1; r <= a; r++) {
    scanf("%d%d%d", &b, &c, &d);
    b = xa[b];
    e = 0;
    for (i = 1; i <= d; i++) {
      f = zh(b + i, b - 1);
      if (f == 0)
        e += c;
      else
        e += 1ll * ((km(c + 1, f) - f) % y + y) % y * km(y - 2, f - 1) % y;
      e %= y;
    }
    printf("%d\n", e);
  }
}
// 1299709
// 622386287