#include <bits/stdc++.h>
using namespace std;
char s[205][2005], st[100];
int Start[205], len[205], ans[205];
int top, id;
int main() {
  int cnt = 0;
  while (gets(s[cnt] + 1)) len[cnt] = strlen(s[cnt] + 1), cnt++;
  bool flag1 = 0, flag2 = 0, flag3 = 0;
  for (int i = 0; i < cnt; i++) {
    for (int j = 1; j <= len[i]; j++) {
      if (isdigit(s[i][j])) {
        if (!flag1) {
          if (isalpha(s[i][j - 1])) {
            flag2 = 1;
            flag1 = 1;
          } else {
            top = 0;
            id = i;
            flag1 = 1;
            flag3 = 0;
            st[++top] = s[i][j];
          }
        } else {
          // if (flag3 == 0 && s[i][j - 1] == '0') flag2 = 1;
          if (flag2) continue;
          else {
            // flag3 = 1;
            st[++top] = s[i][j];
          }
        }
        continue;
      } 
      if (!isalpha(s[i][j])) {
        if (flag2 == 0 && top != 0 && !isalpha(s[i][j - 1])) {
          for (int i = 1; i <= top; i++) {
            printf ("%c", st[i]);
          }
          printf (" ");
          ans[id]++;
        }
        top = 0;
        flag1 = flag2 = 0;
      }
      if (flag1 == 1 && flag2 == 0) {
        // if (flag3 == 0 && s[i][j - 1] == '0') flag2 = 1;
        if (flag2) continue;
        // flag3 = 1;
        // st[++top] = s[i][j];
      }
    }
    if (i == cnt - 1) break;
    if (!isdigit(s[i][len[i]]) || !isdigit(s[i + 1][1])) {
      top = 0;
      flag1 = flag2 = flag3 = 0;
    }
  }
  if (top != 0) {
    if (flag2 == 0) {
      for (int i = 1; i <= top; i++) {
        printf ("%c", st[i]);
      }
      printf (" ");
      ans[id]++;
    }
    top = 0;
    flag1 = flag2 = 0;
  }
  printf ("\n");
  for (int i = 0; i < cnt; i++) {
    printf ("%d\n", ans[i]);
  }
}