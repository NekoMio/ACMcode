#include <bits/stdc++.h>
using namespace std;
string s[2][100];
unordered_map<string, int> mp;
int Big[50][50], id;
bool flag, vis[50];
void DFS(int S) {
  vis[S] = 1;
  for (int i = 1; i <= id; i++) {
    if (Big[S][i]) {
      if (vis[i]) {
        flag = 1;
        break;
      }
      DFS(i);
      if (flag == 1) break;
    }
  }
  vis[S] = 0;
}
bool Judge(int S) {
  flag = 0;
  DFS(S);
  return flag;
}
int main() {
  int n;
  while (~scanf("%d", &n)) {
    id = 0;
    memset (Big, 0, sizeof (Big));
    mp.clear();
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      cin >> s[0][i] >> s[1][i];
      if (!mp.count(s[0][i])) mp[s[0][i]] = ++id;
      if (!mp.count(s[1][i])) mp[s[1][i]] = ++id;
      Big[mp[s[0][i]]][mp[s[1][i]]] = 1;
      if (cnt == 0 && Judge(mp[s[0][i]])) {
        if (cnt == 0) {
          cout << s[0][i] << " " << s[1][i] << "\n";
        }
        cnt = 1;
      }
    }
    if (cnt == 0) printf ("0\n");
  }
}