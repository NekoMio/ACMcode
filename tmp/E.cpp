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
int base = 10000;
struct BigNum {
  int a[20];
  int len;
  BigNum(const char *s = "") {
    long long sum = 0, su = 1;
    int n = strlen(s);
    memset(a, 0, sizeof(a));
    len = 0;
    for (int j = n - 1; j >= 0; j--) {
      sum += (s[j] - '0') * su;
      su *= 10;
      if (su == base) {
        a[++len] = sum;
        sum = 0, su = 1;
      }
    }
    if (sum != 0 || len == 0) a[++len] = sum;
  }
  BigNum operator*(const int &b) const {
    BigNum ans;
    ans.len = len;
    int y = 0;
    for (int i = 1; i <= ans.len; i++) {
      ans.a[i] = a[i] * b + y;
      y = ans.a[i] / base;
      ans.a[i] %= base;
    }
    while (y) {
      ans.a[++ans.len] = y % base;
      y /= base;
    }
    return ans;
  }
  void operator*=(int x) {
    len++;
    for (int i = 1; i <= len; i++) a[i] *= x;
    for (int i = 1; i <= len; i++) {
      a[i + 1] += a[i] / base;
      a[i] %= base;
    }
    while (len > 0 && a[len] == 0) len--;
  }
  void print() {
    printf("%d", a[len]);
    for (int i = len - 1; i >= 1; i--) printf("%04d", a[i]);
  }
};
int st[100], tot;
int main() {
  int T = read();
  while (T--) {
    int n = read();
    if (n == 2)
      printf("-1\n");
    else if (n == 3)
      printf("1\n2\n3\n");
    else if (n == 4)
      printf("1\n2\n6\n9\n");
    if (n >= 5) {
      printf("1\n2\n3\n");
      BigNum Sum("6");
      for (int i = 4; i <= n - 2; i++) {
        Sum.print();
        printf("\n");
        Sum *= 2;
      }
      (Sum * 2).print();
      printf("\n");
      (Sum * 3).print();
      printf("\n");
    }
  }
}