#include <bits/stdc++.h>
using namespace std;
// string s[5 * 1000];
char s[4005][6005];
const int MAXN = 1e7 + 5e6;
struct edge {
  int END, next;
}v[MAXN];
int first[MAXN / 10], p;
void add(int a, int b) {
  // printf ("Add %d %d\n", a, b);
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;

  v[p].END = a;
  v[p].next = first[b];
  first[b] = p++;
}
int ID[1005][1005], Index;
int dis[MAXN / 10];
queue<int> Q;
int BFS(int S, int T) {
  dis[S] = 1;
  Q.push(S);
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] == -1) {
        dis[v[i].END] = dis[k] + 1;
        Q.push(v[i].END);
      }
    }
  }
  return dis[T];
}
int main() {
  int TT;
  // ios_base::sync_with_stdio(false);
  // cin.tie(0);
  // cin >> TT;
  scanf ("%d", &TT);
  memset (first, -1, sizeof (first));
  memset (dis, -1, sizeof (dis));
  while (TT--) {
    int n, m;
    Index = 0;
    // cin >> n >> m;
    scanf ("%d%d", &n, &m);
    int S, T;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        ID[i][j] = ++Index;
    getchar();
    // for (int i = 1; i <= 4 * n + 3; i++) getline(cin, s[i]);
    for (int i = 1; i <= 4 * n + 3; i++) gets(s[i]);
    for (int i = 3, o = 1; i < 4 * n + 3; i += 2, o++) {
      for (int j = 5, k = 1; j < 6 * m + 3; j += 6, k++) {
        if (!((k & 1) ^ (o & 1))) {
          if (s[i][j - 1] == 'S') S = ID[(i - 2) / 4 + 1][j / 6 + 1];
          if (s[i][j - 1] == 'T') T = ID[(i - 2) / 4 + 1][j / 6 + 1];
        } else {
          if (s[i][j - 1] == ' ') {
            add(ID[(i - 2 - 2) / 4 + 1][j / 6 + 1], ID[i / 4 + 1][j / 6 + 1]);
          }
        }
      }
    }
    for (int i = 4, o = 1; i < 4 * n + 2; i += 2, o++) {
      for (int j = 8, k = 1; j < 6 * m + 2; j += 6, k++) {
        if (s[i][j - 1] == ' ') {
          if (o & 1) add(ID[o / 2 + 1][k], ID[o / 2 + 1][k + 1]);
          else {
            if (k & 1) add(ID[o / 2 + 1][k], ID[o / 2][k + 1]);
            else add(ID[o / 2][k], ID[o / 2 + 1][k + 1]);
          }
        }
      }
    }
    printf ("%d\n", BFS(S, T));
    memset (first, -1, sizeof (first[0]) * (Index + 5)), p = 0;
    memset (dis, -1, sizeof (dis[0]) * (Index + 5));
  }
  // while (1);
}