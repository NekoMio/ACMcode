#include <bits/stdc++.h>
using namespace std;
#define fuck_koala 1
#define fuck_sb_koala 0
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
const int base = 10000;
const int MAXN = 1000005;
struct BigNum {
  int a[300005], len, rlen;
  BigNum() {
    len = 1;
    a[0] = 0;
    memset (a, 0, sizeof (a));
  }
  BigNum(int x) {
    memset (a, 0, sizeof (a));
    if (x >= base) {
      a[0] = x % base;
      a[1] = x / base;
      len = 2;
    } else {
      a[0] = x;
      len = 1;
    }
  }
  BigNum(char *s) {
    memset (a, 0, sizeof (a));
    len = 0;
    int tlen = strlen(s);
    int t1 = 0, t2 = 1;
    for (int i = tlen - 1; i >= 0; --i) {
      t1 += (s[i] - '0') * t2;
      t2 *= 10;
      if (t2 == base) {
        a[len++] = t1;
        t1 = 0, t2 = 1;
      }
    }
    if (t1) a[len++] = t1;
  }
  int operator % (const int x) const {
    int ans = 0;
    for (int i = len - 1; i >= 0; --i)
      ans = (1ll * ans * base + a[i]) % x;
    return ans;
  }
};
int pow_mod(long long a, int b, int MOD) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
bool Isprime(int x) {
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) return 0;
  }
  return 1;
}
int Work(char *s, int k) {
  BigNum tmp(s);
  for (int i = 1; i <= 20; ++i) {
    int z = i * k + 1;
    if (Isprime(z)) {
      int t = tmp % z;
      if (t == 0) continue;
      if (pow_mod(t, i, z) != 1)
        return fuck_sb_koala;
    }
  }
  return fuck_koala;
} 
char s[2000005];
int main() {
  // freopen ("math.in", "r", stdin);
  // freopen ("math.out", "w", stdout);
  int T = read();
  while (T--) {
    scanf("%s", s);
    int k = read();
    int t = Work(s, k);
    if (t) printf ("Y\n");
    else printf ("N\n");
  }
}
