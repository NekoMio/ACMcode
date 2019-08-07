#include <bits/stdc++.h>
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
int Get_Num(long long x) {
  int ans = 0;
  while (x) {
    ans ++;
    x /= 10;
  }
  return ans;
}
long long Maxval = 0;
int main() {
  int n = read();
  if (n == 1) {
    printf("1\n9\n0\n-72\n");
    return 0;
  } else if (n == 2) {
    printf("50\n19\n25\n-63\n");
  } else if (n == 3) {
    printf("950\n109\n844\n27\n");
  } else {
    Maxval = 81ll * (n - 2) + 25;
    int x = Get_Num(Maxval) + 1;
    long long tmp = 0;
    for (int i = 1; i <= x - 2; i++) {
      tmp = tmp * 10 + 9;
    }
    tmp = tmp * 100 + 50;
    long long t = tmp - Maxval;
    for (int i = 1; i <= n - 2; i++) printf ("9");
    printf ("50\n1");
    for (int i = 2; i <= n - 1; i++) printf ("0");
    printf ("9\n");
    for (int i = 1; i <= n - x; i++) printf ("9");
    printf("%lld\n", t);
    for (int i = 1; i <= n - 3; i++) printf ("9");
    printf ("27\n");
  }
}