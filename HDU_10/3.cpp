#include <algorithm>
#include <cstdio>
using namespace std;

int a, b, c, d, e, f, g, i, m, n;
double h1, h2, h3, x[20000] = {0};

void ma(double &j, double k) {
  if (j < k) j = k;
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    for (i = 1; i <= b; i++) {
      scanf("%lf", &x[i]);
    }
    sort(x + 1, x + b + 1);
    h1 = x[b];
    h2 = 1;
    h3 = 0;
    for (i = 1; i <= b; i++) {
      h2 *= (1 - x[i]);
      h3 += x[i] / (1 - x[i]);
      ma(h1, h2 * h3);
    }
    h2 = 1;
    h3 = 0;
    for (i = b; i >= 1; i--) {
      h2 *= (1 - x[i]);
      h3 += x[i] / (1 - x[i]);
      ma(h1, h2 * h3);
    }
    printf("%.8lf\n", h1);
  }
}
#include <cstdio>
#include <algorithm>
using namespace std;

int a, b, c, d, e, f, g, i, m, n;
double h1, h2, h3, x[20000] = {0};

void ma(double &j, double k) {
  if (j < k) j = k;
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    for (i = 1; i <= b; i++) {
      scanf("%lf", &x[i]);
    }
    sort(x + 1, x + b + 1);
    h1 = x[b];
    h2 = 1;
    h3 = 0;
    for (i = 1; i <= b; i++) {
      h2 *= (1 - x[i]);
      h3 += x[i] / (1 - x[i]);
      ma(h1, h2 * h3);
    }
    h2 = 1;
    h3 = 0;
    for (i = b; i >= 1; i--) {
      h2 *= (1 - x[i]);
      h3 += x[i] / (1 - x[i]);
      ma(h1, h2 * h3);
    }
    printf("%.8lf\n", h1);
  