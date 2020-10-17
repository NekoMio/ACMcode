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
struct edge {
  int S, END, v, next;
  double p;
} ZHENG[2000005], FAN[2000005];
struct A {
  int END, f, g;
  bool operator<(const A &a) const {
    if (f == a.f) return a.g < g;
    return a.f < f;
  }
};
int first_zheng[2005], first_fan[2005], p;
int dis[2005];
void add(int a, int b, int c, double pd) {
  ZHENG[p].p = pd;
  ZHENG[p].S = a;
  ZHENG[p].END = b;
  ZHENG[p].v = c;
  ZHENG[p].next = first_zheng[a];
  FAN[p].S = a;
  FAN[p].p = pd;
  FAN[p].END = a;
  FAN[p].v = c;
  FAN[p].next = first_fan[b];
  first_zheng[a] = p;
  first_fan[b] = p++;
}
int val[2005];
int pre[2005][2005], pre2[2005][2005];
bool vis[2005];
typedef pair<double, pair<int, int> > T;
priority_queue<T, vector<T>, less<T> > Q;
int n, u, m, c;
void spfa(int a) {
  dis[a] = 0;
  queue<int> p;
  p.push(a);
  vis[a] = 1;
  while (!p.empty()) {
    int tmp = p.front();
    vis[tmp] = 0;
    p.pop();
    for (int i = first_fan[tmp]; i != -1; i = FAN[i].next) {
      if (dis[FAN[i].END] > dis[tmp] + FAN[i].v) {
        dis[FAN[i].END] = dis[tmp] + FAN[i].v;
        if (!vis[FAN[i].END]) {
          vis[FAN[i].END] = 1;
          p.push(FAN[i].END);
        }
      }
    }
  }
}
void Spfa2(int S) {
  memset (pre2, -1, sizeof(pre2));
  Q.push(T(1, pair<int, int>(S, 0)));
  dis2[S][0] = 1;
  T tmp;
  pre2[S][0] = -2;
  while (!Q.empty()) {
    tmp = Q.top();
    Q.pop();
    int k = tmp.second.first;
    int j = tmp.second.second;
    if (dis2[k][j] > tmp.first) continue;
    for (int i = first2[k]; i != -1; i = v2[i].next) {
      if (v2[i].c + j > c) continue;
      int y = v2[i].END;
      if (dis2[y][j + v2[i].c] < dis2[k][j] * v2[i].p) {
        dis2[y][j + v2[i].c] = dis2[k][j] * v2[i].p;
        pre2[y][j + v2[i].c] = i;
        Q.push(T(dis2[y][j + v2[i].c], pair<int, int>(y, j + v2[i].c)));
      } 
    }
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