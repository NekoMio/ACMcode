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
int main() {
  int t = read();
  while (t--) {
    int a = read(), b = read(), c = read();
    int aa = a, bb = b, cc = c;
    int tmp = min(aa, bb / 2);
    bb -= tmp * 2;
    int Ans = tmp;
    tmp = min(bb, cc / 2);
    Ans += tmp;
    int Ans2 = 0;
    tmp = min(b, c / 2);
    Ans2 += tmp;
    b -= tmp;
    tmp = min(a, b / 2);
    Ans2 += tmp;
    printf ("%d\n", max(Ans2, Ans) * 3);
  }
  // while (1);
}