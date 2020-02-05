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
const int MAXN = 1e6 + 5;
int a[MAXN], L[MAXN], R[MAXN];
bool flag[MAXN];
int main() {
  int n = read(), x = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    if (L[a[i]] == 0) L[a[i]] = i;
    R[a[i]] = i;
  }
  L[x + 1] = n + 1;
  for (int i = x; i >= 1; i--) {
    if (L[i] == 0) {
      L[i] = L[i + 1], R[i] = L[i + 1];
      flag[i] = 1;
    }
  }
  int pos = x;
  for (int i = x - 1; i >= 1; i--) {
    if (R[i] <= L[i + 1])
      pos = i;
    else
      break;
  }
  int Mx = 0;
  long long Ans = 0;
  for (int i = 1; i <= x; i++) {
    int ans = lower_bound(L + max(pos, i + 1), L + x + 1, Mx) - L;
    Ans = Ans + (x + 2 - ans);
    if (flag[i] != 1) {
      if (Mx > L[i]) break;
      Mx = max(Mx, R[i]);
    }
  }
  printf("%lld\n", Ans);
  // while (1);
}