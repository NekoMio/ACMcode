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
const int MAXN = 500005;
const int MOD = 1000109107;
const int full = 20;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int val[MAXN], t[MAXN];
int fa[MAXN];

struct Trie {
  int s[21];
  struct Node {
    Node *ch[2];
    int s;
    Node () {
      ch[0] = ch[1] = NULL;
      s = 0;
    }
  }*null, *root;
  Node *NewNode() {
    Node *o = new Node();
    o->ch[0] = o->ch[1] = null;
    return o;
  }
  Trie() {
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    root = NewNode();
  }
  void insert(int x, int op = 1) {
    Node *rt = root;
    for (int i = 0; i <= full; ++i) {
      int nxt = (x >> i) & 1;
      if (rt->ch[nxt] == null) rt->ch[nxt] = NewNode();
      rt = rt->ch[nxt];
      rt->s += op;
      if (nxt == 1) s[i] += op;
    }
  }
  int Query_Update() {
    Node *rt = root;
    for (int i = 0; i <= full; ++i) {
      s[i] -= rt->ch[1]->s;
      s[i] += rt->ch[0]->s;
      swap(rt->ch[0], rt->ch[1]);
      rt = rt->ch[0];
    }
    int ans = 0;
    for (int i = 0; i <= full; ++i) {
      if (s[i] & 1) ans = ans ^ (1 << i);
    }
    return ans;
  }
}root[MAXN];
void DFS(int rt, int f) {
  fa[rt] = f;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == f) continue;
    DFS(v[i].END, rt);
    root[rt].insert(0);
  }
}
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  DFS(1, 0);
  int Ans = 0;
  for (int i = 1; i <= m; ++i) {
    int x = read();
    t[x]++;
    int ans = 0;
    if (fa[x] != 0) 
      ans = (++val[fa[x]] + t[fa[fa[x]]]);
    ans = ans ^ (root[x].Query_Update());
    if (fa[fa[x]] != 0)
    {
      root[fa[fa[x]]].insert(val[fa[x]] + t[fa[fa[x]]], 1);
      root[fa[fa[x]]].insert(val[fa[x]] - 1 + t[fa[fa[x]]], -1);
    }
    // printf("%d\n", ans);
    ans = 1ll * ans * ((1ll * i * i % MOD + i) % MOD) % MOD;
    Ans = (Ans + ans) % MOD;
  }
  printf ("%d\n", Ans);
}
