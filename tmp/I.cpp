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
const int MAXN = 1e4 + 5;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
vector<int> ch[MAXN];
set<unsigned> st[MAXN];
map<unsigned, int> mp1, mp2;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int size[MAXN], fa[MAXN];
char c[MAXN], s[MAXN];
unsigned int Hash1[MAXN], Hash2[MAXN], base = 31;
bool cmp(const int &a, const int &b) {
  return size[a] > size[b];
}
void Get_Size(int rt, int f) {
  size[rt] = 1;
  fa[rt] = f;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != f) {
      ch[rt].push_back(v[i].END);
      Get_Size(v[i].END, rt);
      size[rt] += size[v[i].END];
    }
  }
  sort(ch[rt].begin(), ch[rt].end(), cmp);
}
void DFS(int rt) {
  vector<int>::iterator it;
  set<unsigned>::iterator it2;
  if (mp1.find(c[rt]) != mp1.end()) st[rt].insert(c[rt]);
  for (it = ch[rt].begin(); it != ch[rt].end(); ++it) {
    DFS(*it);
  }
}
int main() {
  int T = read();
  while (T--) {
    int n = read();
    memset (first, -1, sizeof (first));
    p = 0;
    for (int i = 1; i < n; i++) {
      int a = read(), b = read();
      add(a, b);
      add(b, a);
    }
    scanf ("%s", c + 1);
    scanf ("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; i++)
      Hash1[i] = Hash1[i - 1] * base + s[i];
    for (int i = len; i >= 1; i--)
      Hash2[i] = Hash2[i + 1] * base + s[i];
    Get_Size(1, 0);
    DFS(1);
  }
}