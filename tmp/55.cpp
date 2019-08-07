#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#define N 2005
using namespace std;
int T, n;
struct nd {
  int x, y;
  long long da;
} nod[N];
bool cmp(nd a, nd b) {
  if (a.y == b.y) return a.x < b.x;
  return a.y < b.y;
}
int zz;
int B[N];
map<int, int> dl;
struct no {
  int left, right, mid;
  long long sum, lmx, rmx, mx;
} node[N * 10];
void build(int left, int right, int x) {
  node[x].mx = 0;
  node[x].left = left, node[x].right = right;
  node[x].sum = node[x].lmx = node[x].rmx = 0;
  if (left == right) return;
  int mid = (left + right) >> 1;
  node[x].mid = mid;
  build(left, mid, x << 1);
  build(mid + 1, right, x << 1 | 1);
}
void insert(int to, int x, int da) {
  if (node[x].left == node[x].right) {
    node[x].sum += da;
    node[x].rmx += da;
    node[x].lmx += da;
    node[x].mx += da;
    return;
  }
  int mid = node[x].mid;
  if (to > mid)
    insert(to, x << 1 | 1, da);
  else
    insert(to, x << 1, da);
  node[x].sum = node[x << 1].sum + node[x << 1 | 1].sum;

  if (node[x << 1].lmx > node[x << 1].sum + node[x << 1 | 1].lmx)
    node[x].lmx = node[x << 1].lmx;
  else
    node[x].lmx = node[x << 1].sum + node[x << 1 | 1].lmx;

  if (node[x << 1 | 1].rmx > node[x << 1 | 1].sum + node[x << 1].rmx)
    node[x].rmx = node[x << 1 | 1].rmx;
  else
    node[x].rmx = node[x << 1 | 1].sum + node[x << 1].rmx;

  node[x].mx = node[x].sum;
  if (node[x].mx < node[x << 1].rmx + node[x << 1 | 1].lmx)
    node[x].mx = node[x << 1].rmx + node[x << 1 | 1].lmx;
  if (node[x].mx < node[x << 1].mx) node[x].mx = node[x << 1].mx;
  if (node[x].mx < node[x << 1 | 1].mx) node[x].mx = node[x << 1 | 1].mx;
}
int main() {
  //    freopen("test.in","r",stdin);
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    dl.clear();
    for (int i = 1; i <= n; i++)
      scanf("%d%d%lld", &nod[i].x, &nod[i].y, &nod[i].da);
    sort(nod + 1, nod + 1 + n, cmp);
    zz = 0;
    for (int i = 1; i <= n; i++) {
      if (nod[i].x != nod[i - 1].x || nod[i].y != nod[i - 1].y || i == 1) zz++;
      if (nod[i].x == nod[i - 1].x && nod[i].y == nod[i - 1].y && i != 1)
        nod[zz].da += nod[i].da;
      else
        nod[zz] = nod[i];
    }
    n = zz;
    zz = 0;
    for (int i = 1; i <= n; i++) {
      zz++;
      B[zz] = nod[i].x;
    }
    sort(B + 1, B + zz + 1);
    zz = 0;
    for (int i = 1; i <= n; i++) {
      if (B[i] != B[i - 1] || i == 1) zz++;
      B[zz] = B[i];
      dl[B[i]] = zz;
    }
    for (int i = 1; i <= n; i++) nod[i].x = dl[nod[i].x];
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
      if (nod[i].da > ans) ans = nod[i].da;
      build(1, zz, 1);
      int to = n;
      for (int j = i; j <= n; j++) {
        if (nod[j].y == nod[i].y) {
          insert(nod[j].x, 1, nod[j].da);
        } else {
          to = j - 1;
          break;
        }
      }
      if (node[1].mx > ans) ans = node[1].mx;
      for (int j = to + 1; j <= n; j++) {
        int tto = n;
        for (int k = j; k <= n; k++) {
          if (nod[j].y == nod[k].y) {
            insert(nod[k].x, 1, nod[k].da);
          } else {
            tto = k - 1;
            break;
          }
        }
        if (node[1].mx > ans) ans = node[1].mx;
        j = tto;
      }
      i = to;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
/*

1
2
0 0 1
0 1 2
2
4
1 1 50
2 1 50
1 2 50
2 2 -500
2
-1 1 5
-1 1 1

1
4
0 1 10
0 2 -10
0 4 20
0 5 20

3
5
0 0 10
1 1 9
1 -1 9
-1 1 10
-1 -1 -10


4
1 1 50
2 1 50
1 2 50
2 2 -500
2
-1 1 5
-1 1 1
*/