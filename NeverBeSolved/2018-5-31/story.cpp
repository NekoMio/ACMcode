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
struct data {
  int l, r, h;
}a[MAXN];
int Work() {
  int n = read(), m = read(), q = read();
  int cnt1 = 0, cnt2 = 0;
  for (int i = 1; i <= m; ++i) {
    a[i].l = read(), a[i].r = read(), a[i].h = read();
    
  }
}
int main() {
  int T = read();
  while (T--) {
    printf ("%d\n", Work());
  }
}
