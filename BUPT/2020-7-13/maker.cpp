#include <bits/stdc++.h>
using namespace std;
int a[10005], b[1003];
bool Judge(int i, int m) {
  for (int j = 1; j <= m; j++) {
    if (a[i + j - 1] < b[j]) return 0;
  }
  return 1;
}
int main() {
  int n = 10000, m = 5;
  FILE *f1 = fopen("1.in", "w");
  FILE *f2 = fopen("1.ans", "w");
  fprintf(f1, "%d %d\n", n, m);
  for (int i = 1; i <= n; i++) {
    fprintf(f1, "%d ", a[i] = rand() % 10 + 1);
  }
  fprintf(f1, "\n");
  for (int i = 1; i <= m; i++) {
    fprintf(f1, "%d ", b[i] = rand() % 10 + 1);
  }
  fprintf(f1, "\n");
  int ans = 0;
  for (int i = 1; i + m - 1 <= n; i++) {
    if (Judge(i, m)) {
      ans++;
      printf ("%d\n", i);
    }
  }
  fprintf(f2, "%d\n", ans);
}