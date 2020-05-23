#include <bits/stdc++.h>
using namespace std;
deque<int> p[20];
set<int> st[4005];
#define D pair<int, int>
deque<D> Q[20][2];
int tmp;
struct data {
  int a, b;
  bool operator < (const data &d) const {
    return a < d.a;
  }
}S[1005];
void Insert(int x, int t, int dep, int now, int tp) {
  if (t == dep + 1) st[now << 1 | tp].insert(x);
  else {
    if (st[now << 1].count(x)) {
      Insert(x, t, dep + 1, now << 1, tp);
    } else {
      Insert(x, t, dep + 1, now << 1 | 1, tp);
    }
  }
}
void DFS(int l, int r, int now) {
  // if (st[now].size() == 2) {
  //   S[l].a = *st[now].begin();
  //   S[l].b = l;
  //   st[now].erase(S[l].a);
  //   S[r].a = *st[now].begin();
  //   S[r].b = r;
  //   return;
  // }
  if (st[now].size() == 1) {
    S[l].a = *st[now].begin();
    S[l].b = l;
    return;
  }
  int mid = l + r >> 1;
  DFS(l, mid, now << 1);
  DFS(mid + 1, r, now << 1 | 1);
}
int n;
void Print() {
  printf ("ANSWER ");
  DFS(1, n, 1);
  sort(S + 1, S + n + 1);
  for (int i = 1; i <= n; i++) printf ("%d ", S[i].b);
  printf ("\n");
}
bool vis[1005];
int main() {
  int t = 0;
  scanf ("%d", &n);
  Q[t][0].push_back(D(1, n));
  for (int i = 1; i <= n; i++) st[1].insert(i);
  while (++t) {
    bool flag = 1;
    while (!Q[t - 1][0].empty()) {
      D x = Q[t - 1][0].front();
      Q[t - 1][0].pop_front();
      int mid = x.first + x.second >> 1;
      flag = flag & (x.second == x.first);
      Q[t][0].push_back(D(x.first, mid));
      if (mid + 1 <= x.second) Q[t][1].push_back(D(mid + 1, x.second));
    }
    while (!Q[t - 1][1].empty()) {
      D x = Q[t - 1][1].front();
      Q[t - 1][1].pop_front();
      int mid = x.first + x.second >> 1;
      flag = flag & (x.second == x.first);
      Q[t][0].push_back(D(x.first, mid));
      if (mid + 1 <= x.second) Q[t][1].push_back(D(mid + 1, x.second));
    }
    if (flag) {
      Print();
      break;
    } else {
      printf ("ASK ");
      for (auto x : Q[t][0]) {
        for (int i = x.first; i <= x.second; i++)
          p[t].push_back(i);
      }
      printf ("%d ", p[t].size());
      for (auto x : p[t]) printf ("%d ", x);
      printf ("\n");
      fflush(stdout);
      memset (vis, 0, sizeof(vis[0]) * (n + 1));
      for (int i = 1; i <= p[t].size(); i++) {
        scanf ("%d", &tmp);
        vis[tmp] = 1;
        Insert(tmp, t, 0, 1, 0);
      }
      for (int i = 1; i <= n; i++) {
        if (!vis[i])
          Insert(i, t, 0, 1, 1);
      }
    }
  }
}