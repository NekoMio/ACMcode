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
char s[101005];
int S[205], E[205], len[205];
int ans[10];
int f[2][101005];
int max(int x, int y) {
  return x > y ? x : y;
}
int Calc(int x, int y) {
  register int now = 0;
  register int i, j;
  for (i = 0; i <= len[y] && i <= 9; ++i) f[now][i] = 0x3f3f3f3f;
  f[now][0] = 0;
  for (i = 0; i < len[x]; ++i) {
    now ^= 1;
    for (j = max(i - 8, 0); j <= len[y] && j <= i + 9; ++j) f[now][j] = 0x3f3f3f3f;
    for (j = max(i - 8, 0); j <= len[y] && j <= i + 8; ++j) {
      if (j != len[y] && s[S[x] + i] == s[S[y] + j]) f[now][j + 1] = min(f[now][j + 1], f[now ^ 1][j]);
      if (j != len[y]) f[now][j + 1] = min(f[now][j + 1], f[now ^ 1][j] + 1);
      if (j != len[y]) f[now ^ 1][j + 1] = min(f[now ^ 1][j + 1], f[now ^ 1][j] + 1);
      f[now][j] = min(f[now][j], f[now ^ 1][j] + 1);
    }
  }
  for (i = max(0, len[y] - 9); i < len[y]; ++i) {
    f[now][i + 1] = min(f[now][i + 1], f[now][i] + 1);
  }
  return f[now][len[y]];
}
int main() {
  // freopen("say3.in", "r", stdin);
  int n = read();
  for (int i = 1; i <= n; ++i) {
    S[i] = E[i - 1] + 1;
    scanf ("%s", s + S[i]);
    E[i] = S[i] + (len[i] = strlen(s + S[i])) - 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int t = Calc(i, j);
      if (t <= 8) ans[t]++;
    }
  }
  for (int i = 1; i <= 8; ++i) {
    printf ("%d ", ans[i]);
  }
}
