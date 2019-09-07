// #pragma GCC optimize("O2")
#include <bits/stdc++.h>
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
const int MAXN = 205;
struct data {
  int a, b, v, id;
}Query[20005];
int r[MAXN];
struct edge {
  int END, next, v;
}v[MAXN * MAXN];
int first[MAXN], p, Hash[MAXN], cnt;
int Dis[MAXN][MAXN];
void add(int a, int b, int x) {
  v[p].END = b;
  v[p].v = x;
  v[p].next = first[a];
  first[a] = p++;
}
bool vis[MAXN];
bool flag[MAXN];
int dis[MAXN];
// queue<int> Q;
int Q[1000005];
bool Spfa(int x, int L)
{
	memset(dis, 0x3f, sizeof (dis));
	memset(flag, 0, sizeof (flag));
	dis[x] = 0;
  int h = 1, t = 0;
	flag[x] = 1;
	Q[++t] = x;
	while (h <= t)
	{
		int k = Q[h++];
		// Q.pop();
		flag[k] = 0;
    // if (r[k] > L) continue;
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] > dis[k] + v[i].v)
			{
				dis[v[i].END] = dis[k] + v[i].v;
        if (r[v[i].END] > L) continue;
				if (!flag[v[i].END])
				{
					flag[v[i].END] = 1;
					Q[++t] = v[i].END;
				}
			}
		}
	}
	return 0;
}
int ans[20005];
int main() {
  int T = read(), tt = 0;
  while (T--) {
    tt++;
    printf ("Case #%d:\n", tt);
    memset (first, -1, sizeof (first));
    memset (vis, 0, sizeof (vis));
    memset (Dis, 0x3f, sizeof (Dis));
    p = 0;
    int n = read(), q = read(), x;
    for (int i = 1; i <= n; i++) Hash[i] = r[i] = read();
    sort(Hash + 1, Hash + n + 1);
    cnt = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++) r[i] = lower_bound(Hash + 1, Hash + cnt + 1, r[i]) - Hash;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        x = read();
        Dis[i][j] = x;
        if (i != j) add(i, j, x);
      }
    }
    for (int i = 1; i <= q; i++) {
      Query[i].a = read(), Query[i].b = read(), Query[i].v = read();
      if (Query[i].a > Query[i].b) swap(Query[i].a, Query[i].b);
      Query[i].id = i;
    }
    sort(Query + 1, Query + n + 1, [&](const data &A, const data &B) {
      return A.v < B.v;
    });
    int lst = -1;
    for (int i = 1; i <= q; i++) {
      int L = lower_bound(Hash + 1, Hash + cnt + 1, Query[i].v) - Hash;
      if (L == lst) {
        ans[Query[i].id] = Dis[Query[i].a][Query[i].b];
      } else {
        for (int j = 1; j <= n; j++) {
          if (!vis[j] && r[j] <= L) {
            vis[j] = 1;
            Spfa(j, L);
            for (int k = 1; k <= n; k++) {
              for (int l = 1; l < k; l++) {
                Dis[l][k] = min(Dis[l][k], dis[l] + dis[k]);
              }
            }
          }
        }
        lst = L;
        ans[Query[i].id] = Dis[Query[i].a][Query[i].b];
      }
    }
    for (int i = 1; i <= q; i++) printf ("%d\n", ans[i]);
  }
}