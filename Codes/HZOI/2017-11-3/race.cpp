#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
int bin[31];
inline int read()
{
    int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct Node
{
	Node *ch[2];
	int s, f;
#define size(_) ((_)?(_)->s:0)
}*root;
int full = 30;
void Insert(int x)
{
	Node *rt = root;
	for (int i = full; i >= 0; i--)
	{
		int nxt = (x >> i) & 1;
		if (!rt->ch[nxt]) rt->ch[nxt] = new Node();
		rt = rt->ch[nxt];
		rt->s++;
	}
}
int Ans = 0, n, m;
void dfs(Node *rt, long long f, long long ans)
{
	if (rt->ch[0] == NULL && rt->ch[1] == NULL)
	{
		Ans ^= ans;
		return;	
	}
	if (rt->ch[0])
	{
		dfs(rt->ch[0], (f + size(rt->ch[1])) % MOD, (ans + size(rt->ch[1]) * (f + size(rt->ch[1])) % MOD * bin[m - 1] % MOD) % MOD);
	}
	if (rt->ch[1])
	{
		dfs(rt->ch[1], (f + size(rt->ch[0])) % MOD, (ans + size(rt->ch[0]) * (f + size(rt->ch[0])) % MOD * bin[m - 1] % MOD) % MOD);
	}
}
int main()
{
	root = new Node();
	bin[0] = 1;
	for (int i = 1; i <= 30; i++) bin[i] = bin[i - 1] << 1;
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		Insert(read());
	dfs(root, 0, 0);
	printf ("%d", Ans);
	return 0;
}
