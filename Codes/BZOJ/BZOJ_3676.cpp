#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 3e5 + 10;
char ch[MAXN];
struct Node
{
	int cnt, now, fail[MAXN], len[MAXN], size[MAXN], tr[MAXN][26];
	Node() {cnt = 1; fail[0] = fail[1] = 1; len[1] = -1;}
	void extend(int x, int pos)
	{
		int p = now;
		while (ch[pos - len[p] - 1] != ch[pos]) p = fail[p];
		if (!tr[p][x])
		{
			int np=++cnt, q = fail[p];
			len[np] = len[p] + 2;
			while (ch[pos - len[q] - 1] != ch[pos]) q = fail[q];
			fail[np] = tr[q][x];
			tr[p][x] = np;
		}
		now = tr[p][x];
		size[now]++;
	}
}PAM;

int main()
{
	scanf ("%s", ch + 1);
	int n = strlen(ch + 1);
	for (int i = 1; i <= n; i++) PAM.extend(ch[i] - 'a', i);
	long long ans = 0;
	for (int i = PAM.cnt; i; i--)
	{
		PAM.size[PAM.fail[i]] += PAM.size[i];
		ans = max(ans, 1ll * PAM.size[i] * PAM.len[i]);
	}
	printf ("%lld\n", ans);
}