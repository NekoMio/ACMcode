#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 40000001
using namespace std;
int ans[200];
int fr[N], pr[N];
int T, m, n, Q, js;
int que[200];
int fw[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
      scanf("%d", &que[i]);
      fw[que[i]] = i;
    }
    js = 0;
    for (register int i = 1; i <= n; ++i) {
      fr[i] = i + 1;
      pr[i] = i - 1;
    }
    m++;
    pr[1] = n;
    fr[n] = 1;
    for (register int i = 1, nw = 1, j; i <= n && js <= Q; ++i) {
      if (fw[nw]) js++, ans[fw[nw]] = i;
      fr[pr[nw]] = fr[nw];
      pr[fr[nw]] = pr[nw];
      for (j = 1; j <= m; ++j) nw = fr[nw];
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]), fw[que[i]] = 0;
  }
  return 0;
}
/*
2
5
2
42

3
4
2
1

5
1
2
2
3

*/