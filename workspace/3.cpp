#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define N 200005
using namespace std;
int n, a[N], m;
int rnk[N], tp[N], cnt[N], SA[N], hi[N];
void Rsort() {
  for (int i = 0; i <= m; i++) cnt[i] = 0;
  for (int i = 1; i <= n; i++) cnt[rnk[tp[i]]]++;
  for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; i--) SA[cnt[rnk[tp[i]]]--] = tp[i];
}
bool cmp(int x, int y, int w) {
  return (tp[x] == tp[y] && tp[x + w] == tp[y + w]);
}
int M = 50;
void work() {
  memset(rnk, 0, sizeof(rnk));
  memset(tp, 0, sizeof(tp));
  memset(cnt, 0, sizeof(cnt));
  memset(SA, 0, sizeof(SA));
  memset(hi, 0, sizeof(hi));
  m = M * 2;
  for (int i = 1; i <= n; i++) rnk[i] = a[i], tp[i] = i;
  Rsort();
  for (int i, w = 1, p = 1; p < n; m = p, w <<= 1) {
    for (p = 0, i = n - w + 1; i <= n; i++) tp[++p] = i;
    for (i = 1; i <= n; i++)
      if (SA[i] > w) tp[++p] = SA[i] - w;
    Rsort();
    swap(rnk, tp);
    rnk[SA[1]] = p = 1;
    for (i = 2; i <= n; i++) rnk[SA[i]] = cmp(SA[i], SA[i - 1], w) ? p : ++p;
  }
  for (int j, i = 1, k = 0; i <= n; hi[rnk[i++]] = k)
    for (k = k ? k - 1 : k, j = SA[rnk[i] - 1]; a[i + k] == a[j + k]; k++)
      ;
}
int T, Q;
char A[N];
struct no {
  no* ch[2];
  int size;
  no() { ch[0] = ch[1] = 0, size = 0; }
}* null = new no(), *root[N];
no* new_node() {
  no* x = new no();
  x->ch[0] = x->ch[1] = null;
  return x;
}
void insert(no* la, no* nw, int l, int r, int to) {
  nw->size = la->size + 1;
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (to > mid) {
    nw->ch[1] = new_node();
    nw->ch[0] = la->ch[0];
    insert(la->ch[1], nw->ch[1], mid + 1, r, to);
  } else {
    nw->ch[0] = new_node();
    nw->ch[1] = la->ch[1];
    insert(la->ch[0], nw->ch[0], l, mid, to);
  }
}
int get_rank(no* la, no* nw, int l, int r, int k) {
  int mid;
  while (l <= r) {
    if (l == r) return l;
    mid = (l + r) >> 1;
    if (nw->ch[0]->size - la->ch[0]->size >= k) {
      r = mid;
      nw = nw->ch[0];
      la = la->ch[0];
    } else {
      l = mid + 1;
      k -= nw->ch[0]->size - la->ch[0]->size;
      nw = nw->ch[1];
      la = la->ch[1];
    }
    if (l == r) return l;
  }
}
int rmq[20][N], xp[20], low[N];
int get_min(int l, int r) {
  int len = r - l + 1;
  return min(rmq[low[len]][l], rmq[low[len]][r - xp[low[len]] + 1]);
}
int main() {
  //    freopen("test.in","r",stdin);
  //    freopen("1.out","w",stdout);
  null->ch[0] = null->ch[1] = null;
  scanf("%d", &T);
  xp[0] = 1;
  for (int i = 1; i <= 19; i++) xp[i] = xp[i - 1] << 1;
  for (int i = 1; i <= 100000; i++) {
    low[i] = low[i - 1];
    if (i == xp[low[i] + 1]) low[i]++;
  }
  while (T--) {
    memset(rmq, 0, sizeof(rmq));
    scanf("%d%d", &n, &Q);
    scanf("%s", A + 1);
    for (int i = 1; i <= n; i++) {
      a[i] = A[i] - 'a' + 1;
    }
    work();
    root[0] = new_node();
    for (int i = 1; i <= n; i++) {
      root[i] = new_node();
      insert(root[i - 1], root[i], 1, n, SA[i]);
    }
    //    for(int i=1;i<=n;i++) cout<<rnk[i]<<' ';
    //    cout<<endl;
    for (int i = 1; i <= n; i++) {
      rmq[0][i] = hi[i];
      //    cout<<rmq[0][i]<<' ';
    }
    //    cout<<endl;
    for (int i = 1; i <= 19; i++) {
      for (int j = 1; j <= n; j++) {
        rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + xp[i - 1]]);
      }
    }
    for (int i = 1; i <= Q; i++) {
      int l, r, k, ll, rr;
      scanf("%d%d%d", &l, &r, &k);
      if (hi[rnk[l]] < r - l + 1)
        ll = rnk[l];
      else {
        int L = 1, R = rnk[l] - 1, mid;
        while (L <= R) {
          mid = (L + R) >> 1;
          if (get_min(mid + 1, rnk[l]) >= r - l + 1) {
            ll = mid;
            R = mid - 1;
          } else
            L = mid + 1;
        }
      }
      if (hi[rnk[l] + 1] < r - l + 1)
        rr = rnk[l];
      else {
        int L = rnk[l] + 1, R = n, mid;
        while (L <= R) {
          mid = (L + R) >> 1;
          if (get_min(rnk[l] + 1, mid) >= r - l + 1) {
            rr = mid;
            L = mid + 1;
          } else
            R = mid - 1;
        }
      }
      if (rr - ll + 1 < k)
        printf("-1\n");
      else {
        printf("%d\n", get_rank(root[ll - 1], root[rr], 1, n, k));
      }
    }
  }
  return 0;
}
/*
1
9 4
baabddcbc
4 5 1
1 7 1
1 9 3
1 8 2

*/