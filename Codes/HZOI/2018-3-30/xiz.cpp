#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 1000005;
int S[MAXN], T[MAXN], ID[MAXN];
int pre[MAXN], nxt[MAXN], last[MAXN];
int preT[MAXN], nxtT[MAXN], lastT[MAXN];
unsigned int HashS, HashT;
unsigned int bin[MAXN], base = 131;
int main()
{
	int t = read(), c = read();
	while (t--)
	{
		int n = read(), m = read();
		for (int i = 1; i <= n; i++) S[i] = read();
		for (int j = 1; j <= m; j++) T[j] = read();
		bin[0] = 1;
		for (int i = 1; i <= n; i++) bin[i] = bin[i - 1] * base;
		memset (pre, 0, sizeof (pre));
		memset (preT, 0, sizeof (preT));
		memset (nxt, 0, sizeof (nxt));
		memset (nxtT, 0, sizeof (nxtT));
		memset (lastT, 0, sizeof (lastT));
		memset (last, 0, sizeof (last));
		for (int i = 1; i <= n; i++) { pre[i] = last[S[i]], nxt[pre[i]] = i, last[S[i]] = i; }
		for (int i = 1; i <= m; i++) { preT[i] = lastT[T[i]], nxtT[preT[i]] = i, lastT[T[i]] = i; }
		HashT = HashS = 0;
		for (int i = 1; i <= m; i++) 
			HashT = HashT * base + (preT[i] ? i - preT[i] + 1 : 1);
		for (int i = 1; i <= m; i++) 
			HashS = HashS * base + (pre[i] ? i - pre[i] + 1 : 1);
		int cnt = 0;
		for (int i = 1; i <= n - m + 1; i++)
		{
			if (HashS == HashT) ID[++cnt] = i;
			if (nxt[i] && nxt[i] <= i + m)
			{
				HashS -= (nxt[i] - i) * bin[i + m - nxt[i] - 1];
				// HashS -= bin[m - 1];
				// HashS += bin[i + m - nxt[i] - 1];
			}
			HashS -= bin[m - 1];
			// if (pre[S[i + m]])
			HashS = HashS * base + (pre[i + m] > i ? i + m - pre[i + m] + 1 : 1);
			// HashT *= base;
		}
		// return 0;
		printf ("%d\n", cnt);
		for (int i = 1; i <= cnt; i++)
			printf ("%d ", ID[i]);
		printf ("\n");
	}
}