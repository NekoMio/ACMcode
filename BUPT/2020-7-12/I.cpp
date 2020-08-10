#include <bits/stdc++.h>
using namespace std;
int d[51];
int vis[51];
struct node {
  int id;
  vector<int> edge;
  bool operator<(const node &x) const {
    return x.edge.size() - d[x.id] < x.edge.size() - d[x.id];
  }
} a[51];
priority_queue<node> pq;
int n, m;
void init() { memset(vis, 0, sizeof(vis)); }
bool work() {
  for (int i = 1; i <= n; i++) pq.push(a[i]);
  while (!pq.empty()) {
    // cout<<"HH"<<endl;
    node temp = pq.top();
    pq.pop();
    if (vis[temp.id]) continue;
    if (temp.edge.size() - d[temp.id] < 0) return false;
    if (temp.edge.size() - d[temp.id] == 0) {
      vis[temp.id] = 1;
      cout << "HH" << endl;
      // continue;
    }
    int len = temp.edge.size();
    cout << len << endl;
    for (int i = 0; i < d[temp.id]; i++) {
      // cout<<"HH"<<endl;
      // vec.erase(remove(vec.begin(),vec.end(),x),vec.end());
      int y = temp.edge[i];
      int id = temp.id;
      a[y].edge.erase(remove(a[y].edge.begin(), a[y].edge.end(), id),
                      a[y].edge.end());
      cout << y << " " << a[y].edge.size() << " " << d[y] << endl;
      if (a[y].edge.size() != 0) pq.push(a[y]);
    }
    // cout<<temp.id<<" "<<temp.edge.size()<<endl;
    a[temp.id].edge.erase(a[temp.id].edge.begin(),
                          a[temp.id].edge.begin() + d[temp.id]);
    cout << temp.id << " " << temp.edge.size() << endl;
    if (a[temp.id].edge.size() != 0) pq.push(a[temp.id]);
  }
  return true;
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    init();
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) {
      int num1, num2;
      scanf("%d%d", &num1, &num2);
      a[num1].id = num1;
      a[num1].edge.push_back(num2);
      a[num2].id = num2;
      a[num2].edge.push_back(num1);
    }
    // cout<<"HH"<<endl;
    bool ans = work();
    if (ans)
      printf("Yes\n");
    else
      printf("No\n");
  }
}
