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
const int MAXN = 105;
int h[MAXN];
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read(), k = read();
    for (int i = 1; i <= n; i++) h[i] = read();
    bool flag = 1;
    for (int i = 1; i < n; i++) {
      if (h[i] > h[i + 1]) {
        if (h[i + 1] - k < 0) {
          m += h[i];
        } else {
          m += h[i] - h[i + 1] + k;
        }
      }
      else {
        if (h[i + 1] - h[i] < k) {
          if (h[i + 1] < k) m += h[i];
          else m += h[i] - (h[i + 1] - k);
        } else {
          if (h[i + 1] - k - h[i] > m) {
            flag = 0;
            break;
          } else {
            m -= h[i + 1] - k - h[i];
          }
        }
      }
    }
    if (flag) printf ("YES\n");
    else printf ("NO\n");
  }
}