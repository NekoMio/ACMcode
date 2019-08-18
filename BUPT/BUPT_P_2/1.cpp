#include <cstdio>
using namespace std;
int main() {
  int T, cnt = 0;
  scanf ("%d", &T);
  while (T--) {
    int n;
    cnt++;
    scanf ("%d", &n);
    printf ("Case #%d: %d\n", cnt, n - 1);
  }
}