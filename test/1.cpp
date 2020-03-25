#include <cmath>
#include <cstdio>
int a, i, m, n;
double b, c, d, e, f, g;
double xa[5] = {0}, xb[5] = {0}, xc[5] = {0}, xd[5] = {0};
double ep = 0.00000001;
double pi = acos(-1);

void mi(double &j, double k) {
  if (j < 0) j = k;
  if ((k >= 0) && (k < j)) j = k;
}

double qj(int j, int k, int l) {
  double p = -1, q, r, s, t;
  if (xc[j] <= b) {
    if (xc[k] * xd[l] <= b + ep) mi(p, xc[k] * sqrt(1 - xd[l] * xd[l]));
  } else {
    q = sqrt(xc[j] * xc[j] - b * b);
    r = (xc[j] * xc[j] + q * q - b * b) / (2 * xc[j] * q);
    s = (xc[j] * xc[j] + b * b - q * q) / (2 * xc[j] * b);
    if (((r <= xd[k] + ep) && (s <= xd[l] + ep)) ||
        ((s <= xd[k] + ep) && (r <= xd[l] + ep)))
      return q;
    t = acos(xd[k]) + acos(s);
    if ((t < pi / 2 + ep) && (xc[l] * sin(t) > q - ep) &&
        (xc[l] * cos(t) < b + ep))
      mi(p, xc[l] * sin(t));
    t = acos(xd[l]) + acos(s);
    if ((t < pi / 2 + ep) && (xc[k] * sin(t) > q - ep) &&
        (xc[k] * cos(t) < b + ep))
      mi(p, xc[k] * sin(t));
  }
  return p;
}

int main() {
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    for (int i = 1; i <= 3; i++) {
      scanf("%lf%lf", &xa[i], &xb[i]);
    }
    scanf("%lf", &b);
    xc[1] = sqrt((xa[2] - xa[3]) * (xa[2] - xa[3]) +
                 (xb[2] - xb[3]) * (xb[2] - xb[3]));
    xc[2] = sqrt((xa[1] - xa[3]) * (xa[1] - xa[3]) +
                 (xb[1] - xb[3]) * (xb[1] - xb[3]));
    xc[3] = sqrt((xa[1] - xa[2]) * (xa[1] - xa[2]) +
                 (xb[1] - xb[2]) * (xb[1] - xb[2]));
    xd[1] =
        (xc[2] * xc[2] + xc[3] * xc[3] - xc[1] * xc[1]) / (2 * xc[2] * xc[3]);
    xd[2] =
        (xc[1] * xc[1] + xc[3] * xc[3] - xc[2] * xc[2]) / (2 * xc[1] * xc[3]);
    xd[3] =
        (xc[1] * xc[1] + xc[2] * xc[2] - xc[3] * xc[3]) / (2 * xc[1] * xc[2]);
    c = -1;
    mi(c, qj(1, 2, 3));
    mi(c, qj(1, 3, 2));
    mi(c, qj(2, 1, 3));
    mi(c, qj(2, 3, 1));
    mi(c, qj(3, 1, 2));
    mi(c, qj(3, 2, 1));
    if (c <= 0)
      printf("impossible\n");
    else
      printf("%.6f\n", c);
  }
}