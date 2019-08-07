#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
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
const int MAXN = 50005;
int a[MAXN], n, k[MAXN], d[MAXN];
pair<int, int> Max[MAXN];
#define lowbit(_) ((_) & (-(_)))
void Add(int x, int c) {
  for (int i = a[x] + 1; i <= n + 1; i += lowbit(i)) {
    if (Max[i].first < c) {
      Max[i].first = c;
      Max[i].second = x;
    } else if (Max[i].first == c) {
      if (d[Max[i].second] > d[x]) Max[i].second = x;
    }
  }
}
pair<int, int> Query(int x) {
  pair<int, int> ans;
  for (int i = a[x] + 1; i > 0; i -= lowbit(i)) {
    if (ans.first < Max[i].first) {
      ans.first = Max[i].first;
      ans.second = Max[i].second;
    } else if (ans.first == Max[i].first) {
      if (d[ans.second] > d[Max[i].first]) ans.second = Max[i].second;
    }
  }
  return ans;
}
int f[MAXN];
struct edge {
  int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int MAX[MAXN], fa[MAXN], Dep[MAXN];
bool able[MAXN];
void DFS(int rt, int dep) {
  Dep[rt] = dep;
  MAX[rt] = max(MAX[rt], dep);
  for (int i = first[rt]; i != -1; i = v[i].next) {
    DFS(v[i].END, dep + 1);
    MAX[rt] = max(MAX[rt], MAX[v[i].END]);
  }
}
stack<int> st;
int main() {
  int T = read();
  while (T--) {
    memset (first, -1, sizeof (first));
    memset (Max, 0, sizeof (Max));
    memset (MAX, 0, sizeof (MAX));
    memset (able, 0, sizeof (able));
    memset (Dep, 0, sizeof (Dep));
    p = 0;
    n = read();
    for (int i = 1; i <= n; i++)
      a[i] = read();
    for (int i = 1; i <= n; i++)
      k[i] = read();
    for (int i = 1; i <= n; i++)
      d[k[i]] = i;
    f[0] = 0;
    Add(0, 0);
    for (int i = 1; i <= n; i++) {
      int tmp = Query(i).second;
      f[i] = f[tmp] + 1;
      Add(i, f[i]);
      fa[i] = tmp;
      add(tmp, i);
    }
    // for (int i = 1; i <= n; i++) {
    //   printf ("%d ", f[i]);
    // }
    // printf ("\n");
    // for (int i = 1; i <= n; i++) {
    //   printf ("%d ", fa[i]);
    // }
    // printf ("\n");
    DFS(0, 0);
    for (int i = n; i >= 1; i--) {
      st.push(MAX[0]);
      able[k[i]] = 1;
      Dep[k[i]] = 0;
      int t = 0;
      for (int j = k[i]; ; j = fa[j]) {
        int Mx = MAX[j];
        if (able[j]) {
          t = 1;
          MAX[j] = 0;
        } else {
          MAX[j] = Dep[j];
          t = 0;
        }
        for (int l = first[j]; l != -1; l = v[l].next) {
          MAX[j] = max(MAX[j], MAX[v[l].END] - t);
        }
        if (Mx == MAX[j]) break;
        if (j == 0) break;
      }
    }
    while (!st.empty()) {
      printf ("%d ", st.top());
      st.pop();
    }
    printf ("\n");
  }
  // while (1);
}