#include <bits/stdc++.h>
using namespace std;
int Map[305][305];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    memset(Map, 0, sizeof(Map));
    if (n & 1) {
      for (int i = 1; i <= n; i += 2) {
        for (int j = 1; j <= n; j += 2) {
          Map[i][j] = 1;
        }
      }
      for (int i = 4; i <= n - 3; i += 4) {
        for (int j = 4; j <= n - 3; j += 4) {
          Map[i][j] = 1;
        }
      }
      for (int i = 6; i <= n - 3; i += 4) {
        for (int j = 6; j <= n - 3; j += 4) {
          Map[i][j] = 1;
        }
      }
    } else {
      if (n == 4) {
        Map[1][1] = Map[1][4] = Map[2][2] = Map[4][1] = Map[4][4] = 1;
      } else {
        for (int i = 1; i < n / 2; i += 2) {
          for (int j = 1; j <= n; j += 2) {
            Map[i][j] = 1;
          }
        }
        if (n / 2 >= 3) {
          for (int j = 2; j <= n; j += 2) {
            Map[n / 2][j] = 1;
          }
        }
        for (int i = n; i > n / 2 + 1; i -= 2) {
          for (int j = 2; j <= n; j += 2) {
            Map[i][j] = 1;
          }
        }
        if (n / 2 >= 3 && ((n / 2) & 1)) {
          for (int j = 3; j <= n; j += 2) {
            Map[n / 2 + 1][j] = 1;
          }
        } else {
          Map[n / 2][2] = 0, Map[n / 2 + 1][1] = 1;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        printf("%d%c", Map[i][j], " \n"[j == n]);
      }
    }
  }
}