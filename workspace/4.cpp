#include <cstdio>
#include <cstring>
#include <algorithm>
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
char mp[2005][2005];
int Sum[2005][2005], Sum2[2005][2005];
int Num[2005][2005], Num2[2005][2005];
int main() {
  int n = read(), k = read();
  for (int i = 1; i <= n; i++)
    scanf("%s", mp[i] + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      Sum[i][j] = Sum[i][j - 1] + (mp[i][j] == 'B');
    Sum[i][n + 1] = Sum[i][n] == 0;
    Sum[i][n + 1] += Sum[i - 1][n + 1];
  }
  for (int j = 1; j <= n; j++) {
    for (int i = 1; i <= n; i++)
      Num[i][j] = Num[i - 1][j] + (mp[i][j] == 'B');
    Num[n + 1][j] = Num[n][j] == 0;
    Num[n + 1][j] += Sum[n + 1][j - 1];
  }
  for (int j = 1; j <= n - k + 1; j++)
    for (int i = 1; i <= n; i++)
      Sum2[i][j] = Sum2[i - 1][j] + (Sum[i][j - 1] == 0 && (Sum[i][n] - Sum[i][j + k - 1]) == 0);
  for (int i = 1; i <= n - k + 1; i++)
    for (int j = 1; j <= n; j++)
      Num2[i][j] = Num2[i][j - 1] + (Num[i - 1][j] == 0 && (Num[n][j] - Num[i + k - 1][j]) == 0);
  int ans = 0;
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n + 1; j++) {
  //     printf ("%d ", Sum[i][j]);
  //   }
  //   printf ("\n");
  // }
  // for (int i = 1; i <= n + 1; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     printf ("%d ", Num[i][j]);
  //   }
  //   printf ("\n");
  // }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     printf ("%d ", Sum2[i][j]);
  //   }
  //   printf ("\n");
  // }
  for (int i = 1; i <= n - k + 1; i++) {
    for (int j = 1; j <= n - k + 1; j++) {
      ans = max(ans, Sum2[i + k - 1][j] - Sum2[i - 1][j] + Num2[i][j + k - 1] - Num2[i][j - 1] + \
        Sum[i - 1][n + 1] + Sum[n][n + 1] - Sum[i + k - 1][n + 1] + \
        Num[n + 1][j - 1] + Num[n + 1][n] - Num[n + 1][j + k - 1]);
    }
  }
  printf("%d\n", ans);
}