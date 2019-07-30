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
int Num[11];
unsigned long long Ans, tmp1, tmp2, f[13], bin[13];
int main() {
  f[0] = 1, bin[1] = 1;
  for (int i = 1; i <= 12; i++) f[i] = f[i - 1] * i;
  for (int i = 2; i <= 12; i++) bin[i] = bin[i - 1] * 10;
  while (1) {
    int n = read();
    if (n == 0) break;
    Ans = 0;
    memset (Num, 0, sizeof (Num));
    for (int i = 1; i <= n; i++)
      Num[read()]++;
    tmp1 = 1;
    for (int i = 0; i <= 9; i++) {
      tmp1 *= f[Num[i]];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= 9; j++) if (Num[j]) {
        Ans += (f[n - 1] / (tmp1 / f[Num[j]] * f[Num[j] - 1])) * bin[i] * j;
      }
    }
    printf ("%llu\n", Ans);
  }
}