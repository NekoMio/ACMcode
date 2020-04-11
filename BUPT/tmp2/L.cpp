#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 1;
int prime[MAXN], cnt;
bool isnprime[MAXN];
void Get_Prime(int n = 1e4) {
  isnprime[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isnprime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i * prime[j] > n) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) break; 
    }
  }
}
bool isprime(long long x) {
  for (int i = 2; 1ll * i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}
int main() {
  Get_Prime();
  int T, Cnt = 0;
  scanf ("%d", &T);
  long long n;
  bool flag = 0;
  while (T--) {
    printf ("Case %d: ", ++Cnt);
    scanf ("%lld", &n);
    if (n <= 11) printf ("IMPOSSIBLE\n");
    else {
      if (n & 1) {
        n -= 9;
        flag = 1;
      } else {
        n -= 8;
        flag = 0;
      }
      for (int i = 1; i <= cnt; i++) {
        if (isprime(n - prime[i])) {
          printf ("2 2 2 %d %d %lld\n", 2 + flag, prime[i], n - prime[i]);
          break;
        }
      }
    }
  }
}