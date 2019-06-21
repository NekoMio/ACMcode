#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
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
struct data {
  int v;
  long long cnt;
  bool operator < (const data &b) const {
    return cnt == b.cnt ? v < b.v : cnt < b.cnt;
  }
};
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
vector<data> Add[MAXN], Rm[MAXN];
set<data> st[MAXN];
long long C[MAXN], Ad[MAXN], ans;
bool flag = 0;
void DFS(int rt, int fa) {
  for (auto x : Add[rt])
    st[rt].insert(x);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
    if (flag) return;
    if (st[v[i].END].size() > st[rt].size()) {
      swap(st[v[i].END], st[rt]), swap(Ad[v[i].END], Ad[rt]);
    }
    for (auto x : st[v[i].END]) {
      st[rt].insert((data){x.v, C[x.v] = x.cnt - Ad[v[i].END] + Ad[rt]});
    }
  }
  for (auto x : Rm[rt]) {
    st[rt].erase((data){x.v, C[x.v]});
  }
  if (rt == 1) return;
  if (st[rt].empty()) { flag = 1; return; }
  ans += st[rt].begin()->cnt - Ad[rt];
  Ad[rt] += st[rt].begin()->cnt - Ad[rt];
}
int main() {
  memset (first, -1, sizeof(first));
  int n = read(), m = read();
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read(), c = read();
    Add[a].push_back((data){i, c});
    Rm[b].push_back((data){i, c});
    C[i] = c;
  }
  DFS(1, 0);
  if (flag) printf ("-1\n");
  else printf ("%lld\n", ans);
}