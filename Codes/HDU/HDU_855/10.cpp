#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
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
const int MAXN = 1e5 + 5;
struct data {
  char name[15];
  int num, ti;
  bool operator < (const data &b) {
    return num == b.num ? ti < b.ti : num > b.num;
  }
}a[MAXN];
int main() {
  int T = read();
  while (T--) {
    int n = read(), p = read();
    for (int i = 1; i <= n; i++)
      scanf ("%s%d%d", a[i].name, &a[i].num, &a[i].ti);
    sort(a + 1, a + n + 1);
    if (n * p % 10 == 5) {
      printf ("%s\n", a[n * p / 10 + 1].name);
    } else {
      printf ("Quailty is very great\n");
    }
  }
  // while (1);
}