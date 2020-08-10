#include <bits/stdc++.h>
using namespace std;
double ct[6];
bool Judge(double x, double *t, double &T) {
  memcpy(ct, t, sizeof (ct));
  ct[5] = x;
  sort(ct + 1, ct + 6);
  if (ct[2] + ct[3] + ct[4] <= 3 * T) return 1;
  else return 0;
}
int main() {
  double t[6], T;
  scanf ("%lf%lf%lf%lf", &t[1], &t[2], &t[3], &t[4]);
  scanf ("%lf", &T);
  sort(t + 1, t + 5);
  if (t[1] + t[2] + t[3] > 3 * T) printf ("impossible\n");
  else if (t[2] + t[3] + t[4] <= 3 * T) printf ("infinite\n");
  else {
    double l = 0, r = 30;
    while (r - l >= 1e-3) {
      double mid = (l + r) / 2;
      if (Judge(mid, t, T)) l = mid;
      else r = mid;
    }
    printf ("%.2f\n", l);
  }
}