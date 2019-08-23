#include <cstdio>
#include <algorithm>
using namespace std;
int a[100005], b[100005];
int main() {
  int T = 5;
  printf ("%d\n", T);
  while (T--) {
    int n = 100000, m = 100000;
    printf ("%d %d\n", n, m);
    for (int i = 1; i <= n; i++)
      a[i] = rand();
    for (int i = 1; i <= n; i++)
      b[i] = i;
    sort(b + 1, b + n + 1, [&](const int &x, const int &y){
      return a[x] < a[y];
    });
    for (int i = 1; i <= n; i++) {
      printf ("%d ", b[i]);
    }
    for (int i = 1; i <= m; i++) {
      int op = rand() & 1;
      if (op == 0) {
        printf ("1 %d\n", rand() % n + 1);
      } else {
        printf ("2 %d %d\n", rand() % n + 1, rand() % n + 1);
      }
    }
  }
}