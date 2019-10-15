#include <cstdio>
long long T, n, k, m, i;
long long js(long long x) {
  // printf("%lld %lld %lld\n",x,k,m);
  long long tmp, j;
  if (x == 1) return 0;
  if (x == m) return (k - 1) % m;
  if (k == 1) return n - m;
  if ((x > k) && (x - x / k >= m)) {
    tmp = js(x - x / k);
    if (tmp < x % k)
      return tmp - x % k + x;
    else
      return tmp - x % k + (tmp - x % k) / (k - 1);
  } else {
    tmp = (k - 1) % m;
    // printf("%lld %lld\n",m,x);
    for (j = m + 1; j <= x; j++) {
      tmp = (tmp + k) % j;
    }
    return tmp;
  }
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%lld", &T);
  for (i = 1; i <= T; i++) {
    scanf("%lld%lld%lld", &n, &m, &k);
    m = n - m + 1;
    printf("Case #%lld: %lld\n", i, js(n) + 1);
  }
}