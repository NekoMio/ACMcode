#include <bits/stdc++.h>
using namespace std;
template<typename _Tp>
inline _Tp read() {
  _Tp x = 0, f = 1;
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
long long C[3];
int main() {
  long long n = read<long long>(), m = read<long long>();
  int Q = read<long long>();
  long long Gcd = __gcd(n, m);
  C[1] = n / Gcd, C[2] = m / Gcd;
  while (Q--) {
    long long se = read<long long>(), sy = read<long long>(), ex = read<long long>(), ey = read<long long>();
    // cerr << (sy - 1) / C[se] << " " << (ey - 1) / C[ex] << endl;
    if ((sy - 1) / C[se] == (ey - 1) / C[ex]) {
      printf ("YES\n");
    }
    else {
      printf ("NO\n");
    }
  }
} 