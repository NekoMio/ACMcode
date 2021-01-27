#include <bits/stdc++.h>
using namespace std;
struct Node {
  int tag;
  map<string, Node*> mp;
  Node (int x) {
    tag = x;
  }
}*root;
void add(char *s, int tag) {
  int n = strlen(s), pre = 0;
  s[n++] = '/';
  Node *rt = root;
  for (int i = 0; i < n; i++) {
    if (s[i] == '/') {
      s[i] = 0;
      if (!rt->mp.count(s + pre)) {
        rt->mp[s + pre] = new Node(tag);
      }
      rt->tag = tag;
      rt = rt->mp[s + pre];
      pre = i + 1;
    }
  }
}
int Num = 0;
void DFS(Node *rt) {
  if (rt->tag == 1) Num++;
  if (rt->tag == 0) {
    for (auto x : rt->mp) {
      DFS(x.second);
    }
  }
}
int Calc(Node *rt) {
  // DFSPushUp(rt);
  Num = 0;
  DFS(rt);
  return Num;
}
char c[1005];
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, m;
    root = new Node(0);
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf ("%s", c);
      add(c, 1);
    }
    for (int i = 1; i <= m; i++) {
      scanf ("%s", c);
      add(c, 0);
    }
    int ans = 0;
    for (auto rt : root->mp) {
      ans += Calc(rt.second);
    }
    printf ("%d\n", ans);
  }
}