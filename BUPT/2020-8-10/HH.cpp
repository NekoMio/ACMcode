#include <bits/stdc++.h>
using namespace std;
int Map[305][305];
void Search(int n) {
  if (n == 2 || n == 1) {
    Map[1][1] = 1;
    return;
  }
  if (n == 3) {
    Map[1][1] = 1;
    Map[1][3] = 1;
    Map[3][1] = 1;
    Map[3][3] = 1;
    return;
  }
  if (n & 1) {
    Search(n / 2);
    int base = n / 2 + 1;
    for (int i = 1; i <= base - 1; i++) {
      for (int j = 1; j <= base - 1; j++) {
        Map[n - i + 1][j] = Map[i][j];
        Map[i][n - j + 1] = Map[i][j];
        Map[n - i + 1][n - j + 1] = Map[i][j];
      }
    }
    if (((n / 2) & 1) != 1) {
      for (int i = 1; i <= n; i += 2)
        Map[i][base] = Map[base][i] = 1;
    }
  } else {
    Search((n - 1) / 2);
    int base = n / 2 + 1;
    for (int i = 1; i <= base - 2; i++) {
      for (int j = 1; j <= base - 2; j++) {
        Map[n - i + 1][j] = Map[i][j];
        Map[i][n - j + 1] = Map[i][j];
        Map[n - i + 1][n - j + 1] = Map[i][j];
      }
    }
    Map[base - 1][base] = 1;
    Map[base][base - 1] = 1;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    memset(Map, 0, sizeof(Map));
    Search(n);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        printf("%d%c", Map[i][j], " \n"[j == n]);
      }
    }
  }
}