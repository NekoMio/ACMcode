#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
#define data pair<long long, long long>
vector<data> vc;
set<long long> st;
void DO(long long a, long long b) {
  if (st.count(a - b)) return;
  // assert(a > b);
  // fprintf (stderr, "%lld %lld\n", a, b);
  vc.push_back(data(a, b));
  st.insert(a - b);
} 
void Calc(long long a, long long b) {
  long long tmp = b;
  while (tmp * 2 <= (a / b) * b) {
    DO(a, tmp);
    DO(a - tmp, tmp);
    DO(a, a - tmp - tmp);
    tmp <<= 1;
  }
  long long k = a / b, T = a;
  for (int i = 0; (1ll << i) <= k; ++i) {
    if (k & (1ll << i)) {
      DO(T, (1ll << i) * b);
      T -= (1ll << i) * b;
    }
  }
}
void Gcd(long long a, long long b) {
  if (a % b == 0)
    return;
  Calc(a, b);
  Gcd(b, a % b);
}
int main() {
  long long a = read(), b = read(), c = read(), d = __gcd(a, b);
  if (a < b) swap(a, b);
  if (c % d != 0 || c > max(a, b)) return printf ("-1\n"), 0;
  if (a == c || b == c) return printf ("0\n"), 0;
  Gcd(a, b);
  // printf ("\n\n");
  long long tmp = d;
  while (tmp * 2 <= c) {
    DO(a, tmp);
    DO(a - tmp, tmp);
    DO(a, a - tmp - tmp);
    tmp <<= 1;
  }
  long long k = c / d, T = a;
  for (int i = 0; (1ll << i) <= k; ++i) {
    if (k & (1ll << i)) {
      DO(T, (1ll << i) * d);
      T -= (1ll << i) * d;
    }
  }
  DO(a, T);
  if (vc.size() > 400) return printf ("-1\n"), 0;
  printf ("%d\n", vc.size());
  for (auto x : vc) {
    printf ("%lld %lld\n", x.first, x.second);
  }
}
