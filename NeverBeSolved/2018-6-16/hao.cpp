#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
const int MAXN = 100005;
struct Node {
  Node *ch[2];
  int tag, Min;
  Node() {
    ch[0] = ch[1] = NULL;
    tag = -1;
    Min = 0;
  }
  void Pushup() {
    Min = 0x3f3f3f3f;
    if (ch[0]) Min = min(ch[0]->Min, Min);
    if (ch[1]) Min = min(ch[1]->Min, Min);
  }
  void Pushtag(int c) {
    tag = c;
    Min = c;
  }
  void Pushdown() {
    if (tag != -1) {
      if (ch[0]) ch[0]->Pushtag(tag);
      if (ch[1]) ch[1]->Pushtag(tag);
      tag = -1;
    }
  }
}*root;
int a[MAXN], b[MAXN];
void Build(Node *&rt, int l, int r) {
  rt = new Node();
  if (l == r) {
    rt->Min = b[l];
    return;
  }
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
  rt->Pushup();
}
int Query(Node *rt, int x, int l, int r) {
  if (l == r) {
    return rt->Min;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  int ans = 0;
  if (x <= mid) ans = Query(rt->ch[0], x, l, mid);
  else ans = Query(rt->ch[1], x, mid + 1, r);
  rt->Pushup();
  return ans;
}
int find(Node *rt, int x, int l, int r) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (rt->ch[1]->Min <= x)
}
void Update(Node *rt, int L, int R, int c, int l, int r) {
  if (L <= l && R >= r) {
    rt->Pushtag(c);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Update(rt->ch[0], L, R, c, l, mid);
  if (R > mid) Update(rt->ch[1], L, R, c, mid + 1, r);
  rt->Pushup();
}
bool vis[MAXN];
int lst[MAXN], nxt[MAXN];
struct Data {
  int l, r, val;
}D[5 * MAXN];
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    nxt[i] = lst[a[i]];
    lst[a[i]] = i;
    if (nxt[i] == 0) nxt[i] = n + 1;
  }
  for (int i = 1; i <= n; ++i) {
    vis[a[i]] = 1;
    int t = b[i - 1];
    while (vis[t]) t++;
    b[i] = t;
  }
  Build(root, 1, n);
  for (int i = 1; i <= n; ++i) {
    int x = nxt[i] - 1;
    while (1) {
      int t = Query(root, x, 1, n);
      if (t <= a[i]) break;
      int num = find(t);
      D[++N].l = i;
      D[N].r = num;
      D[N].val = t;
      Update(root, num, x, a[i], 1, n);
      x = num - 1;
      if (x < i) break;
    }
  }
  for (int i = 1; i <= N; ++i) {
    printf ("%d %d %d\n", D[i].l, D[i].r, D[i].val);
  }
}