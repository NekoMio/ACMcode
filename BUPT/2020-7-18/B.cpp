#include <bits/stdc++.h>
using namespace std;
struct Node {
  int s, key;
  char val;
  Node *ch[2];
  Node(char _val = 0) {
    ch[0] = ch[1] = NULL;
    s = 1, val = _val, key = rand();
  }
#define size(_) ((_) ? (_)->s : 0)
  void Pushup() { s = size(ch[0]) + size(ch[1]) + 1; }
  void* operator new(size_t);
} * root, *C, *mempool;
void *Node::operator new(size_t) {
  if (C == mempool) {
    C = new Node[1 << 15];
    mempool = C + (1 << 15);
  }
  return C++;
}
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
typedef pair<Node *, Node *> DNode;
DNode Split(Node *rt, int k) {
  if (!rt) return DNode(NULL, NULL);
  DNode o;
  if (size(rt->ch[0]) >= k) {
    o = Split(rt->ch[0], k);
    rt->ch[0] = o.second;
    rt->Pushup();
    o.second = rt;
  } else {
    o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
    rt->ch[1] = o.first;
    rt->Pushup();
    o.first = rt;
  }
  return o;
}
char kth(Node *rt, int k) {
  while (rt) {
    if (size(rt->ch[0]) + 1 == k) return rt->val;
    if (size(rt->ch[0]) + 1 > k)
      rt = rt->ch[0];
    else
      k -= size(rt->ch[0]) + 1, rt = rt->ch[1];
  }
  return 0;
}
void add(char c) {
  Node *x = new Node(c);
  root = Merge(root, x);
}
const int MAXN = 2e6 + 3;
char s[MAXN];
int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; i++) add(s[i]);
  int Q;
  scanf("%d", &Q);
  char op[3];
  int pos;
  while (Q--) {
    scanf("%s%d", op, &pos);
    if (op[0] == 'A') {
      printf("%c\n", kth(root, pos));
    } else {
      if (pos > 0) {
        DNode o = Split(root, pos);
        root = Merge(o.second, o.first);
      } else {
        DNode o = Split(root, n + pos);
        root = Merge(o.second, o.first);
      }
    }
  }
}