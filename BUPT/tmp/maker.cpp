#include <bits/stdc++.h>
using namespace std;
int main() {
  srand(time(NULL));
  int T = 10;
  printf ("%d\n" ,T);
  while (T--) {
    int n = 20;
    printf ("%d\n", n);
    for (int i = 1; i <= n; i++) {
      printf ("%d ", rand() % 30 + 1);
    }
    printf ("\n");
  }
}