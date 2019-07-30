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
const int MAXN = 10005, MAXK = 505;
int a[MAXN];
int f[MAXN][MAXK];
int main() {
  int n = read(), K = read();
  for (int i = 1; i <= n; i++)
    a[i] = read();
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= K; j++) {
      for (int k = 1; k <= i; k++) {
        if (a[i] > a[j]) f[i][j] = max(f[i][j], f[i][])
      }
    }
  }
}