#include <bits/stdc++.h>
using namespace std;
char a[105], b[105];
int f[105][105], g[105];
int main() {
  while (scanf ("%s%s", a + 1, b + 1) != EOF) {
    int n = strlen(b + 1);
    memset (f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    for (int l = 2; l <= n; l++) {
      for (int i = 1; i + l - 1 <= n; i++) {
        int k = i + l - 1;
        f[i][k] = f[i + 1][k] + 1;
        for (int j = i + 1; j <= k; j++) {
          if (b[i] == b[j])
            f[i][k] = min(f[i][k], f[i + 1][j - 1] + f[j][k]);
        }
      }
    }
    // for (int i = 1; i <= n; i++) {
    //   for (int j = 1; j <= n; j++) {
    //     printf ("%d ", f[i][j]);
    //   }
    //   printf ("\n");
    // }
    memset (g, 0x3f, sizeof(g));
    g[0] = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] == b[i]) g[i] = g[i - 1];
      for (int j = i - 1; j >= 0; j--) {
        g[i] = min(g[i], g[j] + f[j + 1][i]);
      }
    }
    printf ("%d\n", g[n]);
  }
}