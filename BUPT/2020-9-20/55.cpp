#include <bits/stdc++.h>
using namespace std;
bool flag1 = 0, flag2 = 0;
int Divide(int x) {
  int i = 2;
  int Sum = 0;
  while (i * i <= x) {
    while (x % i == 0) {
      Sum++;
      x /= i;
    }
    i++;
  }
  if (x != 1) Sum++;
  return Sum;
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, l;
    scanf ("%d", &n);
    int Ans = 0;
    for (int i = 1; i <= n; i++) {
      scanf ("%d", &l);
      Ans = Ans ^ Divide(l);
    }
    if (Ans == 0) printf ("L\n");
    else printf ("W\n");
  }  
}