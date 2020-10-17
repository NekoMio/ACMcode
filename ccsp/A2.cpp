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
struct data {
  int S, END, next;
  int c;
  double p;
}v[2000005], v2[2000005];
int first[2005], p, first2[2005], p2;
void add(int a, int b, int c, double pd) {
  v[p].END = b;
  v[p].c = c;
  v[p].p = pd;
  v[p].S = a;
  v[p].next = first[a];
  first[a] = p++;
}
void add2(int a, int b, int c, double pd) {
  v2[p2].END = b;
  v2[p2].c = c;
  v2[p2].p = pd;
  v2[p2].S = a;
  v2[p2].next = first2[a];
  first2[a] = p2++;
}
int val[2005];
double dis[2005][2005], dis2[2005][2005];
int pre[2005][2005], pre2[2005][2005];
bool vis[2005];
set<int> sa[2005];
queue<int> Q;
int n, u, m, c;
void Spfa(int S) {
  memset (pre, -1, sizeof(pre));
  memset (vis, 0, sizeof(vis));
  Q.push(S);
  vis[S] = 1;
  dis[S][0] = 1;
  pre[S][0] = -2;
  sa[S].insert(0);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    vis[k] = 0;
    for (int j : sa[k]) {
      int prej = -1;
      if (prej != -1 && dis[k][j] < dis[k][prej]) break;
      prej = j;
      for (int i = first[k]; i != -1; i = v[i].next) {
        if (j + v[i].c > c) continue;
        if (dis[v[i].END][j + v[i].c] < dis[k][j] * v[i].p) {
          dis[v[i].END][j + v[i].c] = dis[k][j] * v[i].p;
          pre[v[i].END][j + v[i].c] = i;
          sa[v[i].END].insert(j + v[i].c);
          if (!vis[v[i].END]) {
            vis[v[i].END] = 1;
            Q.push(v[i].END);
          }
        }
      }
    }
    sa[k].clear();
  }
}
void Spfa2(int S) {
  memset (pre2, -1, sizeof(pre2));
  memset (vis, 0, sizeof(vis));
  Q.push(S);
  vis[S] = 1;
  dis2[S][0] = 1;
  pre2[S][0] = -2;
  sa[S].insert(0);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    vis[k] = 0;
    for (auto j : sa[k]) {
      int prej = -1;
      if (prej != -1 && dis2[k][j] < dis2[k][prej]) break;
      prej = j;
      for (int i = first2[k]; i != -1; i = v2[i].next) {
        if (j + v2[i].c > c) continue;
        if (dis2[v2[i].END][j + v2[i].c] < dis2[k][j] * v2[i].p) {
          dis2[v2[i].END][j + v2[i].c] = dis2[k][j] * v2[i].p;
          pre2[v2[i].END][j + v2[i].c] = i;
          sa[v2[i].END].insert(j + v2[i].c);
          if (!vis[v2[i].END]) {
            vis[v2[i].END] = 1;
            Q.push(v2[i].END);
          }
        }
      }
    }
    sa[k].clear();
  }
}
stack<int> st;
void print(int e, int j) {
  st.push(e);
  int tmpj;
  while (pre[e][j] >= 0) {
    st.push(v[pre[e][j]].S);
    tmpj = j;
    j -= v[pre[e][j]].c;
    e = v[pre[e][tmpj]].S;
  }
  while (!st.empty()) {
    printf ("%d ", st.top());
    st.pop();
  }
}
#define lowbit(_) ((_) & (-_))
int Maxn[2005];
void addM(int x, int pos) {
  for (int i = x; i <= c; i += lowbit(i)) {
    if (dis2[pos][x] > dis2[pos][Maxn[i]]) {
      Maxn[i] = x;
    }
  }
}
int Query(int x, int pos) {
  int ans = dis2[pos][Maxn[x]];
  for (int i = x; i > 0; i -= lowbit(i)) {
    if (dis2[pos][Maxn[i]] > dis2[pos][ans]) {
      ans = Maxn[i];
    }
  }
  return ans;
}
int main() {
  n = read(), u = read(), m = read(), c = read();
  for (int i = 1; i <= u; i++) {
    val[i] = read();
  }
  memset (first, -1, sizeof (first));
  memset (first2, -1, sizeof(first2));
  int a, b, cp;
  double pd;
  for (int i = 1; i <= m; i++) {
    a = read(), b = read();
    scanf ("%lf", &pd);
    cp = read();
    add(a, b, cp, 1 - pd);
    add2(b, a, cp, 1 - pd);
  }
  Spfa(0);
  Spfa2(0);
  double Max = 0;
  int ai, aj, ak;
  for (int i = 1; i <= u; i++) {
    for (int j = 0; j <= c; j++) {
      Maxn[j] = 0;
    }
    for (int j = 1; j + val[i] <= c; j++)
      addM(j, i);
    for (int j = 0; j + val[i] < c; j++) {
      int t = Query(c - j - val[i], i);
      if (Max < dis[i][j] * dis2[i][t]) {
        Max = dis[i][j] * dis2[i][t];
        ai = i;
        aj = j;
        ak = t;
      }
    }
  }
  printf ("%d\n", ai);
  printf ("%d\n", aj + ak + val[ai]);
  printf ("%.7f\n", 1 - Max);
  print(ai, aj);
  int tmpj;
  while (pre2[ai][ak] >= 0) {
    printf ("%d ", v2[pre2[ai][ak]].S);
    tmpj = ak;
    ak -= v2[pre2[ai][ak]].c;
    ai = v2[pre2[ai][tmpj]].S;
  }
  printf ("\n");
}