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
int a[503];
int main() {
  int T = read();
  while (T--) {
    int N = read();
    for (int i = 1; i <= N; i++) {
      a[i] = read();
    }
    int Sum = 0;
    for (int i = 2; i <= N; i++) {
      Sum += a[i] - a[i - 1] - 1;
    }
    printf ("%d\n", Sum - min(a[2] - a[1] - 1, a[N] - a[N - 1] - 1));
  }
  // while (1);
}