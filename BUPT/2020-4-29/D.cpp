#include <bits/stdc++.h>
using namespace std;
char s[100], s1[100] = "bubble", s2[100] = "tapioka";
int main() {
  int len;
  bool flag = 0;
  for (int i = 1; i <= 3; i++) {
    scanf ("%s", s);
    len = strlen(s);
    if (len != 6 && len != 7) {
      printf ("%s%c", s, " \n"[i == 3]), flag = 1;
    } else if (len == 6) {
      int j;
      for (j = 0; j < len; j++) {
        if (s[j] != s1[j]) break;
      }
      if (j != len) printf ("%s%c", s, " \n"[i == 3]), flag = 1;
    } else {
      int j;
      for (j = 0; j < len; j++) {
        if (s[j] != s2[j]) break;
      }
      if (j != len) printf ("%s%c", s, " \n"[i == 3]), flag = 1;
    }
  }
  if (!flag) printf ("nothing\n");
}