#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 50005
using namespace std;
int TT, n, C[N], D[N], M[N], P[N], e[N], R[N], E[N];
struct no {
  int left, right, mid;
  long long mn, lazy;
  int bh2, bh;
  long long mn2, lazy2;
} node[N * 4];
void build(int left, int right, int x, int op) {
  node[x].left = left, node[x].right = right;
  node[x].lazy = node[x].lazy2 = 0;
  node[x].mn = node[x].mn2 = 0;
  if (left == right) {
    if (!op)
      node[x].mn = C[left];
    else
      node[x].mn = e[left], node[x].bh = left, node[x].mn2 = M[left],
      node[x].bh2 = left;
    return;
  }
  int mid = (left + right) >> 1;
  node[x].mid = mid;
  build(left, mid, x << 1, op);
  build(mid + 1, right, x << 1 | 1, op);
  if (node[x << 1].mn < node[x << 1 | 1].mn)
    node[x].mn = node[x << 1].mn, node[x].bh = node[x << 1].bh;
  else
    node[x].mn = node[x << 1 | 1].mn, node[x].bh = node[x << 1 | 1].bh;
  if (op) {
    if (node[x << 1].mn2 < node[x << 1 | 1].mn2)
      node[x].mn2 = node[x << 1].mn2, node[x].bh2 = node[x << 1].bh2;
    else
      node[x].mn2 = node[x << 1 | 1].mn2, node[x].bh2 = node[x << 1 | 1].bh2;
  }
}
void push_down(int x) {
  if (node[x].lazy) {
    node[x << 1].lazy += node[x].lazy;
    node[x << 1].mn += node[x].lazy;
    node[x << 1 | 1].lazy += node[x].lazy;
    node[x << 1 | 1].mn += node[x].lazy;
    node[x].lazy = 0;
  }
}
long long an3, an4;
long long get_mn(int left, int right, int x) {
  if (right < left) return 1e9;
  if (node[x].left == left && node[x].right == right) {
    if (node[x].mn < an3) an3 = node[x].mn, an4 = node[x].bh;
    if (node[x].mn == an3) an4 = max(an4, 1ll * node[x].bh);
    return node[x].mn;
  }
  push_down(x);
  int mid = node[x].mid;
  if (left > mid)
    return get_mn(left, right, x << 1 | 1);
  else if (right <= mid)
    return get_mn(left, right, x << 1);
  else
    return min(get_mn(left, mid, x << 1), get_mn(mid + 1, right, x << 1 | 1));
}
void add(int left, int right, int x, long long da) {
  if (node[x].left == left && node[x].right == right) {
    node[x].mn += da;
    node[x].lazy += da;
    return;
  }
  push_down(x);
  int mid = node[x].mid;
  if (left > mid)
    add(left, right, x << 1 | 1, da);
  else if (right <= mid)
    add(left, right, x << 1, da);
  else
    add(left, mid, x << 1, da), add(mid + 1, right, x << 1 | 1, da);
  if (node[x << 1].mn < node[x << 1 | 1].mn)
    node[x].mn = node[x << 1].mn, node[x].bh = node[x << 1].bh;
  else
    node[x].mn = node[x << 1 | 1].mn, node[x].bh = node[x << 1 | 1].bh;
}
void push_down2(int x) {
  if (node[x].lazy2) {
    node[x << 1].mn2 += node[x].lazy2;
    node[x << 1].lazy2 += node[x].lazy2;
    node[x << 1 | 1].mn2 += node[x].lazy2;
    node[x << 1 | 1].lazy2 += node[x].lazy2;
    node[x].lazy2 = 0;
  }
}
void ch(int left, int right, int x, long long da) {
  if (node[x].left == left && node[x].right == right) {
    node[x].mn2 += da;
    node[x].lazy2 += da;
    return;
  }
  push_down2(x);
  int mid = node[x].mid;
  if (left > mid)
    ch(left, right, x << 1 | 1, da);
  else if (right <= mid)
    ch(left, right, x << 1, da);
  else
    ch(left, mid, x << 1, da), ch(mid + 1, right, x << 1 | 1, da);
  if (node[x << 1].mn2 < node[x << 1 | 1].mn2)
    node[x].mn2 = node[x << 1].mn2, node[x].bh2 = node[x << 1].bh2;
  else
    node[x].mn2 = node[x << 1 | 1].mn2, node[x].bh2 = node[x << 1 | 1].bh2;
}
long long an1, an2;
void work(int left, int right, int x) {
  if (node[x].left == node[x].right) {
    if (node[x].mn2 < an1) an1 = node[x].mn2, an2 = node[x].bh2;
    return;
  }
  push_down2(x);
  int mid = node[x].mid;
  if (left > mid)
    work(left, right, x << 1 | 1);
  else if (right <= mid)
    work(left, right, x << 1);
  else
    work(left, mid, x << 1), work(mid + 1, right, x << 1 | 1);
}
int main() {
  //	freopen("test.in","r",stdin);
  //	freopen("1.out","w",stdout);
  scanf("%d", &TT);
  while (TT--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d%d", &C[i], &D[i], &M[i], &P[i]);
    }
    for (int i = 1; i < n; i++) {
      scanf("%d%d%d", &e[i], &R[i], &E[i]);
    }
    long long sm = 0;
    for (int i = 1; i <= n; i++) {
      sm += P[i];
      sm -= D[i];
      if (sm < 0) {
        printf("-1\n");
        break;
      }
      sm = min(sm, 1ll * e[i]);
    }

    if (sm < 0) continue;
    build(1, n, 1, 0);
    for (int i = 1; i <= n; i++) {
      if (i == 1)
        M[i] += C[i];
      else
        M[i] += get_mn(1, i, 1);
      add(1, i, 1, R[i]);
    }
    build(1, n, 1, 1);
    long long ans = 0;
    int L = 1;
    for (int i = 1; i <= n; i++) {
      while (D[i]) {
        an1 = 1e18, an2 = 0;
        an3 = 1e18, an4 = 0;
        work(L, i, 1);
        long long tmp = get_mn(an2, i - 1, 1);  // buy com fr an2 lowest fr an4
        long long tmp2 = min(tmp, 1ll * min(P[an2], D[i]));
        //	cout<<i<<' '<<an2<<' '<<an4<<' '<<tmp2<<' '<<tmp<<' '<<L<<endl;
        D[i] -= tmp2;
        P[an2] -= tmp2;
        if (!P[an2]) ch(an2, an2, 1, 2e8);
        ans += tmp2 * an1;
        if (an2 != i) {
          add(an2, i - 1, 1, -tmp2);
          if (tmp == tmp2) {
            //	cout<<"dasdasdads"<<endl;
            L = an4 + 1;
          }
        }
      }
      ch(1, i, 1, E[i]);
      if (!e[i]) L = i + 1;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
/*
3
2
10 5 3 6
15 7 2 8
2 3 2
2
10 5 3 6
15 7 2 8
2 3 2
2
10 5 3 6
15 7 2 8
2 3 2
*/