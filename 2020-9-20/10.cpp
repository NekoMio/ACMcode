#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, pre, a;
    scanf ("%d", &n);
    scanf ("%d", &pre);
    bool flag = 0;
    for (int i = 2; i <= n; i++) {
      scanf ("%d", &a);
      if (a == pre) flag = 1;
      pre = a;
    }
    printf ("%s\n", flag == 1 ? "NO" : "YES");
  }
}