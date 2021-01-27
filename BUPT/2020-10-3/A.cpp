#include <bits/stdc++.h>
using namespace std;
struct edge {
  int S, END, next;
  int id;
}v[100005];
int first[10005], p;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].id = c;
  v[p].S = a;
  first[a] = p++;
}
queue<int> Q;
int dis[10005], vis[10005], pree[10005];
bool flag[10005];
int Tp(int x, int y) {
  if (y == -1) return 0;
  else return v[x].id != v[y].id;
}
struct data {
  int id, s, e;
};
stack<data> st;
void spfa(int S, int E) {
  memset (dis, 0x3f, sizeof(dis));
  memset (vis, 0x3f, sizeof(vis));
  memset (pree, -1, sizeof(pree));
  Q.push(S);
  dis[S] = 0;
  vis[S] = 0;
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    flag[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] > dis[k] + 1) {
        dis[v[i].END] = dis[k] + 1;
        vis[v[i].END] = vis[k] + Tp(i, pree[k]);
        pree[v[i].END] = i;
        if (!flag[v[i].END]) {
          Q.push(v[i].END);
          flag[v[i].END] = 1;
        }
      } else if (dis[v[i].END] == dis[k] + 1) {
        if (vis[v[i].END] > vis[k] + Tp(i, pree[k])) {
          vis[v[i].END] = vis[k] + Tp(i, pree[k]);
          pree[v[i].END] = i;
          if (!flag[v[i].END]) {
            Q.push(v[i].END);
            flag[v[i].END] = 1;
          }
        }
      }
    }
  }
  if (dis[E] == 0x3f3f3f3f) {
    printf ("Sorry, no line is available.\n");
  } else {
    printf ("%d\n", dis[E]);
    int a1 = v[pree[E]].S, a2 = v[pree[E]].END;
    int preid = v[pree[E]].id;
    E = v[pree[E]].S;
    while (pree[E] != -1) {
      if (preid != v[pree[E]].id) {
        st.push(data{preid, a1, a2});
        a1 = v[pree[E]].S, a2 = v[pree[E]].END;
        preid = v[pree[E]].id;
      } else {
        a1 = v[pree[E]].S;
      }
      E = v[pree[E]].S;
    }
    st.push(data{preid, a1, a2});
    while (!st.empty()) {
      printf ("Go by the line of company #%d from %04d to %04d.\n", st.top().id, st.top().s, st.top().e);
      st.pop();
    }
  }
}
int main() {
  int n;
  memset (first, -1, sizeof(first));
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    int m, b, pre;
    scanf ("%d", &m);
    for (int j = 1; j <= m; j++) {
      scanf ("%d", &b);
      if (j != 1) {
        add(pre, b, i);
        add(b, pre, i);
      }
      pre = b;
    }
  }
  int K, a, b;
  scanf ("%d\n", &K);
  for (int i = 1; i <= K; i++) {
    scanf ("%d%d", &a, &b);
    spfa(a, b);
  }
}