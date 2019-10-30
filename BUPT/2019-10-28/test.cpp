#include <bits/stdc++.h>
using namespace std;
bool isprime(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}
double n = 1e100;
int main() {
  double p = 1;
  int cnt = 0;
  for (int i = 1; p < n; i++) {
    if (isprime(i)) {
      p *= i;
      printf ("%d\n", i);
      cnt++;
    }
  }
  printf ("%d\n", cnt);
  while (1);
}