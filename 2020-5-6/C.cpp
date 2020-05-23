#include <bits/stdc++.h>
using namespace std;
long long F[1510];
void add(int &a, int &b, int &c, int &n) {
  c++;
  if (c == n + 1) {
    c = 1;
    b++;
    if (b == n + 1) {
      b = 1;
      a++;
      if (a == n + 1) {
        a = 1;
        n++;
      }
    }
  }
}
void print (int a, int b, int c, int n) {
  char cc = (a >= c || b >= c) ? '>' : '<';
  printf ("%d^%d+%d^%d%c%d^%d\n", a, n, b, n, cc, c, n);
}
int main() {
  long long l, r, t;
  scanf ("%lld%lld", &l, &r);
  for (int i = 3; i <= 400; i++) F[i] = 1ll * i * i * i * i;
  int a, b, c, n;
  for (int i = 3; i <= 400; i++) {
    if (l <= F[i]) {
      n = i;
      break;
    }
  }
  t = l - 1;
  t -= F[n - 1];
  c = t % n + 1, t /= n;
  b = t % n + 1, t /= n;
  a = t % n + 1, t /= n;
  print (a, b, c, n);
  for (int i = l + 1; i <= r; i++) {
    add(a, b, c, n);
    print (a, b, c, n);
  }
}