#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int MAXN = 1e7 + 5;
int a[MAXN];
int qu[MAXN], L, R;
void push(int x) {
  while (R >= L && a[qu[R]] <= a[x]) R--;
  qu[++R] = x;
}
void pop(int x) {
  if (R >= L && qu[L] >= x) L++;
}
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read(), k = read(), p = read(), q = read(), r = read(), MOD = read();
    p %= MOD, q %= MOD, r %= MOD;
    for (int i = 1; i <= k; i++) a[i] = read();
    for (int i = k + 1; i <= n; i++) a[i] = (1ll * a[i - 1] * p % MOD + 1ll * q * i % MOD + r) % MOD;
    L = 1, R = 0;
    long long ans1 = 0, ans2 = 0;
    for (int i = n; i >= n - m + 1; i--) push(i);
    ans1 += a[qu[L]] ^ (n - m + 1);
    ans2 += (R - L + 1)  ^ (n - m + 1);
    for (int i = n - m; i >= 1; i--) {
      push(i), pop(i + m);
      ans1 += a[qu[L]] ^ i;
      ans2 += (R - L + 1) ^ i;
    }
    printf ("%lld %lld\n", ans1, ans2);
  }
  // while (1);
}