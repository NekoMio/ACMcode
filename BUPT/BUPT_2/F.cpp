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
    int dep, s, Mx, Num;
    bool flag;
    Node (int d = 0) {
      dep = d;
      s = 0;
      flag = 0;
      memset (ch, 0, sizeof (ch));
    }
  }*root;
  // struct Cmp {
  //   const bool operator() (const Node *a, const Node *b) {
  //     return a->dep < b->dep;
  //   }
  // }cmp;
  Trie_data() {
    root = new Node();
  }
  void insert(char *s) {
    int len = strlen(s);
    Node *rt = root;
    for (int i = 0; i < len; i++) {
      if (!rt->ch[s[i] - 'a']) {
        rt->ch[s[i] - 'a'] = new Node(i + 1);
        rt->Num++;
      }
      rt = rt->ch[s[i] - 'a'];
      rt->s++;
    }
    rt->flag = 1;
  }
}Trie;
char s[MAXN];
deque<int> Q;
void DFS(Trie_data::Node *rt) {
  if (rt->flag) {
    if (Q.empty())
      ans += rt->dep;
    else {
      ans += Q.front();
      Q.pop_front();
      Q.push_back(rt->dep);
    }
  } else {
    Q.push_back(rt->dep);
  }
  int H[27], tot = 0;
  for (int i = 0; i < 26; i++) {
    if (rt->ch[i]) {
      H[++tot] = i;
    }
  }
  sort(H + 1, H + tot + 1, [&](const int &a, const int &b) -> bool {
    return rt->ch[a]->Num - rt->ch[a]->s < rt->ch[b]->Num - rt->ch[b]->s;
  });
  for (int i = 1; i <= tot; i++) {
    DFS(rt->ch[H[i]]);
  }
  if (!Q.empty() && Q.back() == rt->dep) Q.pop_back();
}
void DFS1(Trie_data::Node *rt) {
  rt->Mx = 1;
  for (int i = 0; i < 26; i++) {
    if (rt->ch[i]) {
      DFS1(rt->ch[i]);
      rt->Mx += rt->ch[i]->Mx;
    }
  }
}
int main() {
  int n = read();
  for (int i = 1; i <= n; i++) {
    scanf ("%s", s);
    Trie.insert(s);
  }
  DFS1(Trie.root);
  int H[26], tot = 0;
  for (int i = 0; i < 26; i++) {
    if (Trie.root->ch[i]) {
      H[++tot] = i;
    }
  }
  for (int i = 1; i <= tot; i++) {
    DFS(Trie.root->ch[H[i]]);
  }
  printf ("%d\n", ans);
  // while (1);
}