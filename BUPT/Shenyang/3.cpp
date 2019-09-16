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
const int MAXN = 1005;
int p[MAXN], c[MAXN];
long long F[MAXN * 10];
int main() {
  int n, m;
  while (scanf ("%d %d", &n, &m) != EOF) {
    for (int i = 1; i <= n; i++)
      p[i] = read(), c[i] = read();
    int Ans = 0x7fffffff, Num = 0;
    memset (F, 0x3f, sizeof(F));
    F[0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= m - 1; j++) {
        if (j + c[i] >= m) {
          if (Ans > F[j] + p[i]) {
            Ans = F[j] + p[i];
            Num = j + c[i];
          } else if (Ans == F[j] + p[i]) {
            Num = max(Num, j + c[i]);
          }
        } else {
          F[j + c[i]] = min(F[j + c[i]], F[j] + p[i]);
        }
      }
    }
    printf ("%d %d\n", Ans, Num);
  }
  // while (1);
}