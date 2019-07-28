#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
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
int F[1105];
int a[1005], first[55];
int main() {
  while (1) {
    int n = read();
    if (n == 0) break;
    memset (first, 0, sizeof (first));
    for (int i = 1; i <= n; i++) {
      a[i] = read();
      if (first[a[i]] == 0) first[a[i]] = i;
    }
    int m = read(), Ans = m, tmp;
    if (m >= 5) {
      for (int k = 1; k <= 50; k++) if (first[k]) {
        memset (F, 0, sizeof (F));
        F[m - 5] = 1;
        for (int i = 1; i <= n; i++) {
          if (i != first[k]) {
            for (int j = 0; j <= m - 5; j++) {
              F[j] |= F[j + a[i]];
            }
          }
        }
        tmp = m - 5;
        for (int i = 0; i <= m - 5; i++) {
          if (F[i]) {
            tmp = i;
            break;
          }
        }
        Ans = min(Ans, tmp + 5 - k);
      }
    }
    printf ("%d\n", Ans);
  }
}