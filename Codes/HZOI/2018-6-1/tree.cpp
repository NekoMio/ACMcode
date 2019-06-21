#include <bits/stdc++.h>
using namespace std;
const int MAXBUF = 1 << 23;
// char cB[MAXBUF], *cS = cB, *cT = cB;
// char getc()
// {
// 	if (cS == cT) cT = (cS = cB) + fread(cB, 1, MAXBUF, stdin);
// 	if (cS == cT) return 0;
// 	else return *cS++;
// }
#define getc getchar 
inline int read() {
  int x = 0, f = 1;
  char ch = getc();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getc();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getc();
  }
  return x * f;
}
const int MAXN = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int du[MAXN];
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int Minc[MAXN], g[MAXN];
int tmp[MAXN], top, ans[MAXN], n;
void Init(int rt, int fa) {
  Minc[rt] = 0x3f3f3f3f;
  int t = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    Init(v[i].END, rt);
    Minc[rt] = min(Minc[rt], Minc[v[i].END]);
    t++;
  }
  if (t == 0 || t == 1) Minc[rt] = min(rt, Minc[rt]);
}
void DFS1(int rt, int fa) {
  if (fa) g[rt] = min(g[fa], du[fa] < 3 ? fa : INF);
  else g[rt] = INF;
  int ls = -1, rs = -1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    if (ls < 0) ls = v[i].END;
    else rs = v[i].END;
  }
  if (ls < 0) return;
  if (rs < 0) {
    DFS1(ls, rt);
    g[rt] = min(g[rt], Minc[ls]);
    return;
  }
  int tmp = g[rt];
  g[rt] = min(tmp, Minc[rs]);
  DFS1(ls, rt);
  g[rt] = min(tmp, Minc[ls]);
  DFS1(rs, rt);
  g[rt] = min(g[rt], min(Minc[ls], Minc[rs]));
}
void DFS(int rt, int fa, bool tp) {
  int ls = -1, rs = -1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    if (ls < 0) ls = v[i].END;
    else rs = v[i].END;
  }
  if (ls < 0) return ans[++top] = rt, void();
  if (rs < 0) {
    if (tp) {ans[++top] = rt; DFS(ls, rt, 0); }
    else {
      if (rt == Minc[rt]) {ans[++top] = rt; DFS(ls, rt, 0); }
      else {DFS(ls, rt, 0); ans[++top] = rt;}
    }
    return ;
  }
  if (Minc[ls] > Minc[rs]) swap(ls, rs);
  if (tp) {
    ans[++top] = rt;
    DFS(ls, rt, 0);
    DFS(rs, rt, 1);
  } else {
    DFS(ls, rt, 0);
    ans[++top] = rt;
    DFS(rs, rt, 0);
  }
}
int main() {
  memset (first, -1, sizeof (first));
  n = read();
  int rt;
  for (int i = 1; i <= n; ++i) {
    du[i] = read();
    for (int j = 1; j <= du[i]; ++j) {
      int k = read();
      add(i, k);
    }
    if (du[i] < 3) rt = i;
  }
  Init(rt, 0);
  DFS1(rt, 0);
  int root = INF;
  for (int i = 1; i <= n; ++i) root = min(root, g[i]);
  // printf("g: "); for(int i = 1; i <= n; ++i) printf("%d%c", g[i], i < n ? ' ' : '\n');
  Init(root, 0);
  DFS(root, 0, 1);
  for (int i = 1; i <= n; ++i) {
    printf ("%d ", ans[i]);
  }
  printf ("\n");
}
