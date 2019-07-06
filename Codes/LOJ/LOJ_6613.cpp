#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9'){
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
queue<int> qu;
stack<int> st;
priority_queue<int> max_qu;
priority_queue<int, vector<int>, greater<int>> min_qu;
bool t[5];
int main() {
  memset(t, 1, sizeof(t));
  int n = read();
  register int i, op, v;
  for (i = 1; i <= n; i++) {
    op = read();
    v = read();
    if (op == 1) {
      if (t[2]) st.push(v);
      if (t[1]) qu.push(v);
      if (t[3]) max_qu.push(v);
      if (t[4]) min_qu.push(v);
    } else {
      if (t[2]) {
        if (st.empty() || v != st.top()) t[2] = 0;
        st.pop();
      }
      if (t[1]) {
        if (qu.empty() || v != qu.front()) t[1] = 0;
        qu.pop();
      }
      if (t[3]) {
        if (max_qu.empty() || v != max_qu.top()) t[3] = 0;
        max_qu.pop();
      }
      if (t[4]) {
        if (min_qu.empty() || v != min_qu.top()) t[4] = 0;
        min_qu.pop();
      }
    }
  }
  for (int i = 1; i <= 4; i++) {
    if (t[i]) printf ("Yes\n");
    else printf ("No\n");
  }
  getchar();
  getchar();
}