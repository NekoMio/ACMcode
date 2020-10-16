#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 10;
int n;
struct node {
  int len;
  int id;
  int res;
  bool operator<(const node &x) const { return x.len > len; }
  node() {}
  node(int _len, int _id, int _res) {
    len = _len;
    id = _id;
    res = _res;
  }
};
priority_queue<node> pq;
vector<int> fa[maxn];
int e[maxn];
int deg[maxn];
int ans = 0;
void bfs() {
  node start = node(0, 0, -1);
  pq.push(start);
  int tot = -1;
  while (!pq.empty()) {
    node tmp = pq.top();
    pq.pop();
    int len = tmp.len, id = tmp.id, res = tmp.res;
    // cerr<<tot<<" "<<id<<" "<<len<<endl;
    ans = max(ans, tot + len);
    tot++;
    int sz = fa[id].size();
    for (int i = 0; i < sz; i++) {
      deg[fa[id][i]]--;
      //            cerr<<fa[id][i]<<" "<<deg[fa[id][i]]<<endl;
      if (deg[fa[id][i]]) continue;
      pq.push(node(e[fa[id][i]], fa[id][i], tot));
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i];
    int num;
    cin >> num;
    if (!num) fa[0].push_back(i), deg[i]++;
    for (int j = 1; j <= num; j++) {
      int father;
      cin >> father;
      fa[father].push_back(i);
      deg[i]++;
    }
  }
  bfs();
  cout << ans << endl;
}