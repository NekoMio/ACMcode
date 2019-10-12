#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;
int main() {
  int x;
  scanf ("%d", &x);
  char c[5];
  c[1] = x / 100, c[2] = (x % 100) / 10, c[3] = x % 10;
  if (c[3] == 0) {
    printf ("The number cannot be changed.\n");
  } else {
    swap(c[1], c[3]);
    printf ("%d%d%d\n", c[1], c[2], c[3]);
  }
  // while (1);
}
