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
long long __pow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a;
    b >>= 1;
    a = a * a;
  }
  return ans;
}
map<int, int> F[50];
int n, m;
int f(int a, int b) {
  if (F[b].count(a)) return F[b][a];
  if (a > pow(n, 1.0 / (b + 1)) + 0.0005)
    return !(((int)floor(pow(n, 1.0 / b) + 0.0005) - a) & 1);
  int tmp = 0;
  if (a + 1 <= pow(n, 1.0 / b) + 0.0005) tmp |= f(a + 1, b);
  if (__pow(1ll * a, 1ll * b + 1) <= n) tmp |= f(a, b + 1);
  return F[b][a] = !tmp;
}
int main() {
  n = read(), m = read();
  // memset (F, -1, sizeof (F));
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read();
    if (f(a, b))
      printf("No\n");
    else
      printf("Yes\n");
  }
}