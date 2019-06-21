/*
 * LOJ_2587.cpp
 * Copyright (C) 2018 - WildRage
 * Created time: 2018-05-22
 */
 
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
const int MAXM = 400005;
const int MAXN = 100005;
struct edge {
  int S, END, next;
} v[MAXM], e[MAXM];
int first[MAXN], p, firste[MAXN << 1], pp;
void add(int a, int b) {
  v[p].END = b;
  v[p].S = a;
  v[p].next = first[a];
  first[a] = p++;
}
void Add(int a, int b) {
  e[pp].END = b;
  e[pp].S = a;
  e[pp].next = firste[a];
  firste[a] = pp++;
}
int val[MAXN << 1];
int dfn[MAXN], low[MAXN], Index, T;
int Color[MAXN];
bool iscut[MAXN];
vector<int> vc[MAXN];
stack<int> st;
void Tarjan(int rt, int fa) {
  dfn[rt] = low[rt] = ++Index;
  int S = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!dfn[v[i].END]) {
      st.push(i);
      S++;
      Tarjan(v[i].END, rt);
      low[rt] = min(low[rt], low[v[i].END]);
      if (low[v[i].END] >= dfn[rt]) {
        T++;
        iscut[rt] = 1;
        int x;
        while (1) {
          x = st.top(), st.pop();
          if (Color[v[x].END] != T) {
            Color[v[x].END] = T;
            vc[T].push_back(v[x].END);
          }
          if (Color[v[x].S] != T) {
            Color[v[x].S] = T;
            vc[T].push_back(v[x].S);
          }
          if (v[i].END == v[x].END && rt == v[x].S) break;
        }
      }
    }
    else if (dfn[v[i].END] < dfn[rt] && rt != fa) {
      st.push(i);
      low[rt] = min(low[rt], dfn[v[i].END]);
    }
  }
  if (fa < 0 && S == 1) iscut[rt] = 0;
}
int ID[MAXN], IDCol[MAXN], id;
long long ans = 0;
long long size[MAXN << 1], Sum[MAXN << 1];
int M, Cnt;
void dfs(int rt, int fa) {
  size[rt] = rt <= M;
  Cnt += size[rt];
  for (int i = firste[rt]; i != -1; i = e[i].next) {
    if (e[i].END == fa) continue; 
    dfs(e[i].END, rt);
    size[rt] += size[e[i].END];
  }
}
bool vis[MAXN << 1];
void DFS(int rt, int fa) {
  vis[rt] = 1;
  for (int i = firste[rt]; i != -1; i = e[i].next) {
    if (e[i].END == fa) continue;
    DFS(e[i].END, rt);
    ans = ans + val[rt] * (Cnt - size[e[i].END]) * size[e[i].END];
  }
  ans = ans + val[rt] * size[rt] * (Cnt - size[rt]);
  if (rt <= M) ans = ans + val[rt] * (Cnt - 1);
}
int main() {
  memset (first, -1, sizeof (first));
  memset (firste, -1, sizeof (firste));
  int n = read(), m = read();
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) {
      Tarjan(i, -1);
    }
  }
  for (int i = 1; i <= n; ++i) {
    ID[i] = ++id;
    val[id] = -1;
  }
  M = id;
  for (int i = 1; i <= T; ++i) {
    IDCol[i] = ++id;
    val[id] = vc[i].size();
    for (auto x : vc[i]) {
      Add(IDCol[i], ID[x]);
      Add(ID[x], IDCol[i]);
    }
  }
  for (int i = 1; i <= id; ++i) {
    if (!vis[i]) {
      Cnt = 0;
      dfs(i, 0);
      DFS(i, 0);
    }
  }
  printf ("%lld\n", ans);
}