#include <bits/stdc++.h>
using namespace std;
struct Node {
  Node *ch[2];
  int s, num, tag, val, key;
  Node(int x) {
    ch[0] = ch[1] = NULL;
    s = 1, num = 0, tag = 0, val = x, key = rand();
  }
  #define size(_) ((_) ? (_)->s : 0)
  void Pushup() {
    s = size(ch[0]) + size(ch[1]) + 1;
  }
  void Pushdown() {
    if (tag) {
      if (ch[0]) {
        ch[0]->num += tag;
        ch[0]->tag += tag;
      }
      if (ch[1]) {
        ch[1]->num += tag;
        ch[1]->tag += tag;
      }
      tag = 0;
    }
  }
}*g[100005];
Node *Merge(Node *A, Node *B) {
  if (!A) return B;
  if (!B) return A;
  A->Pushdown(), B->Pushdown();
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
typedef pair<Node*, Node*> DNode;
DNode Split(Node *rt, int k) {
  if (!rt) return DNode(NULL, NULL);
  DNode o;
  rt->Pushdown();
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
int Rank(Node *rt, int x)
{
  if (!rt)
    return 0;
  return x <= rt->val ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
}
int rev[200005];
void del(int x, int y) {
  int k = Rank(g[y], x);
  DNode o = Split(g[y], k);
  DNode t = Split(o.second, 1);
  if (t->first)
    rev[x] += t.first->num;
  // delete t.first;
  g[y] = Merge(o.first, t.second);
}
void add(int x, int y) {
  // if (in[x] != 0) {
  //   del(x, in[x]);
  // }
  if (g[y] == NULL) {
    g[y] = new Node(x);
  } else {
    g[y] = Merge(new Node(x), g[y]);
  }
  // in[x] = y;
}
void Update(int y) {
  g[y]->num++;
  g[y]->tag++;
}
void dfs(Node *rt) {
  if (rt == NULL) return;
  rt->Pushdown();
  rev[rt->val] += rt->num;
  dfs(rt->ch[0]);
  dfs(rt->ch[1]);
}
int sent[200005];
int main() {
  int n, m, s;
  scanf ("%d%d%d", &n, &m, &s);
  int t, x, y;
  while (s--) {
    scanf ("%d%d%d", &t, &x, &y);
    if (t == 1) {
      add(x, y);
    }
    if (t == 2) {
      del(x, y);
    }
    if (t == 3) {
      sent[x]++;
      Update(y);
    }
  }
  for (int i = 1; i <= n; i++) {
    dfs(g[i]);
  }
  for (int i = 1; i <= m; i++) {
    printf ("%d\n", rev[i] - sent[i]);
  }
}