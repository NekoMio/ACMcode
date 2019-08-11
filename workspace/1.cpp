#include <bits/stdc++.h>
using namespace std;
bool flag[11];
char c[100005];
int main() {
  int n;
  scanf ("%d", &n);
  scanf ("%s", c + 1);
  for (int i = 1; i <= n; i++) {
    if (c[i] == 'L') {
      for (int i = 0; i <= 9; i++) {
        if (!flag[i]) {
          flag[i] = 1;
          break;
        }
      }
    } else if (c[i] == 'R') {
      for (int i = 9; i >= 0; i--) {
        if (!flag[i]) {
          flag[i] = 1;
          break;
        }
      }
    } else {
      flag[c[i] - '0'] = 0;
    }
  }
  for (int i = 0; i <= 9; i++) {
    if (flag[i]) {
      printf ("1");
    } else {
      printf ("0");
    }
  }
  printf ("\n");
}