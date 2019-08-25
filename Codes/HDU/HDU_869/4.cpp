#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct Treap {
  struct Node {
    int id, val;
    int key, size;
    Node *ch[2];
    Node() {}
#define _size(_) ((_) ? (_)->size : 0)
    void Pushup() { size = _size(ch[0]) + _size(ch[1]) + 1; }
    void reset(int _id, int x) {
      id = _id, val = x;
      ch[0] = ch[1] = NULL;
      key = rand(), size = 1;
    }
  } * root, *C;
  queue<Node *> Q;
  Node *NewNode(int id, int x) {
    if (C == NULL) {
      C = new Node[50010];
    }
    if (!Q.empty()) {
      Node *rt = Q.front();
      Q.pop();
      rt->reset(id, x);
      return rt;
    }
    C->reset(id, x);
    return C++;
  }
  void Del(Node *&rt) {
    Q.push(rt);
    rt = NULL;
  }
  typedef pair<Node *, Node *> DNode;
  Node *Merge(Node *A, Node *B) {
    if (!A) return B;
    if (!B) return A;
    if (A->key < B->key) {
      A->ch[1] = Merge(A->ch[1], B);
      A->Pushup();
      return A;
    } else {
      B->ch[0] = Merge(A, B->ch[0]);
      B->Pushup();
      return B;
    }
  }
  DNode Split(Node *rt, int k) {
    if (!rt) return DNode(NULL, NULL);
    DNode o;
    if (_size(rt->ch[0]) >= k) {
      o = Split(rt->ch[0], k);
      rt->ch[0] = o.second;
      rt->Pushup();
      o.second = rt;
    } else {
      o = Split(rt->ch[1], k - _size(rt->ch[0]) - 1);
      rt->ch[1] = o.first;
      rt->Pushup();
      o.first = rt;
    }
    return o;
  }
  Treap() { root = NULL; }
  int rank(Node *rt, int x) {
    if (!rt) return 0;
    return x <= rt->val ? rank(rt->ch[0], x)
                        : rank(rt->ch[1], x) + _size(rt->ch[0]) + 1;
  }
  void insert(int id, int x) {
    int k = rank(root, x);
    DNode y = Split(root, k);
    Node *n = NewNode(id, x);
    root = Merge(Merge(y.first, n), y.second);
  }
  pair<int, int> delmin() {
    DNode x = Split(root, 1);
    pair<int, int> ret(x.first->id, x.first->val);
    root = x.second;
    Del(x.first);
    return ret;
  }
  int Qmax(Node *rt) {
    if (rt->ch[1] != NULL) return Qmax(rt->ch[1]);
    return rt->val;
  }
  int delmax() {
    DNode x = Split(root, root->size - 1);
    Del(x.second);
    root = x.first;
    return Qmax(root);
  }
  inline int size() { return _size(root); }
  void DFS(Node *&rt) {
    if (rt == NULL) return;
    DFS(rt->ch[0]);
    DFS(rt->ch[1]);
    Del(rt);
  }
  void reset() { DFS(root); }
};

struct xl {
  long long o, p, q;
};

long long a, b, c, d, e, f, g, i, m, n, h1, h2, h3, r, s;
long long xa[200000] = {0}, xb[200000] = {0}, xc[200000] = {0};
xl w[200000];
long long za[200000] = {0}, zb[200000] = {0};
Treap z;
pair<int, int> zc;

bool sx(xl j, xl k) { return j.o > k.o; }

void ma(long long &j, long long k) {
  if (j < k) j = k;
}

int main() {
  scanf("%lld", &a);
  for (n = 1; n <= a; n++) {
    z.reset();
    scanf("%lld%lld%lld", &b, &c, &d);
    for (i = 1; i <= b; i++) {
      xa[i] = xb[i] = xc[i] = 0;
    }
    for (i = 1; i <= c; i++) {
      scanf("%lld%lld%lld", &w[i].q, &w[i].p, &w[i].o);
    }
    sort(w + 1, w + c + 1, sx);
    for (i = 1; i <= c; i++) {
      e = w[i].q;
      w[i].q = xb[e];
      xb[e] = i;
    }
    e = 0;
    f = 0;
    g = 0;
    w[0].q = 0;
    for (i = 1; i <= d; i++) {
      scanf("%lld", &za[i]);
      ma(e, za[i]);
    }
    for (i = 1; (i <= c) && (i <= e); i++) {
      z.insert(w[i].p, w[i].o);
      ma(g, w[i].o);
      f++;
    }
    for (i = 1; i <= e; i++) {
      zc = z.delmin();
      f--;
      // printf("%lld %lld %lld\n",i,zc.first,zc.second);
      zb[i] = zc.second;
      r = xb[zc.first];
      s = w[r].p;
      while (r != 0) {
        // printf("%lld %lld\n",s,w[r].o);
        if (f + i < e) {
          z.insert(s, zc.second + w[r].o);
          ma(g, zc.second + w[r].o);
          f++;
        } else {
          if (zc.second + w[r].o < g) {
            z.insert(s, zc.second + w[r].o);
            g = z.delmax();
          } else
            r = 0;
        }
        r = w[r].q;
        s = w[r].p;
      }
    }
    for (i = 1; i <= d; i++) {
      printf("%lld\n", zb[za[i]]);
    }
  }
  return 0;
}