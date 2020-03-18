#include <cstdio>
long long a, b, c, d, e, f, g, i, m, n;
long long xa[82][82][8000] = {0}, xb[82][82][8000] = {0};
long long w[20000] = {0};

long long qj(long long j, long long k, long long l) {
  long long r = 0;
  if ((j == b) || (k == c)) return w[l];
  if (xb[j][k][l] == i) return xa[j][k][l];
  if (j * k - b * c + l >= 1) r = qj(j, k, l - 1) * (j * k - b * c + l) % d;
  r = (r + (b - j) * k * qj(j + 1, k, l - 1)) % d;
  r = (r + j * (c - k) * qj(j, k + 1, l - 1)) % d;
  xa[j][k][l] = r;
  xb[j][k][l] = i;
  return r;
}

int main() {
  scanf("%lld", &a);
  w[0] = 1;
  for (i = 1; i <= a; i++) {
    scanf("%lld%lld%lld", &b, &c, &d);
    for (m = 1; m <= 10000; m++) {
      w[m] = w[m - 1] * m % d;
    }
    e = qj(1, 1, b * c - 1) * b * c % d;
    printf("%lld\n", e);
  }
}