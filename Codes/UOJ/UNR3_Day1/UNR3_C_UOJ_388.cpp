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
const int MOD = 998244353;
const int MAXN = 1e5 + 5;
vector<int> vc[MAXN];
struct edge {
  int END, next, v;
}v[MAXN << 1];
int first[MAXN], p, a[MAXN], n, m;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].v = c;
  first[a] = p++;
}
int size[MAXN], son[MAXN], W[MAXN];
void DFS1(int rt, int fa) {
  size[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS1(v[i].END, rt);
    size[rt] += size[v[i].END];
    if (size[son[rt]] < size[v[i].END]) {
      son[rt] = v[i].END;
      W[rt] = v[i].v;
    }
  }
}
struct Node {
  Node *ch[2];
  int cnt[2][2], Sum;
  Node() {
    ch[0] = ch[1] = NULL;
    cnt[0][0] = cnt[1][0] = 0;
    cnt[1][1] = cnt[0][1] = 0;
    Sum = 0;
  }
  void Pushup() {
    if (ch[0]->Sum & 1) {
      cnt[0][0] = ch[0]->cnt[0][0] + ch[1]->cnt[0][1];
      cnt[1][0] = ch[0]->cnt[1][0] + ch[1]->cnt[1][1];
      cnt[0][1] = ch[0]->cnt[0][1] + ch[1]->cnt[0][0];
      cnt[1][1] = ch[0]->cnt[1][1] + ch[1]->cnt[1][0];
    } else {
      cnt[0][0] = ch[0]->cnt[0][0] + ch[1]->cnt[0][0];
      cnt[1][0] = ch[0]->cnt[1][0] + ch[1]->cnt[1][0];
      cnt[0][1] = ch[0]->cnt[0][1] + ch[1]->cnt[0][1];
      cnt[1][1] = ch[0]->cnt[1][1] + ch[1]->cnt[1][1];
    }
    Sum = ch[0]->Sum + ch[1]->Sum;
  }
} * root;
void Build(Node *&rt, int l, int r) {
  rt = new Node();
  if (l == r) {
    if (l & 1) rt->cnt[1][0] = 1;
    else rt->cnt[0][0] = 1;
    return;
  }
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
  rt->Pushup();
}
void Update(Node *rt, int x, int l, int r) {
  if (l == r) {
    if (l & 1) rt->cnt[1][0] ^= 1, rt->cnt[1][1] ^= 1;
    else rt->cnt[0][0] ^= 1, rt->cnt[0][1] ^= 1;
    rt->Sum ^= 1;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) Update(rt->ch[0], x, l, mid);
  else Update(rt->ch[1], x, mid + 1, r);
  rt->Pushup();
}
void RDFS(int rt, int fa) {
  for (auto x : vc[rt]) Update(root, x, 1, m);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    RDFS(v[i].END, rt);
  }
}
int Ans = 0;
int Calc() {
  return (1ll * root->cnt[1][0] * root->cnt[1][1] + 1ll * root->cnt[0][1] * (root->cnt[0][0] + 1)) % MOD;
}
void DFS(int rt, int fa, int w) {
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa || v[i].END == son[rt]) continue;
    DFS(v[i].END, rt, v[i].v);
    RDFS(v[i].END, rt);
  }
  if (son[rt]) {
    DFS(son[rt], rt, W[rt]);
    for (int i = first[rt]; i != -1; i = v[i].next) {
      if (v[i].END == fa || v[i].END == son[rt]) continue;
      RDFS(v[i].END, rt);
    }
  }
  for (auto x : vc[rt])
    Update(root, x, 1, m);
  Ans = (Ans + 1ll * Calc() * w % MOD) % MOD;
  cerr << rt << " " << Calc() << endl;
}
int main() {
  memset (first, -1, sizeof (first));
  n = read(), m = read();
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read(), c = read();
    add(a, b, c);
    add(b, a, c);
  }
  for (int i = 1; i <= m; ++i) {
    a[i] = read();
    vc[a[i]].push_back(i);
  }
  Build(root, 1, m);
  DFS1(1, 0);
  DFS(1, 0, 0);
  printf ("%d\n", Ans);
}
