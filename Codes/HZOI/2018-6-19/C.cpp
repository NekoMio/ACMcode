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
const int MAXN = 200005;
int a[MAXN];
vector<int> vc[MAXN];
struct data {
  int x, val;
};
vector<data> LL[MAXN];
void Trans(int x, int c) {
  for (int i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      vc[i].push_back(c);
      if (i * i != x) vc[x / i].push_back(c);
    }
  }
}
void Add(int l, int r, int c) {
  LL[l].push_back((data){r, c});
}
struct Node {
  Node *ch[2];
  int Max, Min, tag, l, r;
  long long Sum;
  Node(int _l, int _r) {
    ch[0] = ch[1] = NULL;
    Sum = Min = 0;
    l = _l, r = _r;
  }
  void Pushup() {
    Sum = ch[0]->Sum + ch[1]->Sum;
    Max = max(ch[0]->Max, ch[1]->Max);
    Min = min(ch[0]->Min, ch[1]->Min);
  }
  void Pushtag(int c) {
    Min = c;
    Max = c;
    tag = c;
    Sum = 1ll * c * (r - l + 1);
  }
  void Pushdown() {
    if (tag) {
      ch[0]->Pushtag(tag);
      ch[1]->Pushtag(tag);
      tag = 0;
    }
  }
}*root;
void Build(Node *&rt, int l, int r) {
  rt = new Node(l, r);
  if (l == r) return ;
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
}
void Update(Node *rt, int L, int R, int c, int l, int r) {
  if (L > R || rt->Min >= c) return;
  if (L <= l && R >= r && rt->Max < c) {
    rt->Pushtag(c);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Update(rt->ch[0], L, R, c, l, mid);
  if (R > mid) Update(rt->ch[1], L, R, c, mid + 1, r);
  rt->Pushup();
}
long long Query(Node *rt, int L, int R, int l, int r) {
  if (L <= l && R >= r)
    return rt->Sum;
  int mid = l + r >> 1;
  long long ans = 0;
  rt->Pushdown();
  if (L <= mid) ans += Query(rt->ch[0], L, R, l, mid);
  if (R > mid) ans += Query(rt->ch[1], L, R, mid + 1, r);
  rt->Pushup();
  return ans;
}
int main() {
  int n = read();
  int Mx = 0;
  for (int i = 1; i <= n; ++i) a[i] = read(), Mx = max(Mx, a[i]);
  for (int i = 1; i <= n; ++i)
    Trans(a[i], i);
  for (int i = 1; i <= Mx; ++i) {
    int k = vc[i].size();
    if (k >= 2) {
      Add(vc[i][0] + 1, vc[i][k - 1] - 1, i);
      Add(vc[i][1] + 1, n, i);
      Add(1, vc[i][k - 2] - 1, i);
    }
  }
  Build(root, 1, n);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto x : LL[i]) {
      // fprintf (stderr, "%d %d %d\n", i, x.x, x.val);
      Update(root, i, x.x, x.val, 1, n);
    }
    ans = ans + Query(root, i, n, 1, n);
  }
  printf ("%lld\n", ans);
}
