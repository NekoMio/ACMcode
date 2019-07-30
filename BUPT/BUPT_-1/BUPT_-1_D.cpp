#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
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
int Map[505][505];
struct edge {
  int END, next;
}v[250001];
int first[505], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
bool flag = 0;
char s[505];
char T[500];
void DFS(int x, char pre) {
  s[x] = T[pre];
  for (int i = first[x]; i != -1; i = v[i].next) {
    if (s[v[i].END]) {
      if (s[v[i].END] != pre) {
        flag = 1;
        return;
      }
    } else {
      DFS(v[i].END, s[x]);
      if (flag == 1) return;
    }
  }
}
int main() {
  T['a'] = 'c', T['c'] = 'a';
  int n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int a = read(), b = read();
    Map[a][b] = 1;
    Map[b][a] = 1;
  }
  memset(first, -1, sizeof (first));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) if (i != j) {
      if (!Map[i][j]) {
        add(i, j);
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    if (!s[i] && first[i] != -1)
      DFS(i, 'c');
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (Map[i][j]) {
        if (s[i] == 'a' && s[j] == 'c') 
          flag = 1;
      }
    }
  }
  if (flag) printf ("No\n");
  else {
    printf ("Yes\n");
    for (int i = 1; i <= n; i++) {
      printf ("%c", s[i] ? s[i] : 'b');
    }
  }
  // while (1);
}