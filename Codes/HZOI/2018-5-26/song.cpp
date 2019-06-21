#pragma GCC optimize("O3")
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
inline void gmin(int &x, int y) { if (x > y) x = y; }
inline void gmin(long long &x, long long y) { if (x > y) x = y; }
const int MAXN = 4e5 + 5;
const long long INF = 0x3f3f3f3f3f3f3f3f;
char A[MAXN], B[MAXN];
int S[MAXN], E[MAXN], c[MAXN];
long long f[MAXN];
unsigned int Hash[MAXN], Hash_a[MAXN], bin[MAXN], base = 31;
unsigned int Get_Hash(int l, int r) {
  return Hash[r] - Hash[l - 1] * bin[r - l + 1];
}
unsigned int Get_Hash_a(int l, int r) {
  return Hash_a[r] - Hash_a[l - 1] * bin[r - l + 1];
}
long long Min[MAXN << 2];
long long tag[MAXN << 2];
void Pushup(int rt) { Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]); }
void build(int l, int r, int rt) {
  tag[rt] = INF;
  if (l == r) {
    Min[rt] = INF;
    return;
  }
  int mid = l + r >> 1;
  build(l, mid, rt << 1);
  build(mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
void Update(int L, int R, long long c, int l, int r, int rt) {
  if (c > tag[rt]) return;
  if (L <= l && R >= r) {
    gmin(Min[rt], c);
    gmin(tag[rt], c);
    return;
  }
  int mid = l + r >> 1;
  if (L <= mid) Update(L, R, c, l, mid, rt << 1);
  if (R > mid) Update(L, R, c, mid + 1, r, rt << 1 | 1);
  Pushup(rt);
}
long long Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return min(Min[rt], tag[rt]);
  int mid = l + r >> 1;
  long long ans = tag[rt];
  if (L <= mid && Min[rt << 1] < ans) gmin(ans, Query(L, R, l, mid, rt << 1));
  if (R > mid && Min[rt << 1 | 1] < ans) gmin(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
  return ans;
}
struct Trie {
  struct Node {
    Node *ch[2];
    int c;
    Node() {
      ch[0] = ch[1] = NULL;
      c = 0x3f3f3f3f;
    }
  } * root;
  Trie() { root = new Node(); }
  void insert(int x, int E, int val) {
    Node *rt = root;
    for (register int i = x; i <= E; ++i) {
      if (rt->ch[B[i] - '0'] == NULL) rt->ch[B[i] - '0'] = new Node();
      gmin(rt->ch[B[i] - '0']->c, val);
      rt = rt->ch[B[i] - '0'];
    }
  }
  void insertf(int S, int E, int val) {
    Node *rt = root;
    for (register int i = S; i >= E; --i) {
      if (rt->ch[B[i] - '0'] == NULL) rt->ch[B[i] - '0'] = new Node();
      gmin(rt->ch[B[i] - '0']->c, val);
      rt = rt->ch[B[i] - '0'];
    }
  }
} tr, tr2;
int block = 3000;
vector<int> vc;
void Update_from_trie(int x) {
  Trie::Node *rt = tr2.root;
  if (rt->ch[A[x] - '0'] == NULL)
    return;
  else
    rt = rt->ch[A[x] - '0'];
  for (int i = x - 1; i >= 0; --i) {
    gmin(f[x], rt->c + f[i]);
    if (rt->ch[A[i] - '0'] == NULL)
      return;
    else
      rt = rt->ch[A[i] - '0'];
  }
}
int m, n, L;
int Divide(int x, int y) {
  int l = 0, r = min(y, E[x] - S[x] + 1), ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Get_Hash(E[x] - mid + 1, E[x]) == Get_Hash_a(y - mid + 1, y))
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  return ans;
}
int Divide2(int x, int y, int &val) {
  int l = val, r = min(E[x] - S[x] + 1, m - y + 1), ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Get_Hash(S[x], S[x] + mid - 1) == Get_Hash_a(y, y + mid - 1))
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  return ans;
}
void Update_from_Seg(int x) {
  for (auto i : vc) {
    int len = Divide(i, x);
    gmin(f[x], Query(x - len, x - 1, 0, m, 1) + c[i]);
  }
  gmin(f[x], Query(x, x, 0, m, 1));
}
void Update_for_trie(int x) {
  Trie::Node *rt = tr.root;
  for (int i = x + 1; i <= m; ++i) {
    if (rt->ch[A[i] - '0'] == NULL)
      return;
    else
      rt = rt->ch[A[i] - '0'];
    gmin(f[i], rt->c + f[x]);
  }
}
void Update_for_Seg(int x) {
  int lstlen = 0x3f3f3f3f;
  for (auto i : vc) {
    int len = Divide2(i, x + 1, lstlen);
    if (len != 0) Update(x + lstlen, x + len, f[x] + c[i], 0, m, 1);
    lstlen = len;
  }
}
int main() {
  // freopen ("test/11.in", "r", stdin);
  register int i;
  m = read(), n = read(), L = read();
  scanf("%s", A + 1);
  bin[0] = 1;
  for (i = 1; i <= MAXN - 2; ++i) bin[i] = bin[i - 1] * base;
  for (i = 1; i <= n; ++i) {
    c[i] = read();
    S[i] = E[i - 1] + 2;
    scanf("%s", B + S[i]);
    E[i] = S[i] + strlen(B + S[i]) - 1;
    if (E[i] - S[i] <= block) {
      tr.insert(S[i], E[i], c[i]);
      tr2.insertf(E[i], S[i], c[i]);
    } else {
      vc.push_back(i);
    }
  }
  // fprintf (stderr, "%u\n", vc.size());
  memset (f, 0x3f, sizeof (f));
  sort(vc.begin(), vc.end(), [](const int &x, const int &y) {
    return c[x] < c[y];
  });
  for (i = 1; i <= E[n]; ++i) Hash[i] = Hash[i - 1] * base + B[i];
  for (i = 1; i <= m; ++i) Hash_a[i] = Hash_a[i - 1] * base + A[i];
  f[0] = 0;
  build(0, m, 1);
  Update_for_Seg(0);
  Update_for_trie(0);
  Update(0, 0, 0, 0, m, 1);
  for (i = 1; i <= m; ++i) {
    Update_from_trie(i);
    Update_from_Seg(i);
    Update(i, i, f[i], 0, m, 1);
    Update_for_trie(i);
    Update_for_Seg(i);
  }
  if (f[m] != INF) printf("%lld\n", f[m]);
  else printf ("-1\n");
}

