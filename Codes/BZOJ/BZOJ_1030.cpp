#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int mod = 10007;
struct Node
{
	bool flag;
	int ID;
	Node* ch[26], *fail;
	Node(int x)
	{
		flag = 0;
		ID = x;
		fail = NULL;
		memset(ch, 0, sizeof(ch));
	}
}*root, *q[6005];
int Index = 0;
void Insert(char *s)
{
	int len = strlen(s);
	Node *rt = root;
	for (int i = 0; i < len; i++)
	{
		if(rt->ch[s[i]-'A'] == NULL)
		{
			rt->ch[s[i]-'A'] = new Node(++Index);
			q[Index] = rt->ch[s[i]-'A'];
		}
		rt = rt->ch[s[i]-'A'];
	}
	rt->flag = 1;
}
queue<Node*> Q;
void Get_fail()
{
	for (int i = 0; i < 26; i++)
		if(root->ch[i])
		{
			root->ch[i]->fail = root;
			Q.push(root->ch[i]);
		}
	while(!Q.empty())
	{
		Node *rt = Q.front();
		rt->flag |= rt->fail->flag;
		Q.pop();
		Node *p = NULL;
		for (int i = 0; i < 26; i++)
		{
			if(rt->ch[i] != NULL)
			{
				p = rt->fail;
				while(p != NULL)
				{
					if(p->ch[i] != NULL)
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
			if(rt->ch[i]==NULL)
				rt->ch[i] = rt->fail->ch[i];
		}
	}
}
char s[105];
int f[6005][6005];
int main()
{
	int n, m;
	root = new Node(++Index);
	q[Index] = root;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s);
		Insert(s);
	}
	Get_fail();
	f[0][1] = 1;
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j <= Index; j++)
			if(!q[j]->flag && f[i][j])
			{
				for (int k = 0; k < 26; k++)
				{
					if(q[j]->ch[k])
						f[i + 1][q[j]->ch[k]->ID] = (f[i + 1][q[j]->ch[k]->ID] + f[i][j]) % mod;
					else
						f[i + 1][1] = (f[i + 1][1] + f[i][j]) % mod;
				}
			}
	}
	int ans = 1;
	for (int i = 1; i <= m; i++)
		ans = ans * 26 % mod;
	for (int i = 1; i <= Index; i++)
		if(!q[i]->flag)
			ans = (ans - f[m][i] + mod) % mod;
	printf("%d", ans);

}