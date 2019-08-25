#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 5;;
int a[MAXN], b[MAXN];
bool flag[MAXN];
int main() {
  int n, m;
  scanf ("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &a[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf ("%d", &b[i]);
  }
  for (int i = m; i >= 1; i--) {
    if (!flag[b[i]]) {
      printf ("%d ", b[i]);
      flag[b[i]] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!flag[a[i]]) {
      printf ("%d ", a[i]);
      flag[a[i]] = 1;
    }
  }
  // while (1);
}