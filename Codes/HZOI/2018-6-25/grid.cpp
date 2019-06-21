#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '0') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 405;
int id[MAXN][MAXN], Id, n, m, lst;
char s[MAXN][MAXN];
bool vis[MAXN][MAXN], in[MAXN][MAXN];
int C[MAXN][MAXN][2];
struct data {
  int x, y, id;
  data(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}
};
int Calc(int x, int y, int Id) {
  if (!in[x][y]) lst++;
  in[x][y] = 1;
  // C[x][y][Id] = 1;
  int ans = 0;
  if (s[x][y] == 'N') {
    if (Id == 1) {
      if (id[x - 1][y]) {
        if (!vis[x - 1][y]) {
          vis[x - 1][y] = 1;
          if (!C[x - 1][y][1])
            ans = Calc(x - 1, y, 1);
          else
            ans = C[x - 1][y][1];
          vis[x - 1][y] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
      if (id[x][y + 1]) {
        if (!vis[x][y + 1]) {
          vis[x][y + 1] = 1;
          if (s[x][y + 1] == 'N') {
            if (!C[x][y + 1][1])
              ans = Calc(x, y + 1, 1);
            else
              ans = C[x][y + 1][1];
          } else {
            if (!C[x][y + 1][2])
              ans = Calc(x, y + 1, 2);
            else
              ans = C[x][y + 1][2];
          }
          vis[x][y + 1] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
    } else {
      if (id[x + 1][y]) {
        if (!vis[x + 1][y]) {
          vis[x + 1][y] = 1;
          if (!C[x + 1][y][2])
            ans = Calc(x + 1, y, 2);
          else
            ans = C[x + 1][y][2];
          vis[x + 1][y] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
      if (id[x][y - 1]) {
        if (!vis[x][y - 1]) {
          vis[x][y - 1] = 1;
          if (s[x][y - 1] == 'N') {
            if (!C[x][y - 1][2])
              ans = Calc(x, y - 1, 2);
            else
              ans = C[x][y - 1][2];
          } else {
            if (!C[x][y - 1][1])
              ans = Calc(x, y - 1, 1);
            else
              ans = C[x][y - 1][1];
          }
          vis[x][y - 1] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
    }
  } else {
    if (Id == 1) {
      if (id[x - 1][y]) {
        if (!vis[x - 1][y]) {
          vis[x - 1][y] = 1;
          if (!C[x - 1][y][1])
            ans = Calc(x - 1, y, 1);
          else
            ans = C[x - 1][y][1];
          vis[x - 1][y] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
      if (id[x][y - 1]) {
        if (!vis[x][y - 1]) {
          vis[x][y - 1] = 1;
          if (s[x][y - 1] == 'N') {
            if (!C[x][y - 1][2])
              ans = Calc(x, y - 1, 2);
            else
              ans = C[x][y - 1][2];
          } else {
            if (!C[x][y - 1][1])
              ans = Calc(x, y - 1, 1);
            else
              ans = C[x][y - 1][1];
          }
          vis[x][y - 1] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
    } else {
      if (id[x + 1][y]) {
        if (!vis[x + 1][y]) {
          vis[x + 1][y] = 1;
          if (!C[x + 1][y][2])
            ans = Calc(x + 1, y, 2);
          else
            ans = C[x + 1][y][2];
          vis[x + 1][y] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
      if (id[x][y + 1]) {
        if (!vis[x][y + 1]) {
          vis[x][y + 1] = 1;
          if (s[x][y + 1] == 'N') {
            if (!C[x][y + 1][1])
              ans = Calc(x, y + 1, 1);
            else
              ans = C[x][y + 1][1];
          } else {
            if (!C[x][y + 1][2])
              ans = Calc(x, y + 1, 2);
            else
              ans = C[x][y + 1][2];
          }
          vis[x][y + 1] = 0;
          if (ans == -1) return C[x][y][Id] = -1;
        } else
          return C[x][y][Id] = -1;
      }
    }
  }
  return C[x][y][Id] = 1;
}
int Calc1(int _x, int _y, int op = 1) {
  if (op == 1) {
    memset(C, 0, sizeof(C));
    memset(in, 0, sizeof(in));
    lst = 0;
  }
  vis[_x][_y] = 1;
  int t = Calc(_x, _y, 1);
  vis[_x][_y] = 0;
  if (t == -1) return -1;
  return lst * 2;
}
int Calc2(int _x, int _y, int op = 1) {
  if (op == 1) {
    memset(C, 0, sizeof(C));
    memset(in, 0, sizeof(in));
    lst = 0;
  }
  vis[_x][_y] = 1;
  int t = Calc(_x, _y, 2);
  vis[_x][_y] = 0;
  if (t == -1) return -1;
  return lst * 2;
}
int ans[MAXN][MAXN];
int main() {
  memset(ans, -1, sizeof(ans));
  n = read(), m = read();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) id[i][j] = ++Id;
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
  }
  for (int j = 1; j <= m; ++j) {
    for (int i = 1; i <= n; ++i) {
      int t;
      t = Calc1(i, j, i == 1);
      if (t != -1) ans[i][j] = t;
    }
    for (int i = n; i >= 1; --i) {
      int t;
      t = Calc2(i, j, i == n);
      if (t != -1) {
        if (ans[i][j] == -1)
          ans[i][j] = t;
        else
          ans[i][j] = min(ans[i][j], t);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      printf("%d ", ans[i][j]);
    }
    printf("\n");
  }
}
