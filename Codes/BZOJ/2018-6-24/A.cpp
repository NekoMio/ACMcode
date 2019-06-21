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
long long bin[65];
int main() {
  int T = read();
  bin[0] = 1;
  for (int i = 1; i <= 60; ++i) bin[i] = bin[i - 1] * 2;
  for (int i = 0; i <= 60; ++i) bin[i] = bin[i] - 1;
  while (T--) {
    int n, t;
    long long p;
    scanf ("%d %lld", &n, &p);
    for (int i = 0; i <= n; ++i) {
      if (p <= bin[i + 1]) {
        printf ("%lld\n", p - bin[i] - 1);
        break;
      }
    }
  }
}
