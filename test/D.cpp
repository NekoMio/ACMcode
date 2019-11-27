#include <bits/stdc++.h>
using namespace std;
int Map[55][55];
int n;
int main() {
  while (~scanf("%d", &n)) {
    int S, E;
    scanf ("%d%d", &S, &E);
    memset (Map, 0x3f, sizeof(Map));
    for (int i = 1; i <= n; i++) Map[i][i] = 0;
    int a, b, c;
    while (1) {
      scanf ("%d", &a);
      if (a == 0) break;
      scanf ("%d%d", &b, &c);
      Map[a][b] = min(Map[a][b], c);
      Map[b][a] = Map[a][b];
    }
    for (int k = 1; k <= n; k++) 
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          Map[i][j] = min(Map[i][j], Map[i][k] + Map[k][j]);
    printf ("%d\n", Map[S][E]);
  }
}