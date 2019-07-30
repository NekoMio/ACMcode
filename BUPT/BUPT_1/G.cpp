#include <bits/stdc++.h>
using namespace std;
#define LL long long
inline LL read() {
  LL x = 0, f = 1;
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
int Numa[20], Numb[20];
int Get_Num(long long x, int *num) {
  int ans = 0;
  while (x) {
    num[++ans] = x % 10;
    x /= 10;
  }
  return ans;
}
LL pow_(LL x, int b) {
  LL ans = 1;
  while (b) {
    if (b & 1) ans = ans * x;
    b >>= 1;
    x = x * x;
  }
  return ans;
}
LL bin[20];
int main() {
  bin[0] = 1;
  for (int i = 1; i <= 15; i++) bin[i] = bin[i - 1] * 10;
  while (1) {
    LL n = read(), m = read();
    memset (Numa, 0, sizeof (Numa));
    memset (Numb, 0, sizeof (Numb));
    if (n < 0) break;
    int t = Get_Num(m, Numa);
    Get_Num(n, Numb);
    LL ans = 0;
    for (int i = 1; i < t; i++) {
      if (Numa[i] != 0) {
        if (Numb[i] == 0) {
          ans += (m / bin[i] - n / bin[i]) * bin[i - 1];
          if (n / bin[i]) ans += bin[i - 1] - n % bin[i - 1];
        } else {
          ans += (m / bin[i] - n / bin[i]) * bin[i - 1];
        }
      }
      else {
        if (Numb[i] == 0) {
          if (m / bin[i] - n / bin[i]) {
            ans += ((m / bin[i]) - (n / bin[i]) - 1) * bin[i - 1];
            ans += m % bin[i - 1] + 1;
            if (n / bin[i]) ans += bin[i - 1] - n % bin[i - 1];
          } else {
            ans += m % bin[i - 1] - n % bin[i - 1] + 1;
          }
        } else {
          ans += (m / bin[i] - n / bin[i] - 1) * bin[i - 1];
          ans += m % bin[i - 1] + 1;
          // if (n / bin[i]) ans += bin[i - 1] - n % bin[i - 1];
        }
      }
    }
    printf ("%lld\n", ans + (n == 0));
  }
}