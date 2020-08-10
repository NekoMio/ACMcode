#include <bits/stdc++.h>
using namespace std;
int MOD = 1e9;
int main() {
  int n = 1000000, m = 500000;
  printf("%d %d\n", n, m);
  for (int i = 1; i <= n; i++) {
    printf ("%d %d %d\n", 2, rand() * rand() % MOD, rand() * rand() % MOD);
  }
}