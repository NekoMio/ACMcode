#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200000, BASE = 76543;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar();}
  return x * f;
}
struct Hash_Table {
  struct edge {
    int Id, next;
    long long Sum;
  }v[MAXN];
  int first[BASE + 1], p;
  Hash_Table() {
    memset(first, -1, sizeof (first));
    p = 0;
  }
  void clear() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  long long &operator[](const int &x) {
    int t = x % BASE;
    for (int i = first[t]; i != -1; i = v[i].next) {
      if (v[i].Id == x) return v[i].Sum;
    }
    v[p].next = first[t];
    v[p].Id = x;
    first[t] = p++;
    return v[p - 1].Sum = 0;
  }
}f[2];
bool Map[15][15];
char c[15];
int cnt, Ans, n, m;
int Get(int x, int j) {
  x >>= (j - 1);
  x &= 3;
  return x;
}
void Update(int S, int x, int y) {
  int tmp = S >> 2 * (x - 1);
  S -= tmp;
}
void DP() {
  int now = 0;
  f[now][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      now ^= 1;
      f[now].clear();
      bool flag = 0;
      for (int k = 0; k < f[now ^ 1].p; k++) {
        int Id = f[now ^ 1].v[k].Id;
        long long Sum = f[now ^ 1].v[k].Sum;
        int U = Get(Id, j), L = Get(Id, j + 1);
        if (Map[i][j]) {
          if (!flag) cnt--, flag = 1;
          if (!L && !U) f[now][Id] = Sum;
          continue;
        }
        
      }
    }
  }
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) {
    scanf ("%s", c + 1);
    for (int j = 1; j <= n; ++j) {
      cnt += Map[i][j] = c[j] == '*';
    }
  }
  DP();
  printf ("%lld\n", Ans);
}