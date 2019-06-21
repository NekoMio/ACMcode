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
const int N = 100005;
const int MAXN = 100005;
struct edge {
  int END, next;
}e[MAXN << 1], v[25000005];
int firste[MAXN], pe, first[MAXN], p;
void adde(int a, int b) {
  e[pe].END = b;
  e[pe].next = firste[a];
  firste[a] = pe++;
}
void add(int a, int b) {
  // printf ("== %d %d\n", a, b);
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int Max[MAXN];
void DFS(int rt, int fa, int S) {
  if (Max[fa] < min(S, rt)) {
    add(S, rt); 
    add(rt, S);
  }
  if (rt != S) Max[rt] = max(rt, Max[fa]);
  else Max[rt] = 0;
  for (int i = firste[rt]; i != -1; i = e[i].next) {
    if (e[i].END == fa) continue;
    DFS(e[i].END, rt, S);
  }
}
queue<int> Q;
bool vis[5005];
int dis[5005];
int DJ(int S, int E) {
  Q.push(S);
  memset (dis, 0x3f, sizeof (dis));
  dis[S] = 0;
  while (!Q.empty()) {
    int k = Q.front(); Q.pop();
    vis[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] > dis[k] + 1) {
        dis[v[i].END] = dis[k] + 1;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          Q.push(v[i].END);
        }
      }
    }
  }
  return dis[E];
}
int main() {
  // freopen("tree.in", "r", stdin);
  // freopen("tree.out", "w", stdout);
  int n = read(), q = read();
  memset (first, -1, sizeof (first));
  memset (firste, -1, sizeof (firste));
  while (q--) {
    int op = read(), a = read(), b = read();
    if (op == 1) {
      adde(a, b);
      adde(b, a);
      DFS(b, 0, b);
    } else {
      printf ("%d\n", DJ(a, b));
    }
  }
  // while (1);
}