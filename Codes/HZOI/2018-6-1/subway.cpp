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
const int MAXN = 50;
#define lowbit(_) ((_) & (-_))
int n;
struct BIT
{
  int Sum[MAXN];
  void Update(int x, int c) {
    for (int i = x; i <= n; i = i + lowbit(i)) 
      Sum[i] += c;
  }
  int Query(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i = i - lowbit(i))
      ans += Sum[i];
    return ans;
  }
  int Query(int l, int r) {
    return Query(r) - Query(l - 1);
  }
  void clear() {
    memset(Sum, 0, sizeof (Sum));
  }
}st1, st2;
int ans;
int a[MAXN], num[MAXN], id[MAXN], Index, S[MAXN], E[MAXN];
bool flag[MAXN];
void DFS(int x, int t) {
  if (t >= ans) return;
  if (x > Index) return ans = t, void();
  st1.Update(E[x], 1);
  DFS(x + 1, t + min(st1.Query(S[x], E[x] - 1), st1.Query(E[x] + 1, n) + st2.Query(S[x] + 1, n)));
  st1.Update(E[x], -1);
  st2.Update(E[x], 1);
  DFS(x + 1, t + min(st2.Query(S[x], E[x] - 1), st2.Query(E[x] + 1, n) + st1.Query(S[x] + 1, n)));
  st2.Update(E[x], -1);
}
int main() {
  int T = read();
  while (T--) {
    n = read();
    Index = 0;
    st1.clear(), st2.clear();
    memset (flag, 0, sizeof (flag));
    memset (num, 0, sizeof (num));
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= n; ++i) num[a[i]]++;
    int top = 0;
    for (int i = 1; i <= n; ++i) {
      if (!(num[a[i]] & 1)) a[++top] = a[i];
    }
    n = top;
    for (int i = 1; i <= n; ++i) {
       if (!flag[a[i]]) id[a[i]] = ++Index, S[Index] = i, flag[a[i]] = 1;
       else E[id[a[i]]] = i;
    }
    ans = 0x3f3f3f3f;
    st1.Update(1, 1);
    DFS(1, 0);
    printf ("%d\n", ans);
  }
}
