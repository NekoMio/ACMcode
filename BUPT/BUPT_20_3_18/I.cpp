#include <cstdio>
long long a, b, c, d, e, f, g, h, i, m, n, r, s, t, o;
long long xa[2000] = {0}, xb[2000] = {0}, xc[2000] = {0};
long long wa[2000] = {0}, wb[2000] = {0}, wc[2000] = {0};
long long za[200][200] = {0}, zb[200][200][200] = {0};
long long zc[200][2000] = {0};
long long y = 1000000007;

long long qj(long long j, long long k) {
  if (j < k) return qj(k, j);
  if (k == 0) return j;
  return qj(k, j % k);
}

int main() {
  for (i = 1; i <= 100; i++) {
    za[i][i] = i;
    for (m = i + 1; m <= 100; m++) {
      za[i][m] = za[m][i] = qj(i, m);
    }
  }
  h = 0;
  for (i = 1; i <= 100; i++) {
    for (m = 1; m <= i; m++) {
      if (i % m == 0) {
        for (n = 1; n <= m; n++) {
          if (m % n == 0) {
            h++;
            wa[h] = i;
            wb[h] = m;
            wc[h] = n;
            zb[i][m][n] = h;
          }
        }
      }
    }
  }
  xa[0] = xa[1] = 1;
  for (i = 2; i <= 100; i++) {
    xa[i] = (y - y / i) * xa[y % i] % y;
  }
  scanf("%lld", &a);
  for (o = 1; o <= a; o++) {
    scanf("%lld%lld", &b, &c);
    d = 0;
    for (i = 1; i <= b; i++) {
      scanf("%lld", &xb[i]);
      if (xb[i] == 0) d++;
    }
    for (i = 1; i <= c; i++) {
      scanf("%lld", &xc[i]);
    }
    for (i = 1; i <= b; i++) {
      for (m = 0; m <= h; m++) {
        zc[i][m] = 0;
      }
    }
    for (i = 1; i <= c; i++) {
      if (xb[3] != 0) i = xb[3];
      for (m = 1; m <= c; m++) {
        if (xb[2] != 0) m = xb[2];
        for (n = 1; n <= c; n++) {
          if (xb[1] != 0) n = xb[1];
          zc[3][zb[i][za[i][m]][za[za[i][m]][n]]]++;
          if (xb[1] != 0) n = c + 10;
        }
        if (xb[2] != 0) m = c + 10;
      }
      if (xb[3] != 0) i = c + 10;
    }
    for (i = 3; i < b; i++) {
      for (m = 1; m <= h; m++) {
        if (zc[i][m] > 0) {
          // printf("%lld %lld %lld\n",i,m,zc[i][m]);
          r = wa[m];
          s = wb[m];
          t = wc[m];
          for (n = 1; n <= c; n++) {
            if (xb[i + 1] != 0) n = xb[i + 1];
            e = zb[n][za[n][r]][za[n][s]];
            zc[i + 1][e] += zc[i][m] * xc[za[n][t]] % y;
            zc[i + 1][e] %= y;
            if (xb[i + 1] != 0) n = c + 1;
          }
        }
      }
    }
    e = 0;
    c = xa[c];
    for (i = 1; i <= h; i++) {
      e = (e + zc[b][i]) % y;
    }
    for (i = 1; i <= d; i++) {
      e = e * c % y;
    }
    printf("%lld\n", e);
  }
}