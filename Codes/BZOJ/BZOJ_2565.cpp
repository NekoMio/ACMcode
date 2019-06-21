#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
char s[MAXN];
struct Node
{
	int cnt,now,fail[MAXN],len[MAXN],tr[MAXN][26],f[MAXN];
	Node(){cnt = 1; fail[0] = fail[1] = 1; len[1] = -1;}
	void extend(int x, int pos)
	{
		int p = now;
		while(s[pos - len[p] - 1] != s[pos]) p = fail[p];
		if (!tr[p][x])
		{
			int np = ++cnt, q = fail[p]; len[np] = len[p] + 2;
			while (s[pos - len[q] - 1] != s[pos]) q = fail[q];
			fail[np] = tr[q][x];
			tr[p][x] = np;
		}
		now = tr[p][x]; f[pos] = len[now];
	}
}Z, F;

int main()
{
	scanf ("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++) Z.extend(s[i] - 'a', i);
	reverse(s + 1, s + n + 1);
	for (int i = 1; i <= n; i++) F.extend(s[i] - 'a', i);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, Z.f[i] + F.f[n - i]);
	printf ("%d\n", ans);
}