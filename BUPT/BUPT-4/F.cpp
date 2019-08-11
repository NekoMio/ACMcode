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
const int MAXN = 1e6 + 1;
struct edge {
  int END, v, next;
}v[MAXN * 10];
int first[MAXN], p;
void add(int a, int b, int x) {
  v[p].next = first[a];
  v[p].END = b;
  v[p].v = x;
  first[a] = p++;
}
int dis[MAXN];
bool flag[MAXN];
queue<int> q;
bool Spfa(int x)
{
	memset(dis, 0x3f, sizeof (dis));
	memset(flag, 0, sizeof (flag));
	dis[x] = 0;
	flag[x] = 1;
	q.push(x);
	while (!q.empty())
	{
		int k = q.front();
		q.pop();
		flag[k] = 0;
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] > dis[k] + v[i].v)
			{
				dis[v[i].END] = dis[k] + v[i].v;
				if (!flag[v[i].END])
				{
					flag[v[i].END] = 1;
					q.push(v[i].END);
				}
			}
		}
	}
	return 0;
}
void Generate_G(int n, int seed) {
  int nextRand = seed;
  for (int x = 1; x <= n; x++) {
    int w = x % 10 + 1;            // the weight of edges
    int d = 10 - w;                // the number of edges
    for (int i = 1; i <= d; i++) {
        add(x, nextRand % n + 1, w); // add a new edge into G
        nextRand = nextRand * 233 % n;
    }
    add(x, x % n + 1, w);
  }
}
int main() {
  int T = read();
  while (T--) {
    memset (first, -1, sizeof (first));
    p = 0;
    int n = read(), seed = read();
    Generate_G(n, seed);
    Spfa(1);
    printf ("%d\n", dis[n]);
  }
}