#include <bits/stdc++.h>
using namespace std;
int K = 1e9;
const int MAXN = 5e5 + 5;
int t[MAXN], a[MAXN];
int main() {
  int T = 4;
  printf ("%d\n", T);
  while (T--) {
    printf ("%d %d\n", MAXN - 5, (1ll * rand() * rand()) % K);
    for (int i = 1; i <= (MAXN - 5); i++) t[i] = i;
    random_shuffle(t + 1, t )
  }
}