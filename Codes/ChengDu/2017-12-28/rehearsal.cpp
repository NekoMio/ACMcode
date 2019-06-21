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
const int MAXN = 50005;

int S[MAXN], T[MAXN], W[MAXN];


int main()
{
	//freopen("rehearsal.in", "r", stdin);
	//freopen("rehearsal.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		S[i] = read(), T[i] = read(), W[i] = read();
	for (int i = 1; i <= n; i++)
	{
		int Max = 0, ans = 0;
		for (int j = i - 1; j >= 1; j--)
		{
			if (S[j] > Max && S[j] < S[i])
			{
				Max = S[j];
				if (T[j] < T[i])
					ans += W[j];
			}
			if (Max > S[i]) break;
		}
		printf ("%d\n", ans);
	}
}
