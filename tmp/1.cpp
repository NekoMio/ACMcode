#include <stdio.h>
#include <string.h>
char s[106];
char b[15] = "chi1 huo3 guo1";
int Match() {
  int len = strlen(s);
  for (int i = 0; i + 13 < len; i++) {
    int j;
    for (j = 0; j < 14; j++) {
      if (s[i + j] != b[j]) break;
    }
    if (j == 14) return 1;
  }
  return 0;
}
int main() {
  int cnt = 0;
  int pos = 0, sum = 0;
  while (1) {
    gets(s);
    // getchar();
    // printf ("%s\n", s);
    if (strlen(s) == '0') continue;
    if (s[0] == '.') break;
    cnt++;
    if (Match()) {
      sum++;
      if (sum == 1) pos = cnt;
    }
  }
  printf ("%d\n", cnt);
  if (sum == 0) printf ("-_-#");
  else printf ("%d %d\n", pos, sum);
}