#include <bits/stdc++.h>
using namespace std;
char s[20], c[20];
int len = 0;
int trans(char *t) {
  int ret = 0;
  while (*t <= '9' && *t >= '0') {
    ret = ret * 10 + *t - '0';
    t++;
  }
  return ret;
}
bool cmp(char *c1, char *c2) {
  int n1, n2;
  for (int i = 1; i <= len; i++) {
    if (c2[i] == '\0') return 0;
    if (isdigit(c1[i]) && isdigit(c2[i])) {
      n1 = trans(c1 + i);
      n2 = trans(c2 + i);
      if (n1 != n2) {
        return n1 < n2;
      }
    } else if (isdigit(c1[i])) {
      return 1;
    } else if (isdigit(c2[i])) {
      return 0;
    } else if (c1[i] != c2[i]) {
      return c1[i] < c2[i];
    }
  }
  return 1;
}
int main() {
  int n;
  scanf ("%d", &n);
  scanf ("%s", s + 1);
  len = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    scanf ("%s", c + 1);
    printf ("%c\n", cmp(s, c) ? '+' : '-');
  }
}