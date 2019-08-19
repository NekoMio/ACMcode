#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <map>
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
const int MAXN = 2e5 + 5;
struct edge {
  int S, END, next;
}v[MAXN * 2];
int first[MAXN], p;
void add(int a, int b) {
  v[p].S = a;
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
bool inC[MAXN], vis[MAXN], flag_find;
map<int, int> E[MAXN], C[MAXN];
stack<int> st;
int Color[MAXN], Size, Num[MAXN], les;
void Init(int n) {
  memset (first, -1, sizeof (first));
  p = 0, flag_find = 0;
  Size = les = 0;
  while (!st.empty()) st.pop();
  memset (vis, 0, sizeof(vis));
  memset (inC, 0, sizeof(inC));
  memset (Color, 0, sizeof(Color));
  memset (Num, 0, sizeof (Num));
  for (int i = 1; i <= n; i++) E[i].clear();
  for (int i = 1; i <= n; i++) C[i].clear();
}
void DFS(int rt, int f) {
  if (vis[rt]) {
    flag_find = 1;
    while (1) {
      Size++;
      int tmp = st.top();
      inC[tmp / 2] = 1;
      st.pop();
      if (v[tmp].S == rt) break;
    }
    return;
  }
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (f  == i / 2) continue;
    st.push(i);
    DFS(v[i].END, i / 2);
    if (flag_find) return;
  }
  vis[rt] = 0;
  st.pop();
}
void Upd(int E_id, int c) {
  Num[Color[E_id]]--;
  if (Num[Color[E_id]] == Size - 1) les = 0;
  Num[c]++;
  if (Num[c] == Size) les = 1;
}
int main() {
  int T = read(), cnt = 0;
  while (T--) {
    cnt++;
    printf("Case #%d:\n", cnt);
    int n = read(), m = read();
    Init(n);
    for (int i = 1; i <= n; i++) {
      int a = read(), b = read(), c = read();
      add(a, b);
      add(b, a);
      Color[i - 1] = c;
      E[a][b] = i - 1;
      E[b][a] = i - 1;
      C[a][c]++;
      C[b][c]++;
    }
    DFS(1, 0);
    for (int i = 0; i < n; i++) {
      if(inC[i]) {
        Num[Color[i]]++;
        if (Num[Color[i]] == Size) les = 1;
      }
    }
    int Base_Ans = 0;
    for (int i = 1; i <= n; i++) Base_Ans += C[i].size();
    for (int i = 1; i <= m; i++) {
      int a = read(), b = read(), c = read();
      int E_id = E[a][b];
      if (--C[a][Color[E_id]] == 0) C[a].erase(Color[E_id]), Base_Ans--;
      if (--C[b][Color[E_id]] == 0) C[b].erase(Color[E_id]), Base_Ans--;
      if (!C[a].count(c)) Base_Ans++;
      if (!C[b].count(c)) Base_Ans++;
      C[a][c]++;
      C[b][c]++;
      if (inC[E_id]) Upd(E_id, c);
      Color[E_id] = c;
      printf("%d\n", Base_Ans - n + les);
    }
  }
  #ifdef Mine
  while(1);
  #endif
}