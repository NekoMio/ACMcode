#include <bits/stdc++.h>
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
const int INF = 0x3f3f3f3f;
int Map[305][305];
int D[605][305][305], n;
void DFS(int l, int r, int x, int id) {
  if (l == r) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        D[id][i][j] = Map[i][j];
      }
    }
    if (l != x) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          D[id][i][j] = min(D[id][i][j], D[id][i][l] + D[id][l][j]);
        }
      }
    }
    return;
  }
  int mid = l + r >> 1;
  DFS(l, mid, x, id << 1);
  DFS(mid + 1, r, x, id << 1 | 1);
  
}
int main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      Map[i][j] = read();
      if (Map[i][j] == -1) Map[i][j] = INF;
    }
  }
  long long Ans = 0;
  int d;
  for (int k = 1; k <= n; k++) {
    DFS(1, n, k, 1);
    for (int i = 1; i <= )
  }
  printf ("%lld\n", Ans);
  // while (1);
}