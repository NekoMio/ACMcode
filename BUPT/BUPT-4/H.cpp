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
char s[11];
int main() {
  int T = read();
  while (T--) {
    int n = read();
    bool flag = 0;
    for (int i = 1; i <= n; i++) {
      scanf ("%s", s);
      if (i % 2) {
        if (s[0] != '#') flag = 1;
      } else {
        if (s[0] == '#') flag = 1;
      }
    }
    printf ("%s\n", flag ? "No" : "Yes");
  }
}