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
const int N = 1000010;
const int S = (1 << 30) - 1;
struct Node {
  Node *ch[2];
  int val, v0, tag;
  Node() {
    v0 = val = 0;
    tag = -1;
    ch[0] = ch[1] = NULL;
  }
  void Pushtag(int c) {
    val = v0 = tag = c;
  }
  void Pushdown() {
    if (tag != -1) {
      ch[0]->Pushtag(tag);
      ch[1]->Pushtag(tag);
      tag = -1;
    }
  }
  void Pushup() {
    val = ch[0]->val & ch[1]->val;
    v0 = ch[0]->v0 | ch[1]->v0;
  }
}*root;
void Update(Node *rt, int x, int c, int l, int r) {
  if (l == r) { rt->val += c, rt->v0 += c; return;}
  int mid = l + r >> 1;
  rt->Pushdown();
  if (x <= mid) Update(rt->ch[0], x, c, l, mid);
  else Update(rt->ch[1], x, c, mid + 1, r);
  rt->Pushup();
}
void Update(Node *rt, int L, int R, int c, int l, int r) {
  if (R < L) return;
  if (L <= l && R >= r) {
    rt->Pushtag(c);
    return;
  }
  int mid = l + r >> 1;
  rt->Pushdown();
  if (L <= mid) Update(rt->ch[0], L, R, c, l, mid);
  if (R > mid) Update(rt->ch[1], L, R, c, mid + 1, r);
  rt->Pushup();
}
int Query(Node *rt, int x, int l, int r) {
  if (l == r) return rt->val;
  rt->Pushdown();
  int mid = l + r >> 1, ans;
  if (x <= mid) ans = Query(rt->ch[0], x, l, mid);
  else ans = Query(rt->ch[1], x, mid + 1, r);
  rt->Pushup();
  return ans;
}
int find_inf(Node *rt, int x, int l, int r) {
  if (rt->val == S) return -1;
  if (l == r) return l;
  int mid = l + r >> 1;
  rt->Pushdown();
  if (x <= mid) {
    int t = find_inf(rt->ch[0], x, l, mid);
    if (t == -1) return find_inf(rt->ch[1], x, mid + 1, r);
    else return t;
  } else return find_inf(rt->ch[1], x, mid + 1, r);
}
int find_0(Node *rt, int x, int l, int r) {
  if (rt->v0 == 0) return -1;
  if (l == r) return l;
  int mid = l + r >> 1;
  rt->Pushdown();
  if (x <= mid) {
    int t = find_0(rt->ch[0], x, l, mid);
    if (t == -1) return find_0(rt->ch[1], x, mid + 1, r);
    return t;
  } else return find_0(rt->ch[1], x, mid + 1, r);
}
void add(int x, int a) {
  int tmp = Query(root, x, 0, N);
  if (tmp + a <= S) Update(root, x, a, 0, N);
  else {
    Update(root, x, a - S - 1, 0, N);
    int t = find_inf(root, x + 1, 0, N);
    Update(root, x + 1, t - 1, 0, 0, N);
    Update(root, t, 1, 0, N);
  }
}
void Del(int x, int a) {
  int tmp = Query(root, x, 0, N);
  if (tmp - a >= 0) Update(root, x, -a, 0, N);
  else {
    Update(root, x, S + 1 - a, 0, N);
    int t = find_0(root, x + 1, 0, N);
    Update(root, x + 1, t - 1, S, 0, N);
    Update(root, t, -1, 0, N);
  }
}
int vc[35], cnt;
void Update(int a, int b) {
  if (a > 0) {
    int t = b / 30;
    add(t, (a << (b - t * 30)) & S);
    add(t + 1, (a >> (30 - (b - t * 30))));
  } else if (a < 0) {
    a = -a;
    int t = b / 30;
    Del(t, (a << (b - t * 30)) & S);
    Del(t + 1, (a >> (30 - (b - t * 30))));
  }
}
int Query(int x) {
  return (Query(root, x / 30, 0, N) & (1 << (x - x / 30 * 30))) ? 1 : 0;
}
void Build(Node *&rt, int l, int r) {
  rt = new Node();
  if (l == r) return;
  int mid = l + r >> 1;
  Build(rt->ch[0], l, mid);
  Build(rt->ch[1], mid + 1, r);
  rt->Pushup();
}
int main() {
  int n = read(), t1 = read(), t2 = read(), t3 = read();
  Build(root, 0, N);
  while (n--) {
    int op = read();
    if (op == 1) {
      int a = read(), b = read();
      Update(a, b);
    } else {
      printf ("%d\n", Query(read()));
    }
  }
}