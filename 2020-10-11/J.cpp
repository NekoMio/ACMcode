#include <bits/stdc++.h>
using namespace std;
long long p[100005], a;
int st[100], top;
void print(__int128 a) {
  if (a == 0) printf ("0");
  top = 0;
  while (a != 0) {
    st[++top] = a % 10;
    a /= 10;
  }
  for (int i = top; i >= 1; i--) printf("%d", st[i]);
}
int main() {
  int n;
  scanf ("%d", &n);
  scanf ("%lld", &a);
  n--;
  for (int i = 1; i <= n; i++) {
    scanf ("%lld", &p[i]);
  }
  sort(p + 1, p + n + 1, [](const long long &b, const long long &c) -> bool {
    return b > c;
  });
  __int128 ans = 0;
  a = a - p[1];
  for (int i = 2; i <= n; i++) {
    if (a >= (__int128)(p[i - 1] - p[i]) * (i - 2)) {
      a -= (__int128)(p[i - 1] - p[i]) * (i - 2);
      ans += (__int128)(p[i - 1] - p[i]) * (i - 1);
    } else {
      ans += ((__int128)a / (i - 2)) * (i - 1) + (a % (i - 2));
      a = -1;
      break;
      // if (a % (i - 2) == (i - 3)) ans++;
    }
  }
  if (a != -1) {
    ans += ((__int128)a / (n - 1)) * n + (a % (n - 1));
  }
  print(ans);
}