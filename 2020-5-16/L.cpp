#include <bits/stdc++.h>
using namespace std;
bool flag[105], vis[105];
int Map[106][106];
set<int> st[105];
int main() {
  int n, k;
  scanf ("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf ("%d", &Map[i][j]);
      flag[Map[i][j]] = 1;
    }
  }
  int No = 0;
  for (int i = 1; i <= n; i++) {
    memset (vis, 0, sizeof (vis));
    for (int j = 1; j <= n; j++) {
      if (Map[i][j] != 0 && vis[Map[i][j]]) {
        No = 1;
      }
      vis[Map[i][j]] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    memset (vis, 0, sizeof (vis));
    for (int j = 1; j <= n; j++) {
      if (Map[j][i] != 0 && vis[Map[j][i]]) {
        No = 1;
      }
      vis[Map[j][i]] = 1;
    }
  }
  if (No) printf ("NO\n");
  else {
    printf ("YES\n");
    for (int j = 1; j <= n; j++) {
      for (int i = 1; i <= n; i++) {
        if (Map[i][j] != 0) st[j].insert(Map[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      memcpy(vis, flag, sizeof(vis));
      for (int j = 1; j <= n; j++) {
        if (Map[i][j] == 0) {
          for (int k = 1; k <= n; k++) {
            if (!vis[k] && !st[j].count(k)) {
              Map[i][j] = k;
              st[j].insert(k);
              vis[k] = 1;
              break;
            }
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        printf ("%d%c", Map[i][j], " \n"[j == n]);
      }
    }
  }
}