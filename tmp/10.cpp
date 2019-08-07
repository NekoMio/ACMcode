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
const int MAXN = 1e5 + 5;
struct data {
  int l, r, op, d, id;
}a[MAXN];
int main() {
  int T = read(), tt = 0;
  while (T--) {
    tt++;
    int n = read(), m = read(), l, r, d;
    char op[10];
    for (int i = 1; i <= m; i++) {
      scanf ("%s", op);
      if (op[0] == 'w') {
        
        Update(l, r, d, 1, n, 1);
      }
  }
}