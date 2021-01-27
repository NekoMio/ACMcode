#include <bits/stdc++.h>
using namespace std;
char s[100005];
long long F[100005][2][10];
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; i++) s[i] -= '0';
  bool flag = 1;
  int Min = 9;
  for (int i = n; i >= 1; i--) {
    if (i == n) {
      if (s[i] != 0) Min = min((int)s[i], Min);
    } else {
      if (flag == 1) {
        if (s[i] != 0) Min = min((int)s[i], Min);
      } else {
        if (s[i] == 1) {
          Min = min(1, Min);
        }
        else if (s[i] != 0) {
          Min = min((int)s[i] - 1, Min);
        }
      }
    }
    if (s[i] != 9) {
      flag = 0;
    }
  }
  printf ("%d\n", Min);
}