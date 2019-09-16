#include <bits/stdc++.h>
using namespace std;
double F[1005];
char s[1000005];
int main() {
  int T;
  scanf ("%d", &T);
  double a = 0;
  while (T--) {
    scanf ("%s%lf", s, &a);
    F[1] = a * 5.0 / 3;
    // double a = 100000;
    for (int i = 2; i <= 1000; i++)
      F[i] = (a * (5 * F[i - 1] + 3 * a)) / (3 * F[i - 1] + 2 * a);
    if (strlen(s) == 1) {
      printf ("%.10f\n", F[s[0] - '0']);
    } else if (strlen(s) == 2) {
      printf ("%.10f\n", F[(s[0] - '0') * 10 + s[1] - '0']);
    } else if (strlen(s) == 3) {
      printf ("%.10f\n", F[(s[0] - '0') * 100 + (s[1] - '0') * 10 + s[2] - '0']);
    } else {
      printf ("%.10f\n", F[1000]);
    }
  }
  // while (1);
}