#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int a, b, x, y;
    scanf ("%d%d%d%d", &a, &b, &x, &y);
    long double d = abs((long double)b * x + a * y) / sqrt((long double)a * a + b * b);
    // printf ("%lf\n", d);
    long double L = -x + (d / a) * b;
    // printf ("%lf\n", L);
    long double a1 = 9.8 * (b / sqrt((long double)a * a + b * b));
    long double a2 = 9.8 * (a / sqrt((long double)a * a + b * b));
    long double T1 = sqrt(2 * L / a1);
    long double T2 = sqrt(2 * d / a2);
    cout << T1 << " " << T2 << endl;
    int D = floor((T1 / T2) + 0.01);
    int ans = 0;
    if (D & 1) ans = (D + 1) / 2;
    else ans = D / 2;
    printf ("%d\n", ans);
  }
}