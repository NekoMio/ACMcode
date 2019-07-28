#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
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
int a[5000];
int dep[5000], n;
int Ans = 0;
void DFS(int rt, int d) {
  if (d == n) { dep[rt] = a[rt - 1]; return; }
  int l = rt << 1, r = rt << 1 | 1;
  DFS(l, d + 1);
  DFS(r, d + 1);
  if (dep[l] != dep[r])
    Ans += abs(dep[l] - dep[r]);
  dep[rt] = a[rt - 1] + max(dep[l], dep[r]);
}
int main() {
  n = read();
  int N = (1 << n + 1) - 2;
  for (int i = 1; i <= N; i++) {
    a[i] = read();
  }
  DFS(1, 0);
  printf ("%d\n", Ans);
  // while (1);
}
