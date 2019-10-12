#include <bits/stdc++.h>
using namespace std;
char A[10] = "Adrien", B[10] = "Austin";
int main() {
  int n, k;
  scanf ("%d%d", &n, &k);
  if (n == 0) printf ("%s", B);
  else if (n == 1) printf ("%s", A);
  else if (n == 2) printf ("%s", k >= 2 ? A : B);
  else {
    if (n & 1) printf ("%s", A);
    else printf ("%s", k >= 2 ? A : B);
  }
  // while (1);
}