#include <bits/stdc++.h>
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
const int MAXN = 150000;
int prime[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_Prime() {
  isnprime[1] = 1;
  for (int i = 1; i <= MAXN; ++i) {
    if (!isnprime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt; ++j) {
      if (i * prime[j] > MAXN) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
int Sum[MAXN + 2];
int main() {
  Get_Prime();
  // printf ("%d\n", cnt);
  int n = read();
  for (int i = 1; i <= cnt && prime[i] <= n; ++i)
    for (int j = 1; j <= cnt && prime[i] + prime[j] <= n; ++j)
      ++Sum[prime[i] + prime[j]];
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = ans + 1ll * Sum[i] * Sum[n - i];
  }
  printf ("%lld\n", ans);
}
