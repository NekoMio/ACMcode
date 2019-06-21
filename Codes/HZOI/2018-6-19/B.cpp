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
const int MAXN = 1e6 + 5;
int Hash[MAXN], cnt;
struct data {
  int l, a, r;
  bool operator < (const data &c) const {
    return l < c.l;
  } 
}v[MAXN];
struct Node {
  Node *ch[2];
  int Max, add;
  Node() {
    ch[0] = ch[1] = NULL;
    Max = add = 0;
  }
  void Pushup() {
    Max = max(ch[0]->Max, ch[1]->Max);
  }
  void Pushadd(int c) {
    Max += c;
    add += c;
  }
  void Pushdown() {
    if (add) {
      ch[0]->Pushadd(add);
      ch[1]->Pushadd(add);
      add = 0;
    }
  }
}*root;
void Build(Node *&rt, int l, int r) {
  if (rt == NULL) rt = new Node();
  if (l == r) return;
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
  rt->Pushup();
}
void Update(Node *rt, int L, int R, int c, int l, int r) {
  if (L <= l && R >= r) {
    rt->Pushadd(c);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Update(rt->ch[0], L, R, c, l, mid);
  if (R > mid) Update(rt->ch[1], L, R, c, mid + 1, r);
  rt->Pushup();
}
int Query(Node *rt, int L, int R, int l, int r) {
  if (L <= l && R >= r)
    return rt->Max;
  int mid = l + r >> 1;
  int ans = 0;
  rt->Pushdown();
  if (L <= mid) ans = max(ans, Query(rt->ch[0], L, R, l, mid));
  if (R > mid) ans = max(ans, Query(rt->ch[1], L, R, mid + 1, r));
  rt->Pushup();
  return ans;
}
vector<int> vc[MAXN], LL[MAXN];
int main() {
  int n = read();
  for (int i = 1; i <= n; ++i) {
    v[i].l = read(), v[i].a = read(), v[i].r = read();
    Hash[++cnt] = v[i].l, Hash[++cnt] = v[i].a, Hash[++cnt] = v[i].r;
  }
  sort(Hash + 1, Hash + cnt + 1);
  cnt = unique(Hash + 1, Hash + cnt + 1) - Hash - 1;
  sort(v + 1, v + n + 1);
  for (int i = 1; i <= n; ++i) {
    v[i].l = lower_bound(Hash + 1, Hash + cnt + 1, v[i].l) - Hash;
    v[i].a = lower_bound(Hash + 1, Hash + cnt + 1, v[i].a) - Hash;
    v[i].r = lower_bound(Hash + 1, Hash + cnt + 1, v[i].r) - Hash;
    vc[v[i].a].push_back(i);
    LL[v[i].l].push_back(i);
  }
  Build(root, 1, cnt);
  int ans = 0;
  // fprintf (stderr, "\n");
  for (int i = 1; i <= cnt; ++i) {
    // fprintf (stderr, "%d\n", i);
    for (auto x : LL[i])
    {
      // fprintf (stderr, "%d %d %d\n", v[x].a, v[x].r, 1);
      Update(root, v[x].a, v[x].r, 1, 1, cnt);
      ans = max(ans, Query(root, v[x].a, v[x].r, 1, cnt));
    }
    for (auto x : vc[i])
    {
      // fprintf (stderr, "%d %d %d\n", v[x].a, v[x].r, -1);
      Update(root, v[x].a, v[x].r, -1, 1, cnt);
    }
  }
  printf ("%d\n", ans);
}
