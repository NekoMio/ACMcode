#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
struct edge {
  int END, next;
}v[MAXN * 2];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int Fa[MAXN], Size[MAXN], Du[MAXN];
void DFS(int rt) {
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != Fa[rt]) {
      Fa[v[i].END] = rt;
      DFS(v[i].END);
      Size[rt] += Size[v[i].END];
    }
  }
  if (!Size[rt]) Size[rt] = 1;
}
int main() {
  int n, a, b;
  scanf ("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf ("%d%d", &a, &b);
    Du[a]++, Du[b]++;
    add(a, b);
    add(b, a);
  }
  int num = 0, id = 0;
  for (int i = n; i >= 1; i--) {
    if (Du[i] == 1) {
      num++;
      id = i;
    }
  }
  int root;
  if (num & 1) {
    Fa[v[id].END] = id;
  }
  root = v[id].END;
  DFS(root);
  
}