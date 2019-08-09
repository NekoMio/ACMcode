#include <vector>
#include <cstring>
#include <cstdio>
#include <bitset>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int a[100006];
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
      a[i] = read();
      if (a[i] > 0) m--;
    }
    if (m == 0) {
      for (int i = 1; i <= n; i++) {
        printf ("%s\n", a[i] > 0 ? "Truth" : "Not defined");
      }
    } else {
      for (int i = 1; i <= n; i++) {
        printf ("%s\n", a[i] > 0 ? "Lie" : "Not defined");
      }
    }
  }
}