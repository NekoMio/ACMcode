#include <bits/stdc++.h>
using namespace std;
int main() {
  int T = 10;
  int N = 2e5, M = 2e5;
  printf ("%d\n", T);
  while (T--) {
    printf ("%d %d\n", N, M);
    for (int i = 1; i <= M; i++) {
      printf ("%d %d\n", i, rand() % N + 1);
    }
    for (int i = 1; i <= N; i++) {
      printf ("%d %d\n", rand(), rand());
    }
  }
}
