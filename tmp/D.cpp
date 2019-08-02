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
const int MAXM = 100005;
const int MAXN = 505;
struct edge {
  int S, END, next;
  bool able;
}v[MAXM];
int first[MAXN], p;
void add(int a, int b) {
  v[p].S = a;
  v[p].able = 1;
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
bool vis[MAXN], flag;
void DFS(int rt) {
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].able && vis[v[i].END]) return flag = 1, vis[rt] = 0, void();
    if (!v[i].able) continue;
    DFS(v[i].END);
    if (flag) return vis[rt] = 0, void();
  }
  vis[rt] = 0;
}
stack<int> st;
bool tag[MAXN];
int H[MAXN], tot;
void DFS1(int rt) {
  tag[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!tag[v[i].END]) {
      st.push(i);
      DFS1(v[i].END);
      if (flag) return;
      st.pop();
    } else {
      H[++tot] = i;
      while (!st.empty()) {
        H[++tot] = st.top();
        st.pop();
        if (v[H[tot]].S == v[i].END) break;
      }
      flag = 1;
      return;
    }
  }
  tag[rt] = 0;
}
bool Judge(int n) {
  flag = 0;
  for (int i = 1; i <= n; i++) {
    DFS(i);
    if (flag) return 0;
  }
  return 1;
}
int main() {
  freopen ("1.in", "r", stdin);
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int a = read(), b = read();
    add(a, b);
  }
  DFS1(1);
  // cerr << 1 << endl;
  if (Judge(n)) return printf ("YES\n"), 0;
  // cerr << 2 << endl;
  printf ("%d\n", tot);
  for (int i = 1; i <= tot; i++) {
    v[H[i]].able = 0;
    // cerr << i << endl;
    if (Judge(n)) return printf ("YES\n"), 0;
    v[H[i]].able = 1;
  }
  printf ("NO\n");
}