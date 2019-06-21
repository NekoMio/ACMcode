#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
long long f[30][100][(1 << 10) + 1];
int Index;
struct Trie
{
	int S, ID;
	Trie *ch[26];
	Trie *fail;
	Trie(int x)
	{
		S = 0, ID = x;
		memset(ch, 0, sizeof(ch));
		fail = NULL;
	}
}*root, *q[100];
void Insert(char *s, int pos)
{
	int len = strlen(s);
	Trie *rt = root;
	for (int i = 0; i < len; i++)
	{
		if(!rt->ch[s[i]-'a'])
		{
			rt->ch[s[i]-'a'] = new Trie(++Index);
			q[Index] = rt->ch[s[i]-'a'];
		}
		rt = rt->ch[s[i]-'a'];
	}
	rt->S |= (1 << (pos - 1));
}
void Get_fail()
{
	queue<Trie*> Q; 
	for (int i = 0; i < 26; i++)
	{
		if(root->ch[i] != NULL)
		{
			root->ch[i]->fail = root;
			Q.push(root->ch[i]);
		}
	}
	while(!Q.empty())
	{
		Trie *rt = Q.front();
		Q.pop();
		Trie *p = NULL;
		for (int i = 0; i < 26; i++)
		{
			if(rt->ch[i] != NULL)
			{
				p = rt->fail;
				while(p != NULL)
				{
					if(p->ch[i]!=NULL)
					{
						rt->ch[i]->fail = p->ch[i];
						break;
					}
					p = p->fail;
				}
				if(p == NULL)
					rt->ch[i]->fail = root;
				Q.push(rt->ch[i]);
			}
			if(rt->ch[i] == NULL)
				rt->ch[i] = rt->fail->ch[i];
		}
	}
}
int main()
{
	root = new Trie(++Index);
	q[Index] = root;
	int len, n;
	static char s[12][20];
	scanf("%d%d", &len, &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s[i]);
		Insert(s[i], i);
	}
	Get_fail();
	int N = (1 << n) - 1;
	f[0][1][0] = 1;
	for (int i = 0; i < len; i++)
	{
		for (int j = 1; j <= Index; j++)
		{
			for (int S = 0; S <= N; S++)
			{
				//printf("%d,%d,%d:%d ",i, j, S, f[i][j][S]);
				if(f[i][j][S])
				{
					for (int l = 0; l < 26; l++)
					{
						if(q[j]->ch[l] != NULL)
							f[i + 1][q[j]->ch[l]->ID][S | q[j]->ch[l]->S] += f[i][j][S];
						else
							f[i + 1][1][S] += f[i][j][S];
					}
				}
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i <= Index; i++)
		ans += f[len][i][N];
	printf("%lld",ans);
	if(ans > 42)
		return 0;
}