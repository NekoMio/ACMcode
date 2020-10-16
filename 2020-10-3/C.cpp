#include <bits/stdc++.h>
using namespace std;
int Map[25][25], n;
bool flag[21];
int st[25];
bool Judge() {
  for (int i = 1; i <= n; i++) {
    if (!flag[i] && Map[i][st[1]] == 1) return 1;
  }
  return 0;
}
void DFS(int cnt) {
  if (cnt == n + 1) {
    if (Map[st[n]][st[1]] != 1) return;
    for (int i = 1; i <= n; i++) {
      printf ("%d%c", st[i], " \n"[i == n]);
    }
    exit(0);
  }
  if (cnt <= 15)
    if (!Judge()) return;
  for (int i = 1; i <= n; i++) {
    if (!flag[i] && Map[st[cnt - 1]][i] == 1) {
      st[cnt] = i;
      flag[i] = 1;
      DFS(cnt + 1);
      flag[i] = 0;
    }
  }
}
int main() {
  char s[30];
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf ("%s", s + 1);
    for (int j = 1; j <= n; j++) {
      if (s[j] == 'W') {
        Map[i][j] = 1;
      } else if (s[j] == 'L') {
        if (Map[i][j] != 1)
          Map[i][j] = -1;
        Map[j][i] = 1;
      } else {
        if (Map[i][j] != 1)
          Map[i][j] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    st[1] = i;
    flag[i] = 1;
    DFS(2);
    flag[i] = 0;
  }
  printf ("No Solution\n");
}