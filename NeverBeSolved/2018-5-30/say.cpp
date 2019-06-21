// #pragma GCC optimize("O2")
#include <bits/stdc++.h>
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
int S[205], E[205], len[205];
char s[1010005];
int Sum[10], ans;
int nowi, nowj;
inline void gmin(int &x, int y) {
  x > y ? x = y : 0;
}
void DFS(register int x, register int y, int Ans) {
  if (Ans + abs((len[nowi] - x) - (len[nowj] - y)) >= ans) return;
  while (x < len[nowi] && y < len[nowj] && s[S[nowi] + x] == s[S[nowj] + y]) x++, y++;
  if (x == len[nowi] && y == len[nowj]) {
    gmin(ans, Ans);
    return;
  }
  else if (x == len[nowi]) gmin(ans, Ans + len[nowj] - y);
  else if (y == len[nowj]) gmin(ans, Ans + len[nowi] - x);
  else {
    DFS(x + 1, y, Ans + 1);
    DFS(x, y + 1, Ans + 1);
    DFS(x + 1, y + 1, Ans + 1);
  }
}
int main() {
  // freopen ("say5.in", "r", stdin);
  int n = read();
  for (int i = 1; i <= n; ++i) {
    S[i] = E[i - 1] + 1;
    scanf ("%s", s + S[i]);
    E[i] = S[i] + (len[i] = strlen(s + S[i])) - 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) if (abs(len[i] - len[j]) <= 8) {
      ans = 9;
      nowi = i, nowj = j;
      DFS(0, 0, 0);
      Sum[ans]++;
    }
  }
  for (int i = 1; i <= 8; ++i) {
    printf ("%d ", Sum[i]);
  }
}
