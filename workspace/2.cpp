#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
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
const int MAXN = 1e5 + 5;
int a[MAXN];
struct Node {
  Node *ch[2];
  int Max, Num;
  void Pushup() {
    Max = max(ch[0]->Max, ch[1]->Max);
    Num = ch[0]->Num + ch[1]->Num;
  }
  void* operator new(size_t);
}*root[MAXN], *null, *C, *mempool;
void* Node::operator new(size_t) {
  if (C == mempool) {
    C = new Node[1 << 15];
    mempool = C + (1 << 15);
  }
  return C++;
}
Node *NewNode() {
  Node *o = new Node();
  o->ch[0] = o->ch[1] = null;
  o->Max = 0;
  o->Num = 0;
}
void Copy(Node *&rt1, Node *rt2) {
  if (rt2 == null) rt1 = null;
  else rt1 = NewNode(), *rt1 = *rt2;
}
void Insert(Node *&rt1, Node *rt2, int x, int l, int r) {
  Copy(rt1, rt2);
  if (rt1 == null) rt1 = NewNode();
  rt1->Max = max(rt1->Max, x);
  rt1->Num++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (x <= mid) Insert(rt1->ch[0], rt2->ch[0], x, l, mid);
  else Insert(rt1->ch[1], rt2->ch[1], x, mid + 1, r);
}
int Query(Node *rt, int k, int l, int r) {
  if (l == r) return rt->Max;
  int mid = l + r >> 1;
  if (rt->ch[0]->Max == k) return k;
  if (rt->ch[0]->Max > k) return Query(rt->ch[0], k, l, mid);
  else return Query(rt->ch[1], k, mid + 1, r);
}
set<int> st;
int main() {
  int T = read();
  null = new Node();
  null->ch[0] = null->ch[1] = null;
  null->Max = null->Num = 0;
  while (T--) {
    st.clear();
    int n = read(), m = read();
    root[n + 1] = null;
    Insert(root[n], root[n + 1], n + 1, 1, n + 1);
    for (int i = 1; i <= n; i++)
      a[i] = read();
    for (int i = n; i >= 1; i--) {
      Insert(root[i - 1], root[i], a[i], 1, n + 1);
    }
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
      int op = read();
      if (op == 1) {
        int x = read() ^ lastans;
        st.insert(a[x]);
      } else {
        int r = read() ^ lastans, k = read() ^ lastans;
        int ans1, ans2;
        if (st.lower_bound(k) == st.end()) ans1 = n + 1;
        else ans1 = *(st.lower_bound(k));
        ans2 = Query(root[r], k, 1, n + 1);
        printf ("%d\n", lastans = min(ans1, ans2));
      }
#ifdef Mine
      lastans = 0;
#endif
    }
  }
#ifdef Mine
  while (1);
#endif
}