#include <bits/stdc++.h>
using namespace std;
vector<int> vc, vb;
int a[70];
int main() {
  FILE *f;
  f = fopen("I.in", "r");
  int n, d;
  fscanf(f, "%d", &n);
  for (int i = 1; i * 2 <= n * (n - 1); i++) {
    fscanf(f, "%d", &d);
    vb.push_back(d);
  }
  printf ("%d\n", n);
  int T;
  scanf ("%d", &T);
  printf ("%d\n", T);
  while (T--) {
    for (int i = 1; i <= n; i++) {
      scanf ("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
      printf ("%d ", a[i]);
    }
    printf ("\n");
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        vc.push_back(abs(a[i] - a[j]));
      }
    }
    sort(vc.begin(), vc.end());
    for (int i = 0; i * 2 < n * (n - 1); i++) {
      if (vc[i] != vb[i]) return 1; 
    }
    vc.clear();
  }
  return 0;
}