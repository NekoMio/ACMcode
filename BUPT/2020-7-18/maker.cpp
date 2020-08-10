#include <bits/stdc++.h>
using namespace std;
int main() {
  int T = 1, n = 8e4, m = 8e4;
  printf ("%d\n", T);
  while (T--) {
    printf ("%d %d\n", n, m);
    for (int i = 1; i <= m; i++) {
      int x = rand() % n, y = rand() % n;
      while (y == x) y = rand() % n;
      printf ("%d %d\n", x, y);
    }
    int Q = 8e4;
    printf ("%d\n", Q);
    for (int i = 1; i <= Q; i++) {
      printf ("%d ", rand() % n);
    }
    printf ("\n");
  }
}