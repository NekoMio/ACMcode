#include <cstdio>
#include <cstring>
#include <algorithm>
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
  
  return x * f;
}
struct data {
  int x1, y1, x2, y2;
  void read() {
    x1 = ::read(), y1 = ::read(), x2 = ::read(), y2 = ::read();
  }
  bool in1(int x, int y) const {
    return x1 <= x && y1 <= y && x <= x2 && y <= y2;
  }
  bool in2(int x, int y) const {
    return x1 < x && y1 < y && x < x2 && y < y2;
  }
  bool operator == (const data &a) const {
    return x1 == a.x1 && y1 == a.y1 && x2 == a.x2 && y2 == a.y2;
  }
}a1, a2;
int Count() {
  int ret = 0;
  if (a1.x1 == a2.x1) ret++; 
  if (a1.y1 == a2.y1) ret++;
  if (a1.x2 == a2.x2) ret++;
  if (a1.y2 == a2.y2) ret++;
  return ret;
}
int CountX() {
  int ret = 0;
  if (a1.x1 == a2.x1) ret++; 
  if (a1.x2 == a2.x2) ret++;
  return ret;
}
bool Judge(const data &a1, const data &a2) {
  return !a1.in2(a2.x1, a2.y1) && !a1.in2(a2.x2, a2.y2) && !a1.in2(a2.x2, a2.y1) && !a1.in2(a2.x1, a2.y2);
}
int main() {
  // freopen ("9.in", "r", stdin);
  // freopen ("9.out",  "w", stdout);
  int T = read();
  while (T--) {
    a1.read(), a2.read();
    if (a1 == a2) printf ("2\n");
    else if (a1.in1(a2.x1, a2.y1) && a1.in1(a2.x2, a2.y2) && Count() == 2 && CountX() != 1) printf ("4\n");
    else if (a2.in1(a1.x1, a1.y1) && a2.in1(a1.x2, a1.y2) && Count() == 2 && CountX() != 1) printf ("4\n"); 
    else if (a1.in1(a2.x1, a2.y1) && a1.in1(a2.x2, a2.y2)) printf ("3\n");
    else if (a2.in1(a1.x1, a1.y1) && a2.in1(a1.x2, a1.y2)) printf ("3\n"); 
    else if (a1.x1 <= a2.x1 && a1.y1 >= a2.y1 && a1.x2 >= a2.x2 && a1.y2 <= a2.y2 && Count() == 1) printf ("5\n");
    else if (a2.x1 <= a1.x1 && a2.y1 >= a1.y1 && a2.x2 >= a1.x2 && a2.y2 <= a1.y2 && Count() == 1) printf ("5\n");
    else if (a1.x1 < a2.x1 && a1.y1 > a2.y1 && a1.x2 > a2.x2 && a1.y2 < a2.y2) printf ("6\n");
    else if (a2.x1 < a1.x1 && a2.y1 > a1.y1 && a2.x2 > a1.x2 && a2.y2 < a1.y2) printf ("6\n");
    else if (a2.x1 >= a1.x2 || a2.y1 >= a1.y2 || a1.x1 >= a2.x2 || a1.y1 >= a2.y2) printf ("3\n");
    else printf ("4\n");
  }
  // while (1);
}
/*
1
1 1 4 2
2 1 3 5
*/