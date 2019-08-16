#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
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
const int BASE = 10000;
struct BigNum2 /* 高精度 */
{
  int n;
  bitset<3600> s;
  BigNum2() {
    n = 0;
    s.reset();
  }
  void operator = (const BigNum2 &b) {
    n = b.n;
    s = b.s;
  }
  BigNum2 operator<<(const int x) {
    BigNum2 ans;
    ans.n = n + x;
    ans.s = s << x;
    return ans;
  }
  BigNum2 operator>>(const int x) {
    BigNum2 ans;
    ans.n = n - x;
    ans.s = s >> x;
    return ans;
  }
  void operator-=(const BigNum2 &b) {
    for (int i = 0; i < n; i++) {
      if (s[i] < b.s[i]) {
        for (int j = i + 1; j < n; j++) {
          if (s[j] == 1) {
            s[j] = 0;
            break;
          } else
            s[j] = 1;
        }
        s[i] = 1;
      } else {
        s[i] = s[i] ^ b.s[i];
      }
    }
    while (n > 1 && s[n - 1] == 0) n--;
  }
  void operator|=(int x) {
    s[x] = 1;
    if (n == 0) n = x + 1;
  }
  BigNum2 operator-(const BigNum2 &b) const {
    BigNum2 ans = *this;
    for (int i = 0; i < n; i++) {
      if (ans.s[i] < b.s[i]) {
        for (int j = i + 1; j < n; j++) {
          if (ans.s[j] == 1) {
            ans.s[j] = 0;
            break;
          } else
            ans.s[j] = 1;
        }
        ans.s[i] = 1;
      } else {
        ans.s[i] = ans.s[i] ^ b.s[i];
      }
    }
    while (ans.n > 1 && ans.s[ans.n - 1] == 0) ans.n--;
    return ans;
  }
  bool operator>(const BigNum2 &a) const {
    if (n != a.n) return n > a.n;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] < a.s[i]) return 0;
      if (s[i] > a.s[i]) return 1;
    }
    return 0;
  }
  bool operator>=(const BigNum2 &a) const {
    if (n != a.n) return n > a.n;
    for (int i = n - 1; i >= 0; i--) {
      if (s[i] < a.s[i]) return 0;
      if (s[i] > a.s[i]) return 1;
    }
    return 1;
  }
  bool iszero() {
    if (n == 1 && s[0] == 0) return 1;
    return 0;
  }
  void clear() {
    n = 0;
    s.reset();
  }
}n2, m2, ans2;
class BigNum
{
 public:
  int n;
  int s[255];
  void build(const BigNum2 &a) {
    n = 1;
    s[0] = 0;
    for (int i = a.n - 1; i >= 0; i--) {
      (*this)*=2;
      (*this)+=a.s[i];
    }
  }
  BigNum(const char *c = "") {
    long long sum = 0, su = 1;
    int len = strlen(c);
    memset(s, 0, sizeof(s));
    n = 0;
    for (int j = len - 1; j >= 0; j--) {
      sum += (c[j] - '0') * su;
      su *= 10;
      if (su == BASE) {
        s[n++] = sum;
        sum = 0, su = 1;
      }
    }
    if (sum != 0 || n == 0) s[n++] = sum;
  }
  void operator+=(int a) {
    n++;
    s[0] += a;
    for (int i = 0; i <= n; i++) {
      s[i + 1] += s[i] / BASE;
      s[i] %= BASE;
    }
    while (n > 0 && s[n - 1] == 0) {
      n--;
    }
  }
  void operator*=(int a) {
    n++;
    for (int i = 0; i <= n; i++) s[i] *= a;
    for (int i = 0; i <= n; i++) {
      s[i + 1] += s[i] / BASE;
      s[i] %= BASE;
    }
    while (n > 0 && s[n - 1] == 0) {
      n--;
    }
  }
  void operator /= (const int &b) 
  {
    int y = 0, tmp;
    for (int i = n - 1; i >= 0; i--)
    {
      tmp = y;
      y = (y + s[i]) % b * BASE;
      s[i] = (tmp + s[i]) / b;
    }
    while (n > 1 && !s[n - 1])
      n--;
  }
  void print() {
    printf("%d", s[n - 1]);
    for (int i = n - 2; i >= 0; i--) printf("%05d", s[i]);
  }
} ans, n, m, tmp;
void build(BigNum2 &a, BigNum b) {
  a.clear();
  while (!(b.n == 1 && b.s[0] == 0)) {
    if (b.s[0] & 1) a.s[a.n] = 1;
    b /= 2;
    a.n++;
  }
}
int main() {
  int T = read();
  while (T--) {
    static char s[1004];
    scanf ("%s", s);
    n = s;
    scanf ("%s", s);
    m = s;
    ans2.clear();
    build(n2, n);
    build(m2, m);
    for (int i = n2.n - 1; i >= 0; i--) {
      if (n2 > (m2 << i) - m2) {
        if (m2 > (n2 >> i)) n2 = n2 - ((n2 >> i) << i);
        else n2 = n2 - (m2 << i);
        ans2 |= i;
      }
    }
    if (!n2.iszero()) ans2 |= 0;
    ans.build(ans2);
    ans.print();
    printf("\n");
  }
}