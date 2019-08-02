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
const int MAXN = 1e5 + 5;
int ans = 0;
struct Trie_data {
  struct Node {
    Node *ch[26];
    int dep, s;
    Node (int d = 0) {
      dep = d;
      memset (ch, 0, sizeof (ch));
    }
  }*root;
  struct Cmp {
    const bool operator() (const Node *a, const Node *b) {
      return a->dep < b->dep;
    }
  }cmp;
  Trie_data() {
    root = new Node();
  }
  void insert(char *s) {
    int len = strlen(s);
    Node *rt = root;
    for (int i = 0; i < len; i++) {
      if (!rt->ch[s[i] - 'a'])
        rt->ch[s[i] - 'a'] = new Node(i + 1);
      rt = rt->ch[s[i] - 'a'];
      rt->s++;
    }
  }
  void BFS(int n) {
    static queue<Node*> Q;
    for (int i = 0; i < 26; i++) 
      if (root->ch[i])
        Q.push(root->ch[i]);
    while (!Q.empty()) {
      Node *rt = Q.front();
      Q.pop();
      n--;
      ans += rt->dep;
      if (n == 0) return;
      for (int i = 0; i < 26; i++) {
        if (rt->ch[i]) Q.push(rt->ch[i]);
      }
    }
  }
}Trie;
char s[MAXN];
int main() {
  int n = read();
  for (int i = 1; i <= n; i++) {
    scanf ("%s", s);
    Trie.insert(s);
  }
  Trie.BFS(n);
  printf ("%d\n", ans);
  // while (1);
}