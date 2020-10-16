#include <bits/stdc++.h>
using namespace std;
double c[2][10005];
double ans[10005];
int main() {
  int N1, N2;
  scanf ("%d", &N1);
  int tmp;
  int Mx1 = 0, Mx2 = 0;
  for (int i = 1; i <= N1; i++) {
    scanf ("%d", &tmp);
    Mx1 = max(Mx1, tmp);
    scanf ("%lf", &c[0][tmp]);
  }
  scanf ("%d", &N2);
  for (int i = 1; i <= N2; i++) {
    scanf ("%d", &tmp);
    Mx2 = max(Mx2, tmp);
    scanf ("%lf", &c[1][tmp]);
  }
  for (int i = Mx1; i >= Mx2; i--) {
    int mi = i - Mx2;
    if (abs(c[0][i] - 0) > 1e-5) {
      double p = c[0][i] / c[1][Mx2];
      for (int j = i, t = Mx2; t >= 0; j--, t--) {
        c[0][j] -= p * c[1][t];
      }
      ans[mi] = p;
    }
  }

  int num = 0;
  for (int i = Mx1 - Mx2; i >= 1; i--) {
    if (round(ans[i] * 10) != 0) {
      num++;
    }
  }
  if (round(ans[0] * 10) != 0) num++;
  printf ("%d ", num);
  int cnt = 0;
  for (int i = Mx1 - Mx2; i >= 1; i--) {
    if (round(ans[i] * 10) != 0) {
      cnt++;
      if (cnt != num) printf ("%d %.1f ", i, ans[i]);
      else printf ("%d %.1f", i, ans[i]);
    }
  }
  if (round(ans[0] * 10) != 0) printf ("0 %.1f", ans[0]);
  if (num == 0) printf ("0 0.0");
  printf("\n");
  int num2 = 0;
  for (int i = Mx2; i >= 1; i--) {
    if (round(c[0][i] * 10) != 0) {
      num2++;
    }
  }
  if (round(c[0][0] * 10) != 0) num2++;
  printf ("%d ", num2);
  int cnt2 = 0;
  for (int i = Mx2; i >= 1; i--) {
    if (round(c[0][i] * 10) != 0) {
      cnt2++;
      if (cnt2 != num2) printf ("%d %.1f ", i, c[0][i]);
      else printf ("%d %.1f", i, c[0][i]);
    }
  }
  if (round(c[0][0] * 10) != 0) printf ("0 %.1f", c[0][0]);
  if (num2 == 0) printf ("0 0.0");
  // printf ("\n");
}