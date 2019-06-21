#include <bits/stdc++.h>
using namespace std;
int tot;
inline int in()
{
  printf ("I\n");
  return ++tot;
}
inline void out(int x) {
  printf ("O %d\n", x);
  ++tot;
}
inline int sig(int x) {
  printf ("S %d\n", x);
  return ++tot;
}
inline int lsg(int x, int num) {
  printf ("< %d %d\n", x, num);
  return ++tot;
}
inline int rsg(int x, int num) {
  printf ("> %d %d\n", x, num);
  return ++tot;
}
inline int add(int x, int y) {
  printf ("+ %d %d\n", x, y);
  return ++tot;
}
inline int add(int x, string y) {
  printf ("C %d %s\n", x, y.c_str());
  return ++tot;
}
inline int filp(int x) {
  printf ("- %d\n", x);
  return ++tot;
}
inline string zeros(int x) {
  string s;
  for (int i = 1; i <= x; ++i) s += '0';
  return s;
}
void x_to_bits(int x, int *bits) {
  x = lsg(x, 500);
  long long t = 702955280397374434ll;
  char s[100];
  for (int i = 31; i >= 1; --i) {
    sprintf (s, "-%lld", t);
    bits[i] = sig(add(x, s + zeros(142)));
    x = add(x, filp(lsg(bits[i], 500 + i)));
    t /= 2;
  }
  bits[0] = rsg(x, 500);
}
int psgn(int x) {
  return sig(lsg(x, 500));
}
int cmpxtoy0(int p, int x) {
  p = lsg(p, 151);
  int y = sig(add(rsg(x, 150), p));
  return add(lsg(add(y, "-0.5"), 152), filp(p));
}
int main() {
  int a = in(), b = in(), m = in();
  int negm = filp(m);
  int ta[40], tb[40];
  x_to_bits(a, ta);
  x_to_bits(b, tb);
  // int zero = rsg(a, 1000);
  int ma = add(m, "-0.1");
  a = ta[31];
  a = add(a, cmpxtoy0(psgn(add(filp(a), ma)), negm));
  for (int i = 30; i >= 0; --i) {
    a = add(add(a, a), ta[i]);
    a = add(a, cmpxtoy0(psgn(add(filp(a), ma)), negm));
  }
  int ans = 0;
  ans = cmpxtoy0(add(filp(tb[0]), "1"), a);
  ans = add(ans, cmpxtoy0(psgn(add(filp(ans), ma)), negm));
  a = add(a, a);
  a = add(a, cmpxtoy0(psgn(add(filp(a), ma)), negm));
  for (int i = 1; i < 32; ++i) {
    ans = add(ans, cmpxtoy0(add(filp(tb[i]), "1"), a));
    ans = add(ans, cmpxtoy0(psgn(add(filp(ans), ma)), negm));
    
    if (i < 31) {
      a = add(a, a);
      a = add(a, cmpxtoy0(psgn(add(filp(a), ma)), negm));
    }
  }
  out(ans);
}

