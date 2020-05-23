#include <bits/stdc++.h>
using namespace std;
struct data {
  int a, b;
}a[5005];
int F[5005];
int T[5005];
int main() {
  int N, w;
  scanf ("%d%d", &N, &w);
  for (int i = 1; i <= N; i++) {
    scanf ("%d", &a[i].a);
    T[i] = a[i].a;
    a[i].b = i;
  }
  sort (a + 1, a + N + 1, [&] (data &x, data &y) -> bool{
    return x.a == y.a ? x.b < y.b : x.a < y.a;
  });
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    F[i] = 0;
    for (int j = 1; j <= i; j++) {
      if (a[j].a < a[i].a && abs(a[j].b - a[i].b) <= w) {
        F[i] = max(F[i], F[j] + 1);
        ans = max(ans, F[i]);
      }
    }
  }
  printf ("%d\n", ans);
}