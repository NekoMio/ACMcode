#include <bits/stdc++.h>
using namespace std;
int ct[6];
bool Judge(int x, int *t, int &T) {
  memcpy(ct, t, sizeof (ct));
  ct[5] = x;
  sort(ct + 1, ct + 6);
  if (ct[2] + ct[3] + ct[4] <= 3 * T) return 1;
  else return 0;
}
int at[6];
int main() {
  double t[6], T;
  scanf ("%lf%lf%lf%lf", &t[1], &t[2], &t[3], &t[4]);
  scanf ("%lf", &T);
  int TT = round(T * 100);
  for (int i = 1; i <= 4; i++) at[i] = round(t[i] * 100);
  sort(at + 1, at + 5);
  if (at[1] + at[2] + at[3] > 3 * TT) printf ("impossible\n");
  else if (at[2] + at[3] + at[4] <= 3 * TT) printf ("infinite\n");
  else {
    int ans = 0;
    for (int i = 100; i <= 2100; i++) {
      if (Judge(i, at, TT)) {
        ans = i;
      }
    }
    printf ("%.2f\n", ans / 100.0);
  }
}