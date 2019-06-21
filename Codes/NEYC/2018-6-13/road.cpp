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
struct Node {
  Node *ch[2], *f;
  int s, val, tag;
  Node() {
    ch[0] = ch[1] = f = NULL;
    s = 1, val = 0, tag = 0;
  }
  void Pushtag(int c) {
    tag = c;
    val = c;
  }
  void Pushdown();
  void Pushup() {
    s = ch[0]->s + ch[1]->s + 1;
  }
}*Q[MAXN], *null;
void Node::Pushdown() {
  if (tag != 0) {
    if (ch[0] != null) ch[0]->Pushtag(tag);
    if (ch[1] != null) ch[1]->Pushtag(tag); 
    tag = 0;
  }
}
Node *NewNode() {
  Node *o = new Node();
  o->ch[0] = o->ch[1] = o->f = null;
  return o;
}
inline int son(Node *rt) {
  return rt->f->ch[1] == rt;
}
inline int IsRoot(Node *rt) {
  return rt->f->ch[0] != rt && rt->f->ch[1] != rt;
}
void rotate(Node *rt) {
  if (IsRoot(rt)) return;
  Node *fa = rt->f, *Grand = fa->f;
  fa->Pushdown(), rt->Pushdown();
  int tmp = IsRoot(fa);
  int k = son(rt), kk = son(fa);
  fa->ch[k] = rt->ch[k ^ 1];
  if (rt->ch[k ^ 1] != null) rt->ch[k ^ 1]->f = fa;
  rt->ch[k ^ 1] = fa, fa->f = rt, rt->f = Grand;
  if (!tmp) Grand->ch[kk] = rt;
  fa->Pushup(), rt->Pushup();
}
void Clear(Node *rt) {
  if (!IsRoot(rt)) Clear(rt->f);
  rt->Pushdown(); 
}
void Splay(Node *rt) {
  for (Clear(rt); !IsRoot(rt); rotate(rt))
    if (!IsRoot(rt->f))
      rotate(son(rt) == son(rt->f) ? rt->f : rt);
}
Node *Access(Node *rt) {
  Node *ret = null;
  for (Node *pre = null; rt != null; pre = rt, rt = rt->f) {
    Splay(rt);
    // rt->Pushdown();
    rt->ch[1] = pre;
    rt->Pushup();
    ret = rt;
  }
  return ret;
}
int C[MAXN], Hash[MAXN], cnt;
int Color[MAXN], Co;
long long Sum[MAXN];
#define lowbit(_) ((_) & (-_))
void Update(int x, int c) {
  x++;
  for (int i = x; i <= cnt + 1; i += lowbit(i)) {
    if (Color[i] != Co) Sum[i] = 0;
    Color[i] = Co;
    Sum[i] += c;
  }
}
long long Query(int x) {
  long long ans = 0;
  x++;
  for (int i = x; i >= 1; i -= lowbit(i)) {
    if (Color[i] == Co) ans += Sum[i];
  }
  return ans;
}
int stC[MAXN], stS[MAXN], top;
long long Query(Node *rt) {
  top = 0;
  for (Node *pre = null; rt != null; pre = rt, rt = rt->f) {
    Splay(rt);
    // rt->Pushdown();
    rt->ch[1] = pre;
    rt->Pushup();
    stC[++top] = rt->val;
    stS[top] = rt->s;
  }
  long long ans = 0;
  Co++;
  for (int i = top; i >= 1; --i) stS[i] -= stS[i - 1];
  for (int i = 1; i <= top; ++i) {
    ans += Query(stC[i] - 1) * stS[i];
    Update(stC[i], stS[i]);
  }
  return ans;
}
int main() {
  // freopen ("road3.in", "r", stdin);
  // freopen ("road.out", "w", stdout);
  null = new Node();
  null->ch[0] = null->ch[1] = null->f = null;
  null->s = 0, null->val = 0;
  int n = read();
  for (int i = 1; i <= n; ++i) {
    C[i] = read();
    Hash[i] = C[i];
  }
  sort(Hash + 1, Hash + n + 1);
  cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
  for (int i = 1; i <= n; ++i) {
    C[i] = lower_bound(Hash + 1, Hash + cnt + 1, C[i]) - Hash;
  }
  for (int i = 1; i <= n; ++i) {
    Q[i] = NewNode();
    Q[i]->val = C[i];
    // printf ("%d\n", C[i]);
  }
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    printf ("%lld\n", Query(Q[a]));
    // Splay(Q[a]);
    Q[b]->f = Q[a];
    Access(Q[b])->Pushtag(C[b]);
    // Splay(Q[b]);
    // Q[b]->Pushtag(C[b]);
  }
}