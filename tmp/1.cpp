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
const int MAXN = 1e6 + 5;
struct Node {
  Node *ch[2];
  long long Sum;
  Node() {
    ch[0] = ch[1] = NULL;
    Sum = 0;
  }
} * root[MAXN], *null;
Node *NewNode() {
  Node *o = new Node();
  o->ch[0] = o->ch[1] = null;
  return o;
}
void Copy(Node *&rt1, Node *rt2) {
  if (rt2 == null)
    rt1 = null;
  else
    rt1 = NewNode(), *rt1 = *rt2;
}
inline void Update(Node *&rt1, Node *rt2, int l, int r, int x, long long val) {
  Copy(rt1, rt2);
  if (rt1 == null) rt1 = NewNode();
  rt1->Sum += val;
  if (l == r) return;
  int mid = l + r >> 1;
  if (x <= mid)
    Update(rt1->ch[0], rt2->ch[0], l, mid, x, val);
  else
    Update(rt1->ch[1], rt2->ch[1], mid + 1, r, x, val);
}
inline long long Query(Node *rt1, Node *rt2, int l, int r, int L, int R) {
  if (L <= l && R >= r) return rt1->Sum - rt2->Sum;
  int mid = l + r >> 1;
  long long ans = 0;
  if (L <= mid) ans += Query(rt1->ch[0], rt2->ch[0], l, mid, L, R);
  if (R > mid) ans += Query(rt1->ch[1], rt2->ch[1], mid + 1, r, L, R);
  return ans;
}
int pos[MAXN], ed[MAXN];
struct data {
  int x, y;
} a[MAXN];
struct Query_Data {
  int x1, y1, x2, y2, id;
} Q[MAXN];
long long Ans[MAXN];
long long Get_val(long long j, long long k, long long l) {
  long long p = 0, q;
  if ((2 * j == l + 1) && (2 * k == l + 1)) return l * l;
  if ((k <= j) && (j + k <= l + 1))  // zuo
  {
    q = k - 1;
    p = (l + l - 2 * q) * q * 2 + (l - 2 * q - 1) * 2;
    p += j - k + 1;
    return p;
  }
  if ((k >= j) && (j + k >= l + 1))  // you
  {
    q = l - k;
    p = (l + l - 2 * q) * q * 2;
    p += l - q + 1 - j;
    return p;
  }
  if ((k < j) && (j + k > l + 1))  // shang
  {
    q = l - j;
    p = (l + l - 2 * q) * q * 2 + (l - 2 * q - 1) * 3;
    p += k - q;
    return p;
  }
  if ((k > j) && (j + k < l + 1)) {
    q = j - 1;
    p = (l + l - 2 * q) * q * 2 + (l - 2 * q - 1);
    p += l - q - k + 1;
    return p;
  }
  return 0;
}

int main() {
  null = new Node();
  null->ch[0] = null->ch[1] = null;
  int T = read();
  while (T--) {
    root[0] = null;
    memset(pos, 0, sizeof(pos));
    int n = read(), m = read(), p = read();
    for (int i = 1; i <= m; i++) a[i].x = read(), a[i].y = read();
    sort(a + 1, a + m + 1,
         [&](const data &a, const data &b) -> bool { return a.x < b.x; });
    for (int i = 1; i <= p; i++) {
      Q[i].x1 = read(), Q[i].y1 = read();
      Q[i].x2 = read(), Q[i].y2 = read();
      Q[i].id = i;
    }
    sort(Q + 1, Q + p + 1,
         [&](const Query_Data &a, const Query_Data &b) -> bool {
           return a.x2 < b.x2;
         });
    int now = 1, cnt = 0, pp = 0;
    for (int i = 1; i <= p; i++) {
      while (a[now].x <= Q[i].x2 && now <= m) {
        while (pp < a[now].x) {
          pp++;
          pos[pp] = cnt;
        }
        cnt++;
        Update(root[cnt], root[cnt - 1], 1, n, a[now].y, Get_val(a[now].y, a[now].x, n));
        now++;
      }
      while (pp < Q[i].x2) {
        pp++;
        pos[pp] = cnt;
      }
      Ans[Q[i].id] = Query(root[cnt], root[pos[Q[i].x1]], 1, n, Q[i].y1, Q[i].y2);
    }
    for (int i = 1; i <= p; i++) printf("%lld\n", Ans[i]);
  }
  // while (1);
}