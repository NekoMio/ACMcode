#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN], b[MAXN], t[MAXN];
int main() {
  FILE *f1, *f2;
  f1 = fopen("G.in", "r");
  f2 = fopen("G.out", "r");
  int T;
  fscanf (f1, "%d", &T);
  while (T--) {
    int n, k;
    fscanf (f1, "%d%d", &n, &k);
    for (int i = 1; i <= n; i++) fscanf (f1, "%d", &a[i]);
    for (int i = 1; i <= n; i++) fscanf (f1, "%d", &b[i]);
    int op;
    fscanf (f2, "%d", &op);
    if (op != -1) {
      for (int i = 1; i <= op; i++)
        fscanf (f2, "%d", &t[i]);
      long long SumA = 0, SumB = 0;
      int l = 1;
      for (int i = 1; i <= n; i++) {
        SumA += a[i], SumB += b[i];
        if (l <= op && i == t[l]) {
          if (SumA > SumB) SumA = SumA - SumB, SumB = 0;
          else SumA = 0, SumB = SumB - SumA;
          l++;
        }
        if (SumA < k && SumB >= k) {
          printf ("OK\n");
          break;
        }
      }
    } else {
      printf ("OK\n");
    }
  }
}