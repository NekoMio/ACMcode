#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 1;
int a[MAXN];
int main() {
  int T = 1;
  printf ("%d\n", T);
  int N = 1e6 - 1;
  for (int i = 1; i <= N; i++) {
    a[i] = i;
  }
  printf ("%d\n", N);
  random_shuffle(a + 1, a + N + 1);
  for (int i = 1; i <= N; i++) {
    printf ("%d ", a[i]);
  }
}