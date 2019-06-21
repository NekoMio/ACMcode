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
int n, S[MAXN], Min[MAXN], lst;
long long ans[2];
struct Treap {
  struct Node {
    Node *ch[2];
    int s, key, val;
    Node(int x) {
      s = 1, key = rand(), val = x;
      ch[0] = ch[1] = NULL;
    }
#define Size(_) ((_) ? (_)->s : 0)
    void Pushup() { s = Size(ch[0]) + Size(ch[1]) + 1; }
  } * root;
  Treap() { root = NULL; }
  Node *Merge(Node *A, Node *B) {
    if (!A) return B;
    if (!B) return A;
    if (A->key > B->key) {
      A->ch[1] = Merge(A->ch[1], B);
      A->Pushup();
      return A;
    } else {
      B->ch[0] = Merge(A, B->ch[0]);
      B->Pushup();
      return B;
    }
  }
  typedef pair<Node *, Node *> DNode;
  DNode Split(Node *rt, int k) {
    if (!rt) return DNode(NULL, NULL);
    DNode o;
    if (Size(rt->ch[0]) >= k) {
      o = Split(rt->ch[0], k);
      rt->ch[0] = o.second;
      rt->Pushup();
      o.second = rt;
    } else {
      o = Split(rt->ch[1], k - Size(rt->ch[0]) - 1);
      rt->ch[1] = o.first;
      rt->Pushup();
      o.first = rt;
    }
    return o;
  }
  int Rank(Node *rt, int x) {
    if (!rt) return 0;
    return rt->val >= x ? Rank(rt->ch[0], x)
                        : Rank(rt->ch[1], x) + Size(rt->ch[0]) + 1;
  }
  int Rk(Node *rt, int x) {
    if (!rt) return 0;
    return S[rt->val] >= x ? Rk(rt->ch[0], x)
                           : Rk(rt->ch[1], x) + Size(rt->ch[0]) + 1;
  }
  int kth(int k) {
    DNode x = Split(root, k - 1);
    DNode y = Split(x.second, 1);
    int ans = y.first ? y.first->val : 0;
    root = Merge(Merge(x.first, y.first), y.second);
    return ans;
  }
  void insert(int x) {
    int k = Rank(root, x);
    DNode o = Split(root, k);
    Node *n = new Node(x);
    root = Merge(o.first, Merge(n, o.second));
  }
  bool count(int x) { return Rank(root, x + 1) != Rank(root, x); }
  int last(int x) {
    int k = Rank(root, x);
    if (k == 0) return 1;
    DNode o = Split(root, k - 1);
    DNode y = Split(o.second, 1);
    int ans = y.first->val;
    root = Merge(o.first, Merge(y.first, y.second));
    return ans;
  }
  int end(Node *rt) {
    if (!rt) return 0;
    if (rt->ch[1]) return end(rt->ch[1]);
    return rt->val;
  }
  int begin(Node *rt) {
    if (!rt) return 0;
    if (rt->ch[0]) return begin(rt->ch[0]);
    return rt->val;
  }
  void remove(int x) {
    int k = Rank(root, x);
    DNode o = Split(root, k);
    DNode y = Split(o.second, 1);
    int t1 = end(o.first), t2 = begin(y.second);
    if (t1 == 0) t1 = 1;
    ans[t1 & 1] -= S[x];
    ans[x & 1] -= S[t2];
    ans[t1 & 1] += S[t2];
    root = Merge(o.first, y.second);
  }
  void DFS(Node *rt) {
    if (rt) {
      DFS(rt->ch[0]);
      ans[lst & 1] -= S[rt->val];
      lst = rt->val;
      ans[lst & 1] += S[rt->val];
      DFS(rt->ch[1]);
    }
  }
  int lower_bound(int x) {
    int k = Rank(root, x);
    return kth(k + 1);
  }
} rt;
bool Test(int x) {
  int t = rt.lower_bound(x);
  if (t == 0) return 1;
  if (S[t] <= S[x]) return 0;
  return 1;
}
void Init() {
  Min[n + 1] = 0x3f3f3f3f;
  for (int i = n; i >= 1; --i) Min[i] = min(Min[i + 1], S[i]);
  for (int i = 1; i <= n; ++i)
    if (S[i] < Min[i + 1]) rt.insert(i);
  ans[0] = ans[1] = 0;
  for (int i = 1; i <= n; ++i) {
    if (!rt.count(i))
      ans[i & 1] += S[i];
    else
      ans[rt.last(i) & 1] += S[i];
  }
}
int main() {
  n = read();
  for (int i = 1; i <= n; ++i) S[i] = read();
  Init();
  printf("%lld\n", ans[1]);
  int q = read();
  while (q--) {
    int a = read(), b = read();
    if (rt.count(a))
      rt.remove(a);
    else ans[a & 1] -= S[a];
    int tt = rt.Rank(rt.root, a);
    Treap::DNode r = rt.Split(rt.root, tt);
    int x1 = rt.Rk(r.first, S[a] + 1);
    int x2 = rt.Rk(r.first, S[a] - b);
    S[a] -= b;
    Treap::DNode x = rt.Split(r.first, x1);
    Treap::DNode y = rt.Split(x.first, x2);

    int tp = lst = rt.end(y.first);
    if (tp == 0) tp = lst = 1;
    rt.DFS(y.second);
    int v = rt.begin(x.second ? x.second : r.second);
    if (v) ans[lst & 1] -= S[v];

    r.first = rt.Merge(y.first, x.second);
    rt.root = rt.Merge(r.first, r.second);

    if (Test(a)) {
      ans[tp & 1] += S[a];
      rt.insert(a);
      if (v) ans[a & 1] += S[v];
    } else {
      if (v) ans[lst & 1] += S[v];
      ans[a & 1] += S[a];
    }
    printf ("%lld\n", ans[1]);
  }
}
