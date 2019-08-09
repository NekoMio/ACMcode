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
int f[2][10][2][10][2];
int main() {
  int T = read();
  while (T--) {
    int n = read();
    int now = 0;
    f[now][1][0][1][0] = 1;
    f[now][1][1][1][1] = 1;
    for (int i = 2; i <= n; i++) {
      now ^= 1;
      memset (f[now], 0, sizeof (f[now]));
      for (int j = 2; j <= 6; j++) {
        
      }
    }
  }
}