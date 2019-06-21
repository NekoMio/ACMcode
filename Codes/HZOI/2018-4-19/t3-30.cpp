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
char S[300];
double F[(1 << 15) + 1];
int Next(int S, int j, int n)
{
	int i = j;
	while (1)
	{
		if (S & (1 << i)) return i;
		i++;
		if (i == n) i = 0;
	}
	return 0;
}
int main()
{
	// freopen ("3.out", "w", stdout);
	int T = read();
	while (T--)
	{
		scanf ("%s", S + 1);
		int n = strlen(S + 1);
		memset (F, 0, sizeof (F));
		int N = (1 << n) - 1;
		F[0] = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int t = Next(i, j, n);
				F[i] = F[i] + (1.0 / n) * (F[i ^ (1 << t)] + ((t + n - j) % n));
			}
			// printf ("%d = %.3f\n", i, F[i]);
		}
		int s = 0;
		for (int i = 1; i <= n; i++)
			if (S[i] == '.')
				s |= (1 << (i - 1));
		printf ("%.10f\n", F[s]);
	}
