#include <bits/stdc++.h>
using namespace std;
int d[51];
int vis[51];
int Map[51][51], n, m, du[51];
int Find_Min() {
  int Id = -1, Min = 0x3f3f3f;
  for (int i = 1; i <= n; i++) {
    if (du[i] == d[i]) continue;
    if (du[i] - d[i] < Min) {
      Min = du[i] - d[i];
      Id = i;
    }
  }
  return Id;
}
vector<pair<int, int> > vc[51];
bool cmp (const pair<int, int> &a, const pair<int, int> &b) {
  if (a.second != b.second) return a.second < b.second;
  return du[a.first] - d[a.first] > du[b.first] - d[b.first];
}
bool work() {
  while (1) {
    int p = Find_Min();
    if (p == -1) return 1;
    if (du[p] - d[p] < 0) return 0;
    sort(vc[p].begin(), vc[p].end(), cmp);
    int t = du[p] - d[p];
    for (auto x = vc[p].begin(); x != vc[p].end(); x++) {
      if (x->second != 1) {
        x->second = 1;
        for (auto y = vc[x->first].begin(); y != vc[x->first].end(); y++) {
          if (y->first == p) y->second = 1;
        }
        du[p]--; du[x->first]--;
        if (du[p] == d[p]) break;
      }
    }
    if (du[p] > d[p]) return 0;
  }
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    memset (vis, 0, sizeof (vis));
    memset (Map, 0, sizeof (Map));
    memset (du, 0, sizeof (du));
    for (int i = 1; i <= n; i++) vc[i].clear();
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) {
      int num1, num2;
      scanf("%d%d", &num1, &num2);
      vc[num1].push_back(pair<int,int>(num2, 0));
      vc[num2].push_back(pair<int,int>(num1, 0));
      du[num1]++;
      du[num2]++;
      Map[num1][num2] = Map[num2][num1] = 1;  
    }
    // cout<<"HH"<<endl;
    bool ans = work();
    if (ans)
      printf("Yes\n");
    else
      printf("No\n");
  }
}
