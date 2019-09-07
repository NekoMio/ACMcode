#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
inline void gmax(int &a, int b) {
  if (a < b) a = b;
}
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
unordered_map<int,int> fa;
int find(int x) {
  if (x != fa[x]) fa[x] = find(fa[x]);
  return fa[x];
}
int main() {
  int n = read(), q = read();
  register int z, x;
  for (int i = 1; i <= q; i++) {
    z = read(), x = read();
    if (z == 1) {
      if (!fa.count(x)) {
        fa[x] = x;
      }
      if (fa.count(x + 1))
        fa[find(x)] = find(x + 1);
      if (fa.count(x - 1))
        fa[find(x - 1)] = find(x);
    }
    else {
      if (!fa.count(x)) printf ("%d\n", x);
      else printf ("%d\n", find(x) + 1);
    }
  }
  // while (1);
}