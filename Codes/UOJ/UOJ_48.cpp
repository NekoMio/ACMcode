#include <bits/stdc++.h>
using namespace std;
template<typename _Tp>
inline _Tp read() {
  _Tp x = 0, f = 1;
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
const int MAXN = 1e5 + 5;
long long a[MAXN], c[1000];
int cnt;
void Divide(long long n) {
  cnt = 0;
  for (int i = 2; 1ll * i * i <= n; ++i) {
    if (n % i == 0) c[++cnt] = i;
    while (n % i == 0) n /= i;
  }
  if (n != 1) c[++cnt] = n;
  sort(c + 1, c + cnt + 1);
}
int main() {
  int n = read<int>();
  for (int i = 1; i <= n; ++i) {
    a[i] = read<long long>();
  }
  // printf ("%.4f\n", (double)clock() / CLOCKS_PER_SEC);
  Divide(a[1]);
  // printf ("%.4f\n", (double)clock() / CLOCKS_PER_SEC);
  for (int i = 1; i <= n; ++i) {
    long long t = __gcd(a[1], a[i]);
    for (int j = 1; j <= cnt + 1; ++j) {
      if (j == cnt + 1) {
        printf ("-1 ");
        break;
      }
      if (t % c[j] == 0) {
        printf ("%lld ", t / c[j]);
        break;
      }
    }
  }
}
