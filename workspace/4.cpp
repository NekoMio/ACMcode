#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct Treap {
  struct Node {
    int id, val;
    int key, size;
    Node* ch[2];
    Node(int _id = 0, int x = 0) {
      id = _id, val = x;
      ch[0] = ch[1] = NULL;
      key = rand(), size = 1;
    }
    #define _size(_) ((_)?(_)->size:0)
    void Pushup() {
      size = _size(ch[0]) + _size(ch[1]) + 1;
    }
    void reset(int _id, int x) {
      id = _id, val = x;
      ch[0] = ch[1] = NULL;
      key = rand(), size = 1;
    }
  }*root, *C;
  queue<Node*> Q;
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
    return C++;
  }
  void Del(Node *&rt) {
    Q.push(rt);
    rt = NULL;
  }
  typedef pair<Node*,Node*> DNode;
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
  Treap() {
    root = NULL;
  }
  int rank(Node *rt, int x) {
    if (!rt) return 0;
    return x <= rt->val ? rank(rt->ch[0], x) : rank(rt->ch[1], x) + _size(rt->ch[0]) + 1;
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
  inline int size() {
    return _size(root);
  }
};
int main() {

}