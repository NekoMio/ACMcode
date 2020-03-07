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
const int MAXN =  1e5 + 5;
struct data {
  int x, r, q;
}a[MAXN];
int r[MAXN];
struct Node {
  Node *ch[2];
  int size;
  Node() {
    size = 0;
    ch[0] = ch[1] = NULL;
  }
  void* operator new(size_t);
}*root[MAXN], *C, *mempool;
void *Node::operator new(size_t) {
  if (C == mempool) {
    C = new Node[1 << 15];
    mempool = C + (1 << 15);
  }
  return C++;
}
void insert(Node *&rt, int l, int r, int x) {
  if (rt == NULL) rt = new Node();
  rt->size++;
  if (l == r) return;
  int mid = l + r >> 1; 
  if (x <= mid) insert(rt->ch[0], l, mid, x);
  else insert(rt->ch[1], mid + 1, r, x);
}
int Query(Node *rt, int l, int r, int L, int R) {
  if (rt == NULL) return 0;
  if (L <= l && R >= r) return rt->size;
  int mid = l + r >> 1;
  int ans = 0;
  if (L <= mid) ans += Query(rt->ch[0], l, mid, L, R);
  if (R > mid) ans += Query(rt->ch[1], mid + 1, r, L, R);
  return ans;
}
int N = 1e9;
int Hash[MAXN];
int main() {
  int n = read(), k = read();
  for (int i = 1; i <= n; i++) {
    a[i].x = read(), a[i].r = read(), a[i].q = read();
    Hash[i] = a[i].q;
  }
  int cnt = 0;
  sort(Hash + 1, Hash + n + 1);
  cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
  sort(a + 1, a + n + 1, [](const data &c, const data &d) {
    return c.r > d.r;
  });
  for (int i = 1; i <= n; i++) {
    a[i].q = lower_bound(Hash + 1, Hash + cnt + 1, a[i].q) - Hash;
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = a[i].q; j > 0 && Hash[a[i].q] - Hash[j] <= k; j--) {
      ans += Query(root[j], 1, N, a[i].x - a[i].r, a[i].x + a[i].r);
    }
    for (int j = a[i].q + 1; j <= cnt && Hash[j] - Hash[a[i].q] <= k; j++) {
      ans += Query(root[j], 1, N, a[i].x - a[i].r, a[i].x + a[i].r);
    }
    insert(root[a[i].q], 1, N, a[i].x);
  }
  printf ("%lld\n", ans);
}