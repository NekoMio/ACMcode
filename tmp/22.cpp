#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <set>
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
void Add(int x) {
  for (int i = a[x] + 1; i <= n + 1; i += lowbit(i)) {
    Max[i] = max(Max[i], pair<int, int>(a[x], x));
  }
}
pair<int, int> Query(int x) {
  pair<int, int> ans;
  for (int i = a[x] + 1; i > 0; i -= lowbit(i)) {
    ans = max(ans, Max[i]);
  }
  return ans;
}
int f[MAXN], pre[MAXN], ans;
bool flag[MAXN];
stack<int> st;
set<int> se;
void Build() {
  int tmp;
  memset (pre, 0, sizeof (pre));
  memset (Max, 0, sizeof (Max));
  memset (f, 0, sizeof (f));
  for (int i = 1; i <= n; i++) {
    if (flag[i]) continue;
    tmp = Query(i).second;
    f[i] = f[tmp] + 1;
    pre[i] = tmp;
    Add(i);
  }
  int pos = 0;
  for (int i = 1; i <= n; i++)
    if (f[i] > f[pos]) pos = i;
  ans = f[pos];
  se.clear();
  for (int i = pos; i != 0; i = pre[i])
    se.insert(i);
}
int main() {
  int T = read();
  while (T--) {
    memset (flag, 0, sizeof(flag));
    n = read();
    for (int i = 1; i <= n; i++)
      a[i] = read();
    for (int i = 1; i <= n; i++)
      k[i] = read();
    Build();
    st.push(ans);
    for (int i = n; i >= 2; i--) {
      flag[k[i]] = 1;
      if (se.count(k[i])) {
        Build();
        st.push(ans);
      } else {
        st.push(ans);
      }
    }
    while (!st.empty()) {
      printf ("%d ", st.top());
      st.pop();
    }
    printf ("\n");
  }
}