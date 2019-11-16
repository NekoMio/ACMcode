#include <bits/stdc++.h>
#include <cctype>
using namespace std;
char s[205][2025];
int start[205], len[205], ans[205];
int n;
char tmp[205 * 2025];
bool Judge(int m) {
  if (tmp[0] == '0') return 0;
  if (isalpha(tmp[0])) return 0;
  if (isalpha(tmp[m - 1])) return 0;
  return 1;
}
int main() {
  while (gets(s[++n])) {
    len[n] = strlen(s[n]);
  }
  n--;
  for (int i = n; i >= 2; i--) {
    if (isdigit(s[i][0]) && isdigit(s[i - 1][len[i - 1] - 1])) {
      for (; s[i][start[i]] != ' ' && start[i] < len[i]; start[i]++, len[i - 1]++) {
        s[i - 1][len[i - 1]] = s[i][start[i]];
      }
      start[i]++;
    }
  }
  for (int i = 1; i <= n; i++) while (s[i][len[i] - 1] == ' ') len[i]--;
  bool vis = 0;
  for (int i = 1; i <= n; i++) {
    int pos = 0;
    for (int j = start[i]; j < len[i]; j++) {
      if (s[i][j] != ' ')
        tmp[pos++] = s[i][j];
      else {
        if (pos != 0) {
          tmp[pos] = '\0';
          if (Judge(pos)) {
            printf ("%s ", tmp);
            ans[i]++;
          }
          pos = 0;
        }
      }
    }
    if (pos != 0) {
      tmp[pos] = '\0';
      if (Judge(pos)) {
        printf ("%s ", tmp);
        vis = 1;
        ans[i]++;
      }
      pos = 0;
    }
  }
  if (vis) printf ("\n");
  for (int i = 1; i <= n; i++) printf ("%d\n", ans[i]);
  while (1);
}