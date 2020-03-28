#include <bits/stdc++.h>
using namespace std;
int Map[21][21];
int st[21];
char s[30];
int bin[13];
long long F[2][531442‬];
int Find(int x, int p) {
  x / bin[p - 1];
  return x % 3;
}
int main() {
  int T;
  bin[0] = 1;
  for (int i = 1; i <= 12; i++) bin[i] = bin[i - 1] * 3;
  scanf ("%d", &T);
  while (T--) {
    int m, n, k;
    scanf ("%d%d%d", &m, &n, &k);
    for (int i = 1; i <= m; i++) {
      scanf ("%s", s + 1);
      for (int j = 1; j <= n; j++)
        Map[j][i] = (s[j] == 'Q');
    }
    int N = (1 << m) - 1;
    F[0][0] = 1;
    int now = 0;
    int Num = N;
    for (int i = 1; i <= n; i++) {
      now ^= 1;
      for (int j = 1; j <= m; j++) st[i] |= ((!Map[i][j]) << (j - 1));
      Num &= st[i];
      for (int j = 0; j <= N; j++) {
        for (int x = 1; x <= m; x++) if (Map[i][x] && ((1 << (x - 1)) & j)) {
          for (int l = 0; l < k; l++) {
            F[now][j ^ (1 << (x - 1))][l + 1] += F[now ^ 1][j][l];
          }
        }
        for (int l = 0; l < k; l++) {
          F[now][j][l] += F[now ^ 1][j][l];
        }
      }
    }
    long long b = 1;
    for (int i = 1; i <= k; i++) {
      b = b * i;
      long long Sum = 0;
      for (int j = 0; j <= N; j++) {
        if (j )
        Sum += F[now][j][i];
      }
      printf ("%lld\n", Sum * b);
    }
  }
}