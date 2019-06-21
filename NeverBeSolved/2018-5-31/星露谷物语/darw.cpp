#include <bits/stdc++.h>
using namespace std;
char s[2001][2001];
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
int main() {
  for (int i = 1; i <= 2000; ++i) {
    for (int j = 1; j <= 2000; ++j) {
      s[i][j] = '.';
    }
  }
  int n = read();
  for (int i = 1; i <= n; ++i) {
    int x = read() + 1000, y = read() + 1000;
    s[x][y] = '#';
    x = read() + 1000, y = read() + 1000;
    s[x][y] = '#';
  }
  for (int i = 1; i <= 2000; ++i) {
    for (int j = 1; j <= 2000; ++j) {
      printf ("%c", s[i][j]);
    }
    printf("\n");
  }
}
