#include <bits/stdc++.h>
using namespace std;
int IDS[30][30], IDE[30], IDN[30][30], Index;
const int MAXN = 2e6 + 5;
struct edge {
  int END, next;
}v[MAXN];
int first[1000], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int CalcId(char *s, int op) {
  if (isupper(s[0])) {
    if (s[1] == '.') {
      return IDS[s[0] - 'A'][s[2] - 'a'];
    } else {
      return IDS[s[0] - 'A'][26];
    }
  } else {
    return IDE[s[0] - 'a'];
  }
}
char rd[4][10];
bool vis[1000];
vector<int> vc[30][30];
void DFS(int rt) {
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END]) {
      DFS(v[i].END);
    }
  }
}
int main() {
  int n;
  memset(first, -1, sizeof(first));
  scanf ("%d", &n);
  for (int i = 0; i < 26; i++) {
    IDS[i][26] = ++Index;
  }
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      IDS[i][j] = ++Index;
    }
  }
  for (int i = 0; i < 26; i++) IDE[i] = ++Index;
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      IDN[i][j] = ++Index;
      add(IDE[i], IDN[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf ("%s%s%s", rd[1], rd[2], rd[3]);
    int a = CalcId(rd[1], 1), b = CalcId(rd[3], 0);
    if (isupper(rd[1][0]) && rd[1][1] == '.') {
      vc[rd[1][0] - 'A'][rd[1][2] - 'a'].push_back(b);
    } else {
      if (a <= 25 && IDE[0] <= b <= IDE[25]) {
        for (int j = 0; j <= 25; j++) {
          add(IDS[rd[1][0] - 'A'][j], IDN[rd[3][0] - 'a'][j]);
          for (auto x : vc[rd[1][0] - 'A'][j]) {
            add(IDN[rd[3][0] - 'a'][j], x);
          }
        }
      }
      add(a, b);
    }
  }
  for (int i = 0; i <= 25; i++) {
    memset (vis, 0, sizeof(vis));
    DFS(IDS[i][26]);
    printf ("%c: ", 'A' + i);
    for (int j = 0; j <= 25; j++) {
      if (vis[IDE[j]]) {
        printf ("%c", 'a' + j);
      }
    }
    printf ("\n");
  }
}