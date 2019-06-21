#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 100005;
int du[MAXN], n, m;
char op[MAXN];
int main()
{
	n = read(), m = read();
	while (m--)
	{
		scanf ("%s", op);
		if (op[0] == 'L')
		{

		}
		else
		{
			
		}
	}
}