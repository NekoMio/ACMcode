#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int BASE = 31;
const int MAXN = 105;
char s[MAXN][MAXN];
char t[MAXN];
unsigned int Hash_Table[2][MAXN][MAXN];
unsigned int bin[MAXN];

void Hash(int c)
{
	int n = strlen(s[c] + 1);
	for (int i = 1; i <= n; i++)
		Hash_Table[0][c][i] = Hash_Table[0][c][i - 1] * BASE + s[c][i];
	for (int i = n; i >= 1; i--)
		Hash_Table[1][c][i] = Hash_Table[1][c][i + 1] * BASE + s[c][i];
}

struct Node
{
	Node *ch[26];
	int s;
	int flag;
	Node()
	{
		s = 0, flag = 0;
		memset (ch, 0, sizeof (ch));
	}
}*root = new Node();
void Insert(char *c, int l, int r)
{
	Node *rt = root;
	for (int i = r; i >= l; i--)
	{
		if (rt->ch[c[i] - 'a'] == NULL)
			rt->ch[c[i] - 'a'] = new Node();
		rt = rt->ch[c[i] - 'a'];
		rt->s++;
	}
	rt->flag++;
}

unsigned int GetHash(int x, int L, int R, int type)
{
	if (type == 0)
		return Hash_Table[0][x][R] - Hash_Table[0][x][L - 1] * bin[R - L + 1];
	else
		return Hash_Table[1][x][L] - Hash_Table[1][x][R + 1] * bin[R - L + 1];
}

void Get_Insert(int x)
{
	int n = strlen(s[x] + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			if (GetHash(x, i, j, 0) == GetHash(x, i, j, 1))
				Insert(s[x], i, j);
		}
	}
}

int Query(char *c)
{
	int n = strlen(c + 1);
	Node *rt = root;
	for (int i = n; i >= 1; i--)
	{
		if (rt->ch[c[i] - 'a'] == NULL) return 0;
		rt = rt->ch[c[i] - 'a'];
	}
	return rt->s - rt->flag;
}


int main()
{
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);
	int n = read();
	int op;
	int cnt = 0;
	bin[0] = 1;
	for (int i = 1; i <= 100; i++)
		bin[i] = bin[i - 1] * BASE;
	for (int i = 1; i <= n; i++)
	{
		op = read();
		if (op == 1)
		{
			scanf ("%s", s[++cnt] + 1);
			Hash(cnt);
			Get_Insert(cnt);
		}
		else
		{
			scanf ("%s", t + 1);
			printf ("%d\n", Query(t));
		}
	}
}
