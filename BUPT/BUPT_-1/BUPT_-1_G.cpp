#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <ctime>
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
int Map[1005][1005][5];
int DP[1005][1005][2], Num[1005][1005][2];
char pre[1005][1005][2];
bool flag = 0;
int X, Y;
int Get(int x, int b) {
  int ans = 0;
  while (x % b == 0) {
    ans ++;
    x /= b;
  }
  return ans;
}
stack<char> st;
int main() {
  // freopen ("1.in", "r", stdin);
  int n = read();
  // fprintf (stderr, "---%.3f---\n", (double)clock() / CLOCKS_PER_SEC);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      Map[i][j][0] = read();
      if (Map[i][j][0] == 0) {
        if (flag == 0) X = i, Y = j;
        flag = 1;
        continue;
      }
      Map[i][j][1] = Get(Map[i][j][0], 2);
      Map[i][j][2] = Get(Map[i][j][0], 5);
    }
  }
  // fprintf (stderr, "---%.3f---\n", (double)clock() / CLOCKS_PER_SEC);
  memset (DP, 0x3f, sizeof (DP));
  DP[1][0][0] = 0, DP[1][0][1] = 0;
  Num[1][0][0] = 0, Num[1][0][1] = 0;
  // fprintf (stderr, "---%.3f---\n", (double)clock() / CLOCKS_PER_SEC);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (DP[i - 1][j][0] < DP[i][j - 1][0]) {
        DP[i][j][0] = DP[i - 1][j][0] + Map[i][j][1];
        Num[i][j][0] = Num[i - 1][j][0] + Map[i][j][2];
        pre[i][j][0] = 'D';
      } else {
        DP[i][j][0] = DP[i][j - 1][0] + Map[i][j][1];
        Num[i][j][0] = Num[i][j - 1][0] + Map[i][j][2];
        pre[i][j][0] = 'R';
      }
      if (DP[i - 1][j][1] < DP[i][j - 1][1]) {
        DP[i][j][1] = DP[i - 1][j][1] + Map[i][j][2];
        Num[i][j][1] = Num[i - 1][j][1] + Map[i][j][1];
        pre[i][j][1] = 'D';
      } else {
        DP[i][j][1] = DP[i][j - 1][1] + Map[i][j][2];
        Num[i][j][1] = Num[i][j - 1][1] + Map[i][j][1];
        pre[i][j][1] = 'R';
      }
    }
  }
  int use = (DP[n][n][0] < DP[n][n][1] ? 0 : 1);
  if (DP[n][n][use] > 1 && flag) {
    printf ("1\n");
    for (int i = 1; i < X; i++) printf ("D");
    for (int i = 1; i < n; i++) printf ("R");
    for (int i = X; i < n; i++) printf ("D");
  } else {
    int x = n, y = n;
    for (int i = 1; i <= 2 * n - 2; i++) {
      st.push(pre[x][y][use]);
      if (pre[x][y][use] == 'D') x--;
      else y--;
    }
    printf ("%d\n", DP[n][n][use]);
    while (!st.empty()) {
      printf ("%c", st.top());
      st.pop();
    }
  }
  // while (1);
}