#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' && ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 1e6 + 5;
const int MOD = 998244353;
int a[MAXN], L[MAXN], R[MAXN];
int Q[MAXN], t;
long long Sum2[MAXN];
int main() {
  int n = read();
  a[0] = a[n + 1] = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i) a[i] = read();
  Q[++t] = 0;
  for (int i = 1; i <= n; ++i) {
    while (a[Q[t]] <= a[i]) L[i] = L[Q[t]], t--;
    if (L[i] == 0) L[i] = i;
    Q[++t] = i;
  }
  Q[t = 1] = n + 1;
  for (int i = n; i >= 1; --i) {
    while (a[Q[t]] < a[i]) R[i] = R[Q[t]], t--;
    if (R[i] == 0) R[i] = i;
    Q[++t] = i;
  }
  for (int i = 1; i <= n; ++i) {
    int p = i - L[i] + 1, q = R[i] - i + 1;
    if (p > q) swap(p, q);
    Sum2[1] = (Sum2[1] + a[i]) % MOD;
    Sum2[p + 1] = ((Sum2[p + 1] - a[i]) % MOD + MOD) % MOD;
    Sum2[q + 1] = ((Sum2[q + 1] - a[i]) % MOD + MOD) % MOD;
    Sum2[q + p + 1] = (Sum2[q + p + 1] + a[i]) % MOD;
  }
  for (int i = 1; i <= n; ++i) Sum2[i] = (Sum2[i - 1] + Sum2[i]) % MOD;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    Sum2[i] = (Sum2[i] + Sum2[i - 1]) % MOD;
    ans = ans ^ Sum2[i];
  }
  printf ("%d\n", ans);
}
