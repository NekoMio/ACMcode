#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
unsigned Hash[MAXN], bin[MAXN], base = 31;
char s[MAXN];
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
unsigned Get_Hash(int l, int r) {
  return Hash[r] - Hash[l - 1] * bin[r - l + 1];
}
int Query(int l, int r, int k, int n) {
  int H = Get_Hash(l, r);
  int len = r - l, t = 0;
  for (int i = 1; i <= n; i++) {
    if (H == Get_Hash(i, i + len)) t++;
    if (t == k) return i;
  }
  return -1;
}
int main() {
  int T = read();
  bin[0] = 1;
  for (int i = 1; i <= MAXN - 1; i++) bin[i] = bin[i - 1] * base;
  while (T--) {
    int n = read(), m = read();
    scanf ("%s", s + 1);
    for (int i = 1; i <= n; i++)
      Hash[i] = Hash[i - 1] * base + s[i];
    for (int i = 1; i <= m; i++) {
      int l = read(), r = read(), k = read();
      printf ("%d\n", Query(l, r, k, n));
    }
  }
}