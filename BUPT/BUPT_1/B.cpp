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
const int MAXN = 1e5 + 5;
int Num[MAXN];
int main() {
  int n = read();
  for (int i = 1; i <= n; i++) Num[read()]++;
  long long ans = 0, m = read();
  for (int i = 0; i < MAXN; i++) {
    while (m && Num[i]) {
      ans += i;
      Num[i]--;
      m--;
    }
    if (m == 0) break;
  }
  printf ("%lld\n", ans);
}