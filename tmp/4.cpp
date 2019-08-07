#pragma GCC optimize("O2")
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
struct Hash_Table {
  struct edge {
    int next;
    long long v;
    pair<int, int> a;
  }v[100005];
  // 9901 7717
  int first[1010], p;
  Hash_Table() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
  long long &operator[] (const pair<int, int> &a) {
    int H = (a.first % 9901 + 9901) * (a.second % 7717 + 7717) % 1009;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].a == a) {
        return v[i].v;
      }
    }
    v[p].a = a;
    v[p].next = first[H];
    first[H] = p++;
    return v[p - 1].v = 0;
  }
  bool count(const pair<int, int> &a) {
    int H = (a.first % 9901 + 9901) * (a.second % 7717 + 7717) % 1009;
    for (int i = first[H]; i != -1; i = v[i].next) {
      if (v[i].a == a) {
        return 1;
      }
    }
    return 0;
  }
  void clear() {
    memset (first, -1, sizeof (first));
    p = 0;
  }
}mp;
struct Node {
  Node *ch[2];
  vector<int> vc;
  Node(int m = 0) {
    vc.resize(m + 1);
    ch[0] = ch[1] = NULL;
  }
  void *operator new (size_t);
}*root, *C, *mempool;
void* Node::operator new(size_t) {
  if (C == mempool) {
    C = new Node[1 << 15];
    mempool = C + (1 << 15);
  }
  return C++;
}
int m;
void dots(vector<int> &a, vector<int> &b, vector<int> &ans) {
  for (int i = 1; i <= m; i++)
    ans[i] = b[a[i]];
}
void Build(int l, int r, Node *&rt) {
  rt = new Node(m);
  if (l == r) {
    for (int i = 1; i <= m; i++)
      rt->vc[i] = read();
    return;
  }
  int mid = l + r >> 1;
  Build(l, mid, rt->ch[0]);
  Build(mid + 1, r, rt->ch[1]);
  dots(rt->ch[0]->vc, rt->ch[1]->vc, rt->vc);
}
void Query(vector<int> &Ans, int L, int R, int l, int r, Node *rt) {
  if (L <= l && R >= r) {
    dots(Ans, rt->vc, Ans);
    return;
  }
  int mid = l + r >> 1;
  if (L <= mid) Query(Ans, L, R, l, mid, rt->ch[0]);
  if (R > mid) Query(Ans, L, R, mid + 1, r, rt->ch[1]);
}
int main() {
  int T = read();
  while (T--) {
    // mp.clear();
    int n = read();
    m = read();
    root = NULL;
    Build(1, n, root);
    int Q = read(), l, r;
    vector<int> Ans;
    for (int i = 1; i <= Q; i++) {
      l = read(), r = read();
      // if (mp.count(pair<int, int>(l, r))) {
      //   printf ("%lld\n", mp[pair<int,int>(l, r)]);
      //   continue;
      // }
      Ans.clear();
      Ans.resize(m + 1);
      for (int i = 1; i <= m; i++) Ans[i] = i;
      Query(Ans, l, r, 1, n, root);
      long long ans = 0;
      for (int i = 1; i <= m; i++) ans += Ans[i] * i;
      printf ("%lld\n", ans);
      // mp[pair<int,int>(l, r)] = ans;
    }
  }
  // while (1);
}