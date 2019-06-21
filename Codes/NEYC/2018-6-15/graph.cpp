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
const int MAXN = 100005;
struct Node {
  Node *ch[2];
  long long Sum;
  Node() {
    ch[0] = ch[1] = NULL;
    Sum = 0;
  }
  void Pushup() {
    Sum = 0;
    if (ch[0]) Sum += ch[0]->Sum;
    if (ch[1]) Sum += ch[1]->Sum;
  }
}*root1, *root2, *Sum1, *Sum2;
void Update(Node *&rt, int x, int c, int l = 0, int r = 1e8) {
  if (rt == NULL) rt = new Node();
  if (l == r) {
    rt->Sum += c;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) Update(rt->ch[0], x, c, l, mid);
  else Update(rt->ch[1], x, c, mid + 1, r);
  rt->Pushup();
}
long long Query(Node *rt, int L, int R, int l = 0, int r = 1e8) {
  if (rt == NULL) return 0;
  if (L <= l && R >= r)
    return rt->Sum;
  int mid = l + r >> 1;
  long long ans = 0;
  if (L <= mid) ans += Query(rt->ch[0], L, R, l, mid);
  if (R > mid) ans += Query(rt->ch[1], L, R, mid + 1, r);
  return ans;
}
int a[MAXN], b[MAXN];
int main() {
  // freopen("ex_graph3.in", "r", stdin);
  // freopen("graph.out", "w", stdout);
  int n = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    Update(root1, a[i], 1);
    Update(Sum1, a[i], a[i]);
  }
  long long Ans = 0;
  for (int i = 1; i <= n; ++i) {
    b[i] = read();
    Update(root2, b[i], 1);
    Update(Sum2, b[i], b[i]);
    Ans += Query(Sum1, 0, b[i]) + (n - Query(root1, 0, b[i])) * b[i];
  }
  printf ("%lld\n", Ans);
  int m = read();
  while (m--) {
    int tp = read(), i = read(), x = read();
    if (tp == 1) {
      Ans -= Query(Sum1, 0, b[i]) + (n - Query(root1, 0, b[i])) * b[i];
      Update(root2, b[i], -1);
      Update(Sum2, b[i], -b[i]);
      b[i] = x;
      Update(root2, b[i], 1);
      Update(Sum2, b[i], b[i]);
      Ans += Query(Sum1, 0, b[i]) + (n - Query(root1, 0, b[i])) * b[i];
      printf ("%lld\n", Ans);
    } else {
      Ans -= Query(Sum2, 0, a[i]) + (n - Query(root2, 0, a[i])) * a[i];
      Update(root1, a[i], -1);
      Update(Sum1, a[i], -a[i]);
      a[i] = x;
      Update(root1, a[i], 1);
      Update(Sum1, a[i], a[i]);
      Ans += Query(Sum2, 0, a[i]) + (n - Query(root2, 0, a[i])) * a[i];
      printf ("%lld\n", Ans);
    }
  }
  // printf ("%.3f", (double) clock() / CLOCKS_PER_SEC);
}