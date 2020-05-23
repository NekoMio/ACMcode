#include <bits/stdc++.h>
using namespace std;
char s1[4005], s2[4005];
int f[4005][4005];
short pre[4005][4005][3];
bool vis[4005][4005];
int nxt1[4005][2], nxt2[4005][2];
stack<int> st;
queue<pair<int, int>> Q;
#define D pair<int, int>
int main() {
  scanf ("%s", s1 + 1);
  scanf ("%s", s2 + 1);
  memset (pre, -1, sizeof (pre));
  int len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
  memset (f, 0x3f, sizeof(f));
  f[0][0] = 1;
  int tpre[2] = {len1 + 1, len1 + 1};
  nxt1[len1 + 1][0] = len1 + 1;
  nxt1[len1 + 1][1] = len1 + 1;
  for (int i = len1; i >= 0; i--) {
    nxt1[i][0] = tpre[0];
    nxt1[i][1] = tpre[1];
    if (i != 0) tpre[s1[i] - '0'] = i;
  }
  tpre[0] = len2 + 1, tpre[1] = len2 + 1;
  nxt2[len2 + 1][0] = len2 + 1;
  nxt2[len2 + 1][1] = len2 + 1;
  for (int i = len2; i >= 0; i--) {
    nxt2[i][0] = tpre[0];
    nxt2[i][1] = tpre[1];
    if (i != 0) tpre[s2[i] - '0'] = i;
  }
  // for (int i = 0; i <= len1 + 1; i++) {
  //   for (int j = len2 + 1; j >= 0; j--) {
  //     for (int k = 0; k <= 1; k++) {
  //       if (f[nxt1[i][k]][nxt2[j][k]] > f[i][j] + 1) {
  //         f[nxt1[i][k]][nxt2[j][k]] = f[i][j] + 1;
  //         pre[nxt1[i][k]][nxt2[j][k]][0] = i;
  //         pre[nxt1[i][k]][nxt2[j][k]][1] = j;
  //         pre[nxt1[i][k]][nxt2[j][k]][2] = k;
  //       }
  //     }
  //   }
  // }
  Q.push(D(0, 0));
  while (!Q.empty()) {
    int i = Q.front().first, j = Q.front().second;
    vis[i][j] = 0;
    Q.pop();
    for (int k = 0; k <= 1; k++) {
      if (f[nxt1[i][k]][nxt2[j][k]] > f[i][j] + 1) {
        f[nxt1[i][k]][nxt2[j][k]] = f[i][j] + 1;
        pre[nxt1[i][k]][nxt2[j][k]][0] = i;
        pre[nxt1[i][k]][nxt2[j][k]][1] = j;
        pre[nxt1[i][k]][nxt2[j][k]][2] = k;
        if (!vis[nxt1[i][k]][nxt2[j][k]]) {
          Q.push(D(nxt1[i][k], nxt2[j][k]));
          vis[nxt1[i][k]][nxt2[j][k]] = 1;
        }
      }
    }
  }
  int ii, jj;
  for (int i = len1 + 1, j = len2 + 1; ; i = ii, j = jj) {
    ii = pre[i][j][0], jj = pre[i][j][1];
    if (ii == -1) break;
    st.push(pre[i][j][2]);
  }
  while (!st.empty()) {
    printf ("%d", st.top());
    st.pop();
  }
}